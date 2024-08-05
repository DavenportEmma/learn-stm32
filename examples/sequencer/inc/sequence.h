#ifndef _SEQUENCE_H
#define _SEQUENCE_H
#include "midi.h"

MIDIStep_TypeDef steps0[] = {
    {NOTE_ON, C2, 127, 0, 0},
    {NOTE_ON, E2, 127, 0, 0},
    {NOTE_ON, G2, 127, 0, 0},
    {NOTE_ON, B2, 127, 0, 0},
    {NOTE_ON, C3, 127, 0, 0},
    {NOTE_ON, B2, 127, 0, 0},
    {NOTE_ON, G2, 127, 0, 0},
    {NOTE_ON, E2, 127, 0, 1}
};

MIDISequence_TypeDef sequence0 = {
    1,
    0,
    8,
    CHANNEL_12,
    steps0
};


MIDIStep_TypeDef steps1[] = {
    {NOTE_ON, C2, 127, 0, 0},
    {NOTE_ON, G2, 127, 0, 1}
};

MIDISequence_TypeDef sequence1 = {
    16,
    0,
    2,
    CHANNEL_2,
    steps1
};


#endif