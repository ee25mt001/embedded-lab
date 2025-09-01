#include <stdint.h>
#include "tm4c123gh6pm.h"

int main(void) {
    SYSCTL_RCGCGPIO_R |= 0x20;           // Enable clock for Port F
    GPIO_PORTF_LOCK_R = 0x4C4F434B;      // Unlock PF0
    GPIO_PORTF_CR_R = 0x1F;              // Allow changes to PF4-0
    GPIO_PORTF_DIR_R = 0x0E;             // PF1, PF2, PF3 as LEDs
    GPIO_PORTF_DEN_R = 0x1F;             // Digital enable PF4-0
    GPIO_PORTF_PUR_R = 0x11;             // Pull-up resistors on PF0, PF4

    uint8_t n = 0;

    while (1) {
        uint8_t sw1 = GPIO_PORTF_DATA_R & 0x10;

        if (sw1 == 0) {
            GPIO_PORTF_DATA_R &= 0x0E;

            if (n == 0) {
                GPIO_PORTF_DATA_R |= 0x02;
                n = 1;
            }
            else if (n == 1) {
                GPIO_PORTF_DATA_R |= 0x08;
                n = 2;
            }
            else if (n == 2) {
                GPIO_PORTF_DATA_R |= 0x04;
                n = 0;
            }

            while((GPIO_PORTF_DATA_R & 0x10) == 0);
        }
    }
}
