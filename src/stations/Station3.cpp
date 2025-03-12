#include "Station3.h"
#include "Constants.h"

Station3::Station3(FRC7902TLCDriver *TLCDriver) : m_TLCDriver(TLCDriver)
{
    passed = false;
    failed = false;
    currentSequencePosition = 0;
    m_TLCDriver->clearAllLEDs();
}

void Station3::init()
{
    passed = false;
    failed = false;
    currentSequencePosition = 0;
    m_TLCDriver->clearAllLEDs();
    m_TLCDriver->setLED(TLC59281::S3_LED, true);

    for (int i = 0; i < 4; i++)
    {
        lastButtonState[i] = false;
        currentLEDState[i] = false;
    }
}

void Station3::periodic()
{
    // Check each of the buttons
    for (int i = 0; i < 4; i++)
    {
        // If the current button is pressed and was not previously and LED is not on
        if (digitalRead(PINS::S3_BUTTON[i]) && !lastButtonState[i] && !currentLEDState[i])
        {   
            
            Serial.println(PINS::S3_BUTTON[i]);

            if (PINS::S3_BUTTON[i] == PINS::S3_SEQUENCE[currentSequencePosition])
            {
                // Turn on the LED and track the state
                m_TLCDriver->setLED(TLC59281::S3_BUTTON_LED[i], true);
                currentLEDState[i] = true;

                // If it is the end of the sequence
                if (currentSequencePosition >= 3)
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

        lastButtonState[i] = digitalRead(PINS::S3_BUTTON[i]);
        
    }
}

bool Station3::isFailed()
{
    return failed;
}

void Station3::end()
{
}

bool Station3::isPassed()
{
    return passed;
}