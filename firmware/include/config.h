#ifndef CONFIG_H
#define CONFIG_H

// --- DISPLAY PINS (ESP32-2432S028) ---
#define TFT_BL 21
#define TFT_CS 15
#define TFT_DC 2
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_RST 12
#define TFT_MISO 12

// --- TOUCH PINS ---
#define TOUCH_CS 33
#define TOUCH_IRQ 36

// --- UART PINS (For Meshtastic Node) ---
// Note: You can use the CN1/CN2 headers
#define MESH_RX 22
#define MESH_TX 27

#endif
