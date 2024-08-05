#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_gcc.h"
#include "stm32f722xx.h"
#include "uart.h"
#include "midi.h"
#include "start_up.h"

MIDIPacket_TypeDef midi_stack[] = {
    {
        NOTE_ON, CHANNEL_12, A2, 127
    },
    {
        NOTE_ON, CHANNEL_12, C3, 126
    },
    {
        NOTE_OFF, CHANNEL_12, A2, 0
    },
    {
        NOTE_OFF, CHANNEL_12, C3, 0
    },
    {
        NOTE_ON, CHANNEL_12, E3, 126
    },
    {
        NOTE_ON, CHANNEL_12, G2, 126
    },
    {
        NOTE_OFF, CHANNEL_12, E3, 0
    },
    {
        NOTE_OFF, CHANNEL_12, G2, 0
    },
};

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    char msg[] = "stack overflow\n\r";
    send(USART3, msg, sizeof(msg)-1);
    __disable_irq();
}

int main(void) {
    start_up();
    xTaskCreate(MIDI_task, "MIDI Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    vTaskStartScheduler();

    while(1) {
        
    }
}