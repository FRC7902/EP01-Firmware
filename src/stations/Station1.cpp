#include "Station1.h"
#include "Constants.h"

Station1::Station1()
{
    passed = false;
    failed = false;
}

void Station1::init()
{
    passed = false;
    failed = false;
}

void Station1::periodic()
{
    passed = false;
    failed = false;
    
    for (int i = 0; i < 6; i++)
    {

        if (!digitalRead(PINS::S1_WIRE[i]))
        {
            if (PINS::S1_WIRE[i] == PINS::S1_CORRECT)
            {
                passed = true;
                break;
            }
            else
            {
                failed = true;
                break;
            }
        }
    }
}

bool Station1::isFailed(){
    return failed;
}

void Station1::end()
{
}

bool Station1::isPassed(){
    return passed;
}