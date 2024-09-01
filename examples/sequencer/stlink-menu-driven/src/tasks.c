#include "stm32f722xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tasks.h"
#include "menu.h"
#include "config.h"

int wait_for_input() {
    print("wait for input\n\r\0");
    if(!(STLINK_UART->ISR & USART_ISR_RXNE)) {
        print("free\n\r\0");
        return USART3->RDR;
    } else {
        print("blocked\n\r\0");
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  
    }

    // while(!(STLINK_UART->ISR & USART_ISR_RXNE)) {}
    // STLINK_UART->RQR |= USART_RQR_RXFRQ;  // Example: Request a flush of the RX buffer (clears RXNE flag)
    // return STLINK_UART->RDR - '0';
}

void menu_task() {
    int menu_id = SEQUENCE_SELECT;
    int sequence = 0;
    int step = 0;
    switch(menu_id) {
        case SEQUENCE_SELECT:
            print("*** select a sequence ***\n\r\0");
            sequence = wait_for_input();
            menu_id = FUNCTION_SELECT;
            break;
        case FUNCTION_SELECT:
            print("*** choose function ***\n\r\0");
            print("1 - modify step\n\r\0");
            int func = wait_for_input();
            switch(func) {
                case 1:
                    menu_id = STEP_SELECT;
                break;
            }
            break;
        case STEP_SELECT:
            print("*** choose step ***\n\r\0");
            step = wait_for_input();
            menu_id = MODIFY_STEP;
            break;
        case MODIFY_STEP:
            print("*** choose modification ***\n\r\0");
            print("1 - pitch\n\r\0");
            print("2 - velocity\n\r\0");
            print("3 - glide\n\r\0");
            int mod = wait_for_input();
            switch(mod) {
                case 1:
                    menu_id = PITCH_MENU;
                    break;
                case 2:
                    menu_id = VELOCITY_MENU;
                    break;
                case 3:
                    menu_id = GLIDE_MENU;
                    break;
            }
            break;
        case PITCH_MENU:
            print("*** modify pitch ***\n\r\0");
            int pitch = wait_for_input();
            menu_id = SEQUENCE_SELECT;
            break;
        case VELOCITY_MENU:
            print("*** modify velocity ***\n\r\0");
            int velocity = wait_for_input();
            menu_id = SEQUENCE_SELECT;
            break;
        case GLIDE_MENU:
            print("*** modify glide ***\n\r\0");
            int glide = wait_for_input();
            menu_id = SEQUENCE_SELECT;
            break;
    }
}