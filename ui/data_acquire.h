#pragma once

#include "stdbool.h"

#define POINTCNT 800


typedef enum {
    TIMEBASE_20MS = 0,
    TIMEBASE_2US,
    TIMEBASE_100NS
} timebases_t;

// 1V /div\n200 mV/div\n100 mV/div\n40 mV/div\n20 mV/div\n10 mV/div\n4 mV/div\n2 mV/div\n1 mV/div
typedef enum {
    CHANNEL_ATT_1V = 0,
    CHANNEL_ATT_200MV,
    CHANNEL_ATT_100MV,
    CHANNEL_ATT_40MV,
    CHANNEL_ATT_20MV,
    CHANNEL_ATT_10MV,
    CHANNEL_ATT_4MV,
    CHANNEL_ATT_2MV,
    CHANNEL_ATT_1MV
} channel_att_t;

typedef enum{
    RISING_EDGE = 0,
    FALLING_EDGE
} trigger_edge_t;

typedef enum {
    COUPLE_DC = 0,
    COUPLE_AC
} couple_mode_t;

typedef struct {
    timebases_t timebase;
    channel_att_t channel_att;
    trigger_edge_t trigger_edge;
    int trigger_level;
    couple_mode_t couple_mode;
    bool is_running;
    bool is_single;
} aquire_setting_t;




void acquire_set_timebase(timebases_t timebase);
void acquire_set_channel_att(channel_att_t att);
void acquire_set_trigger_edge(trigger_edge_t edge);
void acquire_set_trigger_level(int level);
void acquire_set_couple_mode(couple_mode_t couple);
void acquire_set_running(bool running);
void acquire_set_single();
int16_t * acquire_get_data();