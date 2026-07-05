#ifndef UI_H
#define UI_H

#include <lvgl.h>

void ui_init();

// Update functions to be called from main loop when data arrives
void ui_add_node(const char* name, float snr, int bat, const char* dist);
void ui_add_message(const char* sender, const char* text);

#endif
