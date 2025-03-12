#ifndef Station4_h
#define Station4_h

#include <Arduino.h>
#include "StationBase.h"
#include "devices/FRC7902Button.h"
#include "devices/FRC7902TLCDriver.h"

class Station4 : public StationBase
{

public:
    explicit Station4(FRC7902TLCDriver *TLCDriver);

    void init();

    void periodic();

    bool isPassed();

    bool isFailed();

    void end();

private:
    FRC7902TLCDriver *m_TLCDriver;

    bool passed, failed;

    bool lastButtonState[6] = {false, false, false, false, false, false};
    bool currentLEDState[6] = {false, false, false, false, false, false};

    uint8_t currentSequencePosition;
};

#endif