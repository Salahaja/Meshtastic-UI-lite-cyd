#include "ui.h"

static lv_obj_t * tabview;
static lv_obj_t * node_table;
static lv_obj_t * chat_cont;
static lv_obj_t * kb;
static lv_obj_t * ta;

static void ta_event_cb(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(code == LV_EVENT_FOCUSED) {
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
    if(code == LV_EVENT_DEFOCUSED) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

void ui_init() {
    // Dark Theme Style
    static lv_style_t style_main;
    lv_style_init(&style_main);
    lv_style_set_bg_color(&style_main, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_bg_opa(&style_main, LV_OPA_COVER);
    lv_style_set_text_color(&style_main, lv_color_white());

    // Create TabView
    tabview = lv_tabview_create(lv_scr_act(), LV_DIR_BOTTOM, 40);
    lv_obj_set_style_bg_color(tabview, lv_color_hex(0x000000), 0);
    
    lv_obj_t * t1 = lv_tabview_add_tab(tabview, "Nodes");
    lv_obj_t * t2 = lv_tabview_add_tab(tabview, "Chat");
    lv_obj_t * t3 = lv_tabview_add_tab(tabview, "Trace");

    // --- NODE LIST SCREEN ---
    node_table = lv_table_create(t1);
    lv_obj_set_width(node_table, 300);
    lv_table_set_col_cnt(node_table, 3);
    lv_table_set_col_width(node_table, 0, 120);
    lv_table_set_col_width(node_table, 1, 80);
    lv_table_set_col_width(node_table, 2, 80);
    
    lv_table_set_cell_value(node_table, 0, 0, "Node");
    lv_table_set_cell_value(node_table, 0, 1, "SNR");
    lv_table_set_cell_value(node_table, 0, 2, "Bat");

    // Sample data
    lv_table_set_cell_value(node_table, 1, 0, "Base-01");
    lv_table_set_cell_value(node_table, 1, 1, "5.2");
    lv_table_set_cell_value(node_table, 1, 2, "85%");

    // --- CHAT SCREEN ---
    chat_cont = lv_obj_create(t2);
    lv_obj_set_size(chat_cont, 300, 120);
    lv_obj_align(chat_cont, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_flex_flow(chat_cont, LV_FLEX_FLOW_COLUMN);

    ta = lv_textarea_create(t2);
    lv_obj_set_size(ta, 240, 40);
    lv_obj_align(ta, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_textarea_set_placeholder_text(ta, "Type message...");
    lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, NULL);

    lv_obj_t * send_btn = lv_btn_create(t2);
    lv_obj_set_size(send_btn, 50, 40);
    lv_obj_align(send_btn, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_t * btn_label = lv_label_create(send_btn);
    lv_label_set_text(btn_label, "Send");
    lv_obj_center(btn_label);

    // --- KEYBOARD ---
    kb = lv_keyboard_create(lv_scr_act());
    lv_obj_set_size(kb, 320, 120);
    lv_keyboard_set_textarea(kb, ta);
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);

    // --- TRACEROUTE SCREEN ---
    lv_obj_t * label = lv_label_create(t3);
    lv_label_set_text(label, "Traceroute logic goes here...");
    lv_obj_center(label);
}

void ui_add_node(const char* name, float snr, int bat, const char* dist) {
    // Logic to append to table
}

void ui_add_message(const char* sender, const char* text) {
    lv_obj_t * msg = lv_label_create(chat_cont);
    lv_label_set_text_fmt(msg, "[%s]: %s", sender, text);
}
