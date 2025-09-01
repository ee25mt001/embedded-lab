#include <stdint.h>
#include "tm4c123gh6pm.h"
int main(void) {
    SYSCTL_RCGCGPIO_R |= 0x20;          // To enable clock for Port F
    GPIO_PORTF_LOCK_R = 0x4C4F434B;  // Unlocking PF0
    GPIO_PORTF_CR_R = 0x1F;           // allowing changes to PF4-0
    GPIO_PORTF_DIR_R = 0x0E; // PF3, PF2, PF1 as output-LEDs, PF4 & PF0 as input
    GPIO_PORTF_DEN_R = 0x1F;          // to enable digital function for PF4-0
    GPIO_PORTF_PUR_R = 0x11;          // to enable pull-up for PF4 and PF0

    while (1) {
        uint8_t sw0 = GPIO_PORTF_DATA_R & 0x01;  // PF0
        uint8_t sw1 = GPIO_PORTF_DATA_R & 0x10;  // PF4

        if (!sw0 && sw1) {     // SW0 pressed, SW1 not pressed
            GPIO_PORTF_DATA_R = 0x02;   // Red LED (PF1)
        }
        else if (sw0 && !sw1) {     // SW1 pressed, SW0 not pressed
            GPIO_PORTF_DATA_R = 0x04;   // Blue LED (PF2)
        }
        else if (!sw0 && !sw1) {    // Both pressed
            GPIO_PORTF_DATA_R = 0x06;   // Red and Blue LED
        }
        else {       // None pressed
            GPIO_PORTF_DATA_R = 0x00;   // LEDs off
        }
    }
}
