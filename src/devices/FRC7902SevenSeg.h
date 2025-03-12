#ifndef FRC7902SevenSeg_h
#define FRC7902SevenSeg_h

#include <Arduino.h>
#include <math.h>


class FRC7902SevenSeg
{

    // Private
private:
    uint8_t pin_d0, pin_d1, pin_d2, pin_d3;


public:

    FRC7902SevenSeg(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);

    void initDriver();

    void displayNumber(int num);

};


#endif