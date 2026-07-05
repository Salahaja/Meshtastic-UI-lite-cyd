/**
 * @file lv_conf.h
 * Configuration file for v8.3.x
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

/* Use a custom tick source (Arduino millis) */
#define LV_TICK_CUSTOM 1
#if LV_TICK_CUSTOM
    #define LV_TICK_CUSTOM_INCLUDE "Arduino.h"
    #define LV_TICK_CUSTOM_SYS_TIME_EXPR (millis())
#endif

/* Color settings - CYD uses 16-bit color */
#define LV_COLOR_DEPTH 16
#define LV_COLOR_16_SWAP 0

/* Memory settings - Allocate 32KB for UI elements */
#define LV_MEM_CUSTOM 0
#define LV_MEM_SIZE (32U * 1024U)
#define LV_MEM_ADR 0

/* Features we need for the Meshtastic UI */
#define LV_USE_TABLE 1
#define LV_USE_LABEL 1
#define LV_USE_BTN 1
#define LV_USE_TEXTAREA 1
#define LV_USE_KEYBOARD 1
#define LV_USE_TABVIEW 1
#define LV_USE_LIST 1
#define LV_USE_FLEX 1

/* Default Font */
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_DEFAULT &lv_font_montserrat_14

#endif /*LV_CONF_H*/
