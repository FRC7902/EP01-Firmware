#include "FRC7902SevenSeg.h"
#include "Constants.h"


FRC7902SevenSeg::FRC7902SevenSeg(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
{
    pin_d0 = d0;
    pin_d1 = d1;
    pin_d2 = d2;
    pin_d3 = d3;
}

void FRC7902SevenSeg::initDriver()
{
    pinMode(pin_d0, OUTPUT);
    pinMode(pin_d1, OUTPUT);
    pinMode(pin_d2, OUTPUT);
    pinMode(pin_d3, OUTPUT);
}

void FRC7902SevenSeg::displayNumber(int num)
{

    if (num < 0 || num > 10)
        return; // Only allow 0-9

    // Convert number to BCD
    digitalWrite(pin_d0, num & 0x01);
    digitalWrite(pin_d1, num & 0x02);
    digitalWrite(pin_d2, num & 0x04);
    digitalWrite(pin_d3, num & 0x08);
}


