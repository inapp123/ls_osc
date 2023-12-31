// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.4
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"
#include "data_acquire.h"

///////////////////// VARIABLES ////////////////////

// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Chart2;
lv_obj_t * ui_settingsel;
lv_obj_t * ui_topbar;
lv_obj_t * ui_runstopbtn;
lv_obj_t * ui_Label3;
lv_obj_t * ui_singlebtn;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Panel1;
lv_obj_t * ui_Label7;
lv_obj_t * ui_Label8;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Label4;
lv_obj_t * ui_Label9;
lv_obj_t * ui_Label10;
lv_obj_t * ui_Label5;
lv_obj_t * ui_Label6;
lv_obj_t * ui_btnbar;
lv_obj_t * ui_Label12;
lv_obj_t * ui_acquirepanel;
lv_obj_t * ui_timebasepanel;
lv_obj_t * ui_Coupledesc;
lv_obj_t * ui_CoupleBTN1;
lv_obj_t * ui_CoupleBTN2;
lv_obj_t * ui_CoupleBTNLBL1;
lv_obj_t * ui_CoupleBTNLBL2;


lv_obj_t * ui_Timedesc;
lv_obj_t * ui_TimeSel;
lv_obj_t * ui_Voltagedesc;
lv_obj_t * ui_VoltageSel;
lv_obj_t * ui_triggerpanel;
lv_obj_t * ui_trigedgedesc;
lv_obj_t * ui_trigsel;
lv_obj_t * ui_trigvaluedesc;
lv_obj_t * ui_Label13;
lv_obj_t * ui_Panel2;
lv_obj_t * ui_Button2;
lv_obj_t * ui_Label14;
lv_obj_t * ui_Label16;
lv_obj_t * ui_Button1;
lv_obj_t * ui_Label11;
lv_obj_t * ui_Panel3;
lv_obj_t * ui_Button3;
lv_obj_t * ui_Label15;
lv_obj_t * ui_Label17;
lv_obj_t * ui_Button4;
lv_obj_t * ui_Label18;
lv_obj_t * ui_Panel4;
lv_obj_t * ui_Button5;
lv_obj_t * ui_Label19;
lv_obj_t * ui_Label20;
lv_obj_t * ui_Button6;
lv_obj_t * ui_Label21;
lv_obj_t * ui_storagepanel;
lv_obj_t * ui_Timedesc1;
lv_obj_t * ui_Checkbox1;
lv_obj_t * ui_Checkbox2;
lv_obj_t * ui_Checkbox3;
lv_obj_t * ui_Voltagedesc1;
lv_obj_t * ui_VoltageSel1;
lv_obj_t * ui_Button8;
lv_obj_t * ui_Label23;
lv_obj_t * ui_Button7;
lv_obj_t * ui_Label22;
lv_obj_t * ui_cursorpanel;
lv_obj_t * ui_Label25;
lv_obj_t * ui_aboutpanel;
lv_obj_t * ui_Label24;
lv_obj_t * ui_Label26;
lv_obj_t * ui_Label27;
lv_obj_t * ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 32
    #error "LV_COLOR_DEPTH should be 32bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

void selectpanel(ctrl_panel_t panel){
    // lv_roller_get_selected(ui_settingsel);
    lv_obj_add_flag(ui_acquirepanel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_timebasepanel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_triggerpanel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_storagepanel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_cursorpanel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_aboutpanel, LV_OBJ_FLAG_HIDDEN);

    switch(panel){
        case ACQUIRE_PANEL:
            lv_obj_clear_flag(ui_acquirepanel, LV_OBJ_FLAG_HIDDEN);
            break;
        case TIMEBASE_PANEL:
            lv_obj_clear_flag(ui_timebasepanel, LV_OBJ_FLAG_HIDDEN);
            break;
        case TRIGGER_PANEL:
            lv_obj_clear_flag(ui_triggerpanel, LV_OBJ_FLAG_HIDDEN);
            break;
        case STORAGE_PANEL:
            lv_obj_clear_flag(ui_storagepanel, LV_OBJ_FLAG_HIDDEN);
            break;
        case CURSOR_PANEL:
            lv_obj_clear_flag(ui_cursorpanel, LV_OBJ_FLAG_HIDDEN);
            break;
        case ABOUT_PANEL:
            lv_obj_clear_flag(ui_aboutpanel, LV_OBJ_FLAG_HIDDEN);
            break;
    }
}

void settings_dd_cb(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * dd = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED){
        int selected = lv_dropdown_get_selected(dd);
        selectpanel((ctrl_panel_t)selected);
    }
}

void time_roller_cb(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * roller = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED){
        int selected = lv_roller_get_selected(roller);
        char selected_text_buf[30];
        lv_roller_get_selected_str(roller, selected_text_buf, 30);
        lv_label_set_text(ui_Label2, selected_text_buf);
        acquire_set_timebase((timebases_t)selected);
    }
}

void channel_roller_cb(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * roller = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED){
        int selected = lv_roller_get_selected(roller);
        char selected_text_buf[30];
        lv_roller_get_selected_str(roller, selected_text_buf, 30);
        lv_label_set_text(ui_Label4, selected_text_buf);
        acquire_set_channel_att((channel_att_t)selected);
    }
}

void update_trigger_label(int trigger_level, trigger_edge_t edge){
    // ui_Label5
    // char text_buf[30];
    // lv_snprintf(text_buf, 30, "%dmV %s", trigger_level, (edge == RISING_EDGE) ? "上升沿" : "下降沿");
    // lv_label_set_text(ui_Label5, text_buf);
    lv_label_set_text_fmt(ui_Label5, "%dmV %s", trigger_level, (edge == RISING_EDGE) ? "上升沿" : "下降沿");
}

int trig_level = 340;
void trigger_edge_roller_cb(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * roller = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED){
        int selected = lv_roller_get_selected(roller);
        update_trigger_label(trig_level, (trigger_edge_t)selected);
        acquire_set_trigger_edge((trigger_edge_t)selected);
    }
}

void trigger_btn_cb(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED){
        if(btn == ui_Button2){
            trig_level += 1000;
        }
        else if(btn == ui_Button3){
            trig_level += 100;
        }
        else if(btn == ui_Button5){
            trig_level += 20;
        }
        else if(btn == ui_Button1){
            trig_level -= 1000;
        }
        else if(btn == ui_Button4){
            trig_level -= 100;
        }
        else if(btn == ui_Button6){
            trig_level -= 20;
        }

        if(trig_level < -5000){
            trig_level = 5000;
        }
        else if(trig_level > 5000){
            trig_level = -5000;
        }

        lv_label_set_text_fmt(ui_Label13, "%d mV", trig_level);

        acquire_set_trigger_level(trig_level);
        update_trigger_label(trig_level, lv_roller_get_selected(ui_trigsel));
    }
}

void couple_btn_cb(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    couple_mode_t cpm;
    if(code == LV_EVENT_CLICKED){
        if(btn == ui_CoupleBTN1){
            lv_obj_set_style_bg_opa(ui_CoupleBTN1, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(ui_CoupleBTN2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(ui_Label6,"直流");
            cpm = COUPLE_DC;
        }
        else if(btn == ui_CoupleBTN2){
            lv_obj_set_style_bg_opa(ui_CoupleBTN2, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(ui_CoupleBTN1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(ui_Label6,"交流");
            cpm = COUPLE_AC;
        }
        acquire_set_couple_mode(cpm);
    }
}

bool running = true;
void runstop_btn_cb(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED){
        running = !running;
        if(running){
            lv_obj_set_style_bg_opa(ui_runstopbtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        else{
            lv_obj_set_style_bg_opa(ui_runstopbtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        acquire_set_running(running);
    }
}

void single_btn_cb(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED){
        acquire_set_single();
        running = false;
        lv_obj_set_style_bg_opa(ui_runstopbtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}


uint16_t ref1_signal[POINTCNT];
uint16_t ref2_signal[POINTCNT];
uint16_t ref3_signal[POINTCNT];

lv_chart_series_t * ref1_series;
lv_chart_series_t * ref2_series;
lv_chart_series_t * ref3_series;

bool ref1_enable = false;
bool ref2_enable = false;
bool ref3_enable = false;

void save_cb(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED){
        int roller_id = lv_roller_get_selected(ui_VoltageSel1);
        uint16_t * save_dest;
        switch (roller_id)
        {
        case 0:
            save_dest = ref1_signal;
            break;
        case 1:
            save_dest = ref2_signal;
            break;
        case 2:
            save_dest = ref3_signal;
            break;

        default:
            return;
        }

        uint16_t * data = ui_Chart2_series_1->y_points;

        for(int i = 0;i < POINTCNT;i++){
            save_dest[i] = data[i];
        }
    }
}

void ref_checkbox_cb(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * checkbox = lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED){
        if(checkbox == ui_Checkbox1){
            ref1_enable = !ref1_enable;
            if(ref1_enable){
                ref1_series = lv_chart_add_series(ui_Chart2, lv_color_hex(0x57D943), LV_CHART_AXIS_PRIMARY_Y);
                lv_chart_set_ext_y_array(ui_Chart2, ref1_series, ref1_signal);
            }
            else{
                lv_chart_remove_series(ui_Chart2, ref1_series);
            }
        }
        else if(checkbox == ui_Checkbox2){
            ref2_enable = !ref2_enable;
            if(ref2_enable){
                ref2_series = lv_chart_add_series(ui_Chart2, lv_color_hex(0x594ED9), LV_CHART_AXIS_PRIMARY_Y);
                lv_chart_set_ext_y_array(ui_Chart2, ref2_series, ref2_signal);
            }
            else{
                lv_chart_remove_series(ui_Chart2, ref2_series);
            }
        }
        else if(checkbox == ui_Checkbox3){
            ref3_enable = !ref3_enable;
            if(ref3_enable){
                ref3_series = lv_chart_add_series(ui_Chart2, lv_color_hex(0xD923A1), LV_CHART_AXIS_PRIMARY_Y);
                lv_chart_set_ext_y_array(ui_Chart2, ref3_series, ref3_signal);
            }
            else{
                lv_chart_remove_series(ui_Chart2, ref3_series);
            }
        }
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);
    selectpanel(ACQUIRE_PANEL);
}
