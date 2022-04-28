/**
 * Mcp4xxx.h : Driver for MCP4xxx digipots
 * Author: Matthew Hannah (matthew.r.hannah@gmail.com)
 * Date: April 2022
 */

#include "mbed.h"

class Mcp4xxx {

private:
    static constexpr uint8_t WRITE_CMD = 0x00;
    static constexpr uint8_t READ_CMD = 0x0C;
    static constexpr uint8_t INCR_CMD = 0x04;
    static constexpr uint8_t DECR_CMD = 0x08;

public:
    Mcp4xxx(PinName mosi, PinName miso, PinName sck, PinName cs) :
        spi(mosi, miso, sck),
        cs(cs)
    {
        spi.format(8, 0); // may need to make this 1
        spi.frequency(1e6);
    }

    void set_wiper_tap(uint8_t addr, uint16_t tap) {
        cs = 0;

        ThisThread::sleep_for(1ms);

        uint8_t data[2] {};
        data[0] = ((addr & 0x0F) << 4) |  WRITE_CMD | ((tap & 0x100) >> 8);
        data[1] = tap & 0xFF;

        //printf("cmd: 0x%02x%02x\r\n", data[0], data[1]);

        char read[2] {};
        read[0] = spi.write(data[0]);
        read[1] = spi.write(data[1]);

        //printf("rsp: 0x%02x%02x\r\n", read[0], read[1]);

        cs = 1;
    }

private:
    SPI spi;
    DigitalOut cs;
};