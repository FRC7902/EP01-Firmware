#include "FRC7902TLCDriver.h"
#include "Constants.h"

uint16_t ledState = 0x0000; // All LEDs OFF initially

void FRC7902TLCDriver::sendData(uint16_t data)
{
    digitalWrite(PINS::LATCH, LOW); // Keep latch low while shifting data

    for (int i = 15; i >= 0; i--)
    {                                                   // Send MSB first
        digitalWrite(PINS::SPI_TX, (data >> i) & 0x01); // Set data bit
        digitalWrite(PINS::SPI_CLK, HIGH);              // Clock HIGH
        delayMicroseconds(1);                           // Small delay
        digitalWrite(PINS::SPI_CLK, LOW);               // Clock LOW
    }

    digitalWrite(PINS::LATCH, HIGH); // Latch data to outputs
    delayMicroseconds(1);            // Ensure latch time
    digitalWrite(PINS::LATCH, LOW);
}

// Constructor
FRC7902TLCDriver::FRC7902TLCDriver()
{


};

/**
 * Initialises limit switch.
 *
 * @note This should be placed in the setup() method
 */
void FRC7902TLCDriver::initDriver()
{
    pinMode(PINS::SPI_TX, OUTPUT);
    pinMode(PINS::SPI_CLK, OUTPUT);
    pinMode(PINS::LATCH, OUTPUT);

    digitalWrite(PINS::SPI_TX, LOW);
    digitalWrite(PINS::SPI_CLK, LOW);
    digitalWrite(PINS::LATCH, LOW);
}


void FRC7902TLCDriver::setLED(uint8_t ledIndex, bool state)
{
    if (ledIndex > 15)
        return; // Prevent out-of-bounds access

    if (state)
    {
        ledState |= (1 << ledIndex); // Turn on LED
    }
    else
    {
        ledState &= ~(1 << ledIndex); // Turn off LED
    }

    sendData(ledState); // Send updated LED state
}

// Function to turn off all LEDs
void FRC7902TLCDriver::clearAllLEDs() {
    ledState = 0x0000; // Set all bits to 0
    sendData(ledState);
}
