/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "DebounceIn.h"
#include "Mcp4xxx.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     200ms

int main()
{
    printf("test\r\n");
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);
    DigitalOut upLed(LED2);
    DigitalOut downLed(LED3);
    DebounceIn up(p21);
    DebounceIn down(p22);
    Mcp4xxx distortion(p5, p6, p7, p20);

    static uint16_t steps[] = {
        0, 1, 2, 4, 8, 16, 32, 64, 128, 256
    };

    size_t idx = 0;
    while (true) {
        if (up && idx < (sizeof(steps) / sizeof(steps[0]) - 1)) {
            idx++;
            upLed = !upLed;
        }

        if (down && idx > 0) {
            idx--;
            downLed = !downLed;
        }

        printf("setting 0x%04x\r\n", steps[idx]);
        distortion.set_wiper_tap(0, steps[idx]);

        led = !led;
        
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
