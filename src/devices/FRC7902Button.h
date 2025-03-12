#ifndef FRC7902Button_h
#define FRC7902Button_h

#include <Arduino.h>
#include <math.h>


class FRC7902Button
{

    // Private
private:
    uint8_t digitalInputPin;

    uint8_t normalModeState;
    
    uint32_t debouncePeriodMillis;

    uint32_t baselinePressMillis;

    bool lastPressState;


public:

    FRC7902Button(uint8_t pinInput, uint8_t normalMode);

    void initButton();

    void configDebounceMillis(uint32_t debounceMillis);

    bool isPressed();

    void resetDebounce();

};


#endif