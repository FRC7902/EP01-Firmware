#ifndef FRC7902TLCDriver_h
#define FRC7902TLCDriver_h

#include <Arduino.h>
#include <math.h>


class FRC7902TLCDriver
{

    // Private
private:

    void sendData(uint16_t data);

public:

    FRC7902TLCDriver();

    void initDriver();
   

    void setLED(uint8_t ledIndex, bool state);
    void clearAllLEDs();

};


#endif