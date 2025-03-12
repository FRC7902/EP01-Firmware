#include "Station4.h"
#include "Constants.h"

Station4::Station4(FRC7902TLCDriver *TLCDriver) : m_TLCDriver(TLCDriver)
{
    passed = false;
    failed = false;
    currentSequencePosition = 0;
    m_TLCDriver->clearAllLEDs();
}

void Station4::init()
{
    passed = false;
    failed = false;
    currentSequencePosition = 0;
    m_TLCDriver->clearAllLEDs();

    for (int i = 0; i < 6; i++)
    {
        lastButtonState[i] = false;
        currentLEDState[i] = false;
    }
}

void Station4::periodic()
{
    // Check each of the buttons
    for (int i = 0; i < 6; i++)
    {
        // If the current button is pressed and was not previously and LED is not on
        if (digitalRead(PINS::S4_BUTTON[i]) && !lastButtonState[i] && !currentLEDState[i])
        {   
            
            Serial.println(PINS::S4_BUTTON[i]);

            if (PINS::S4_BUTTON[i] == PINS::S4_SEQUENCE[currentSequencePosition])
            {
                // Turn on the LED and track the state
                m_TLCDriver->setLED(TLC59281::S4_BUTTON_LED[i], true);
                currentLEDState[i] = true;

                // If it is the end of the sequence
                if (currentSequencePosition >= 5)
                {
                    passed = true;
                }
                else
                {
                    currentSequencePosition++;
                }
            }
            else
            {
                failed = true;
            }
        }

        lastButtonState[i] = digitalRead(PINS::S4_BUTTON[i]);
        
    }
}

bool Station4::isFailed()
{
    return failed;
}

void Station4::end()
{
}

bool Station4::isPassed()
{
    return passed;
}