#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include <XPT2046_Touchscreen.h>
#include "config.h"
#include "ui.h"
#include "meshtastic_handler.h"

SPIClass touchSPI = SPIClass(VSPI);
XPT2046_Touchscreen touch(XPT2046_CS, XPT2046_IRQ);
TFT_eSPI tft = TFT_eSPI();

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

/* Reading input device (Touchscreen) */
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  if (touch.touched()) {
    TS_Point p = touch.getPoint();
    // Calibration for 320x240 landscape
    data->point.x = map(p.x, 200, 3700, 0, 320);
    data->point.y = map(p.y, 240, 3800, 0, 240);
    data->state = LV_INDEV_STATE_PR;
  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}

void setup() {
  Serial.begin(115200);
  
  // Meshtastic UART (Use IO22/IO27 or similar available pins)
  // Serial2.begin(115200, SERIAL_8N1, 22, 27);

  // Initialize Display
  tft.begin();
  tft.setRotation(1); // Landscape
  tft.setBrightness(255);

  // Initialize Touch
  touchSPI.begin(25, 39, 32, TOUCH_CS); // CLK, MISO, MOSI, CS
  touch.begin(touchSPI);
  touch.setRotation(1);

  // Initialize LVGL
  lv_init();
  
  static lv_disp_draw_buf_t draw_buf;
  static lv_color_t buf[320 * 10];
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, 320 * 10);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = 320;
  disp_drv.ver_res = 240;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  // Initialize Meshtastic UI
  ui_init();
  meshtastic_init();
}

void loop() {
  lv_timer_handler();
  meshtastic_loop();
  delay(5);
}
