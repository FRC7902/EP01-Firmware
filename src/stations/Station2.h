#ifndef Station2_h
#define Station2_h

#include <Arduino.h>
#include "StationBase.h"
#include "devices/FRC7902Button.h"

class Station2 : public StationBase
{


public:
    explicit Station2();

    void init();

    void periodic();

    bool isPassed();

    bool isFailed();

    void end();

    bool buttonPressed();


    void setLEDColour(uint8_t red, uint8_t green, uint8_t blue);

private:
    bool passed, failed;

    void writeRegister(uint8_t reg, uint8_t value);

    bool startedPress, heldUntilBlink;

    bool lastButtonState, currentButtonState;

    unsigned long currentMillis, startedPressMillis, newBlinkMillis;

    uint8_t totalBlinks = 2;
    uint8_t currentBlinks;

    FRC7902Button button;



};

#endif