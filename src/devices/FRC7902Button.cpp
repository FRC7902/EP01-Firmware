#include "FRC7902Button.h";

// Constructor
FRC7902Button::FRC7902Button(uint8_t pinInput, uint8_t normalMode)
{

    digitalInputPin = pinInput;

    if (normalMode == 0 || normalMode == 1)
    {
        normalModeState = normalMode;
    }
    else
    {
        normalMode = 0;
    }
};

/**
 * Initialises limit switch.
 *
 * @note This should be placed in the setup() method
 */
void FRC7902Button::initButton()
{

    pinMode(digitalInputPin, INPUT);
    baselinePressMillis = millis();
    debouncePeriodMillis = 0;
}

void FRC7902Button::configDebounceMillis(uint32_t debounceMillis)
{
    debouncePeriodMillis = debounceMillis;
}

/**
 * Polls and indicates if the limit switch is pressed or not
 *
 * @return true if pressed, false if not pressed
 */
bool FRC7902Button::isPressed()
{
    bool currentPressState = normalModeState ^ digitalRead(digitalInputPin);

    if (debouncePeriodMillis != 0)
    {
        // If the limit switch is currently pressed
        if (currentPressState)
        {
            // If the state has changed
            if (currentPressState != lastPressState)
            {
                baselinePressMillis = millis(); // note the time
            }
            // If the debounce period has been exceeded and the state has not changed
            else if ((millis() - baselinePressMillis) > debouncePeriodMillis)
            {
                return true;
            }
        }

        lastPressState = currentPressState;

        return false;
    }
    else
    {
        return currentPressState;
    }
}

void FRC7902Button::resetDebounce()
{
    baselinePressMillis = millis();
}
