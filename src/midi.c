#include "stm32f722xx.h"
#include "midi.h"
#include "uart.h"

int send_midi_note(
    USART_TypeDef* u,
    MIDIPacket_TypeDef* p
) {
    char buffer[3];
    buffer[0] = p->status | p->channel;
    buffer[1] = p->note;
    buffer[2] = p->velocity;

    return send(u, buffer, 3);
}

int send_midi_control(
    USART_TypeDef* u,
    MIDICC_TypeDef* p
) {
    char buffer[3];
    buffer[0] = p->status | p->channel;
    buffer[1] = p->control;
    buffer[2] = p->value;

    return send(u, buffer, 3);
}