#ifndef _MENU_H
#define _MENU_H

typedef enum {
    MAIN_MENU           = 0,
    SEQUENCE_SELECT     = 1,
    FUNCTION_SELECT     = 2,
    STEP_SELECT         = 3,
    MODIFY_STEP         = 4,
    PITCH_MENU          = 5,
    VELOCITY_MENU       = 6,
    GLIDE_MENU          = 7,
    CHANGE_PRESCALER    = 8,
    SET_MIDI_CHANNEL    = 9,
    SET_ACTIVE_STEPS    = 10,
    CHANGE_TEMPO        = 11
} MenuLUT;

#endif