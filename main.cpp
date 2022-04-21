/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"



// Blinking rate in milliseconds
#define BLINKING_RATE     5ms

#define WRITE_CMD 0x00
#define READ_CMD  0x0C
#define INCR_CMD  0x04
#define DECR_CMD  0x08

void set_ohm(SPI& spi, DigitalOut cs, uint16_t tap) {
    cs = 0;

    ThisThread::sleep_for(1ms);

    char data[2] {};
    data[0] = 0x00 | WRITE_CMD;
    data[1] = tap & 0xFF;

    char read[2] {};
    read[0] = spi.write(data[0]);
    read[1] = spi.write(data[1]);
    //spi.write(data, sizeof(data), read, sizeof(read));

    //printf("wrote: 0x%02x%02x\tread: 0x%02x%02x\r\n", data[0], data[1], read[0], read[1]);

    cs = 1;
}


int main()
{
    printf("test\r\n");
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);
    SPI distortion(p5, p6, p7);
    DigitalOut cs(p20);
    distortion.format(8, 1);
    distortion.frequency(1e6);

    uint8_t data = 0;
    while (true) {
        //led = !led;
        set_ohm(distortion, cs, data);
        data++;
        
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
