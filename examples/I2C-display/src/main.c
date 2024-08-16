#include "stm32f722xx.h"

// OLED I2C address 0x78
// I2C_B_SCL    PF1     CN9_19      AF4
// I2C_B_SDA    PF0     CN9_21      AF4

#define GPIOF_AFRL      (*(volatile uint32_t *)(GPIOF_BASE + 0x20))


void init_i2c() {
    RCC->AHB1ENR |= (1 << 5);
    GPIOF->MODER |= 0xA;    // set alternate mode for pf0 and pf1
    GPIOF_AFRL |= 0x44;     // set alternate function 4 for pf0 and pf1

    // set i2c peripheral clock
    // set pe bit in cr1 register
    // set prescaler scldel and sdadel in i2c_timingr register
    // set master clock sclh and scll bits in i2c_timingr
    // 
}

int main(void) {
    init_i2c();

    while(1) {

    }
}
