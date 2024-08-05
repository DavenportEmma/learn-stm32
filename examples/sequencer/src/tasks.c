#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tasks.h"
#include "uart.h"
#include "start_up.h"

#include "sequence.h"

void MIDI_task() {
    uint8_t stack_counter = 0;

    while(1) {
        MIDIPacket_TypeDef previous_step;
        if(stack_counter == 0) {
            previous_step = midi_sequence[SEQUENCE_LENGTH - 1];
        } else {
            previous_step = midi_sequence[stack_counter - 1];
        }

        if(previous_step.glide == 0) {
            previous_step.status = NOTE_OFF;
            send_midi_note(USART1, &previous_step);
        }

        if(send_midi_note(USART1, &midi_sequence[stack_counter]) > 0) {
            char msg[] = "timeout\n\r";
            send(USART3, msg, sizeof(msg)-1);
        }

        if(previous_step.glide == 1) {
            previous_step.status = NOTE_OFF;
            send_midi_note(USART1, &previous_step);
        }

        stack_counter++;
        if(stack_counter >= SEQUENCE_LENGTH) {
            stack_counter = 0;
        }

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}