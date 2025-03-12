#ifndef Station1_h
#define Station1_h

#include <Arduino.h>
#include "StationBase.h"
#include "devices/FRC7902Button.h"

class Station1 : public StationBase
{


public:
    explicit Station1();

    void init();

    void periodic();

    bool isPassed();

    bool isFailed();

    void end();

private:
    bool passed, failed;

};

#endif