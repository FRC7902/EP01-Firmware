#ifndef StationBase_h
#define StationBase_h

#include <Arduino.h>

/**
 * 
 * @brief Template class to build \b Stations
*/
class StationBase
{

public:
    StationBase();

    virtual void init() = 0;

    virtual void periodic() = 0;

    virtual bool isPassed() = 0;

    virtual bool isFailed() = 0;

    virtual void end() = 0;
};

#endif