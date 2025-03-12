#include "Station2.h"
#include "Constants.h"
#include <Wire.h>

#define LP5810_I2C_ADDR 0x6C // Update this based on your I²C scan results
// LP5810 Register Addresses
#define REG_CHIP_EN 0x000
#define REG_LED_ENABLE 0x020
#define REG_CURRENT_CTRL 0x030
#define REG_PWM_CTRL 0x040

// LED Channel Mapping
#define RED_CHANNEL 0x000   // OUT0
#define GREEN_CHANNEL 0x001 // OUT1
#define BLUE_CHANNEL 0x002  // OUT2

void Station2::writeRegister(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(LP5810_I2C_ADDR);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

Station2::Station2() :  button(PINS::S2_BUTTON, 0)
{
    passed = false;
    failed = false;
    lastButtonState = false;
    currentButtonState = false;
    currentBlinks = 0;
    button.configDebounceMillis(100);
}

void Station2::init()
{
    passed = false;
    failed = false;
    currentBlinks = 0;
    setLEDColour(0, 0, 0);
    delay(500);
    setLEDColour(0, 0, 255);
}

bool Station2::buttonPressed(){
    return button.isPressed();
}

void Station2::periodic()
{

    currentMillis = millis();
    currentButtonState = button.isPressed();

    if (currentButtonState && !lastButtonState)
    {
        startedPress = true;
        startedPressMillis = millis();
        delay(50);
    }

    currentMillis = millis();
    // If the button was pressed and it is within 5 seconds of holding
    if (startedPress && (currentMillis - startedPressMillis) < TIMING::S1_TIME_TO_HOLD_MILLIS)
    {
        // If the button is no longer pressed
        if (!currentButtonState){
            failed = true;
        }
    }
    // If the button is pressed and more than 5 seconds have elapsed
    else if (startedPress && (currentMillis - startedPressMillis) > TIMING::S1_TIME_TO_HOLD_MILLIS)
    {
        if (currentButtonState){

            for (int i = 0; i< totalBlinks; i++){
                setLEDColour(0, 0, 0);
                delay(100);
                setLEDColour(0, 0, 255);
                delay(100);
                // if they let go mid-blinks
                if (!currentButtonState){
                    failed = true;
                    break;
                }
            }
            passed = true; //delete
            heldUntilBlink = true;
        }
    }

    lastButtonState = currentButtonState;
}

bool Station2::isFailed()
{
    return failed;
}

void Station2::end()
{
}

void Station2::setLEDColour(uint8_t red, uint8_t green, uint8_t blue)
{
    // Wire.setSDA(PINS::SDA);
    // Wire.setSCL(PINS::SCL);
    Wire.begin();

    // Enable the LP5810 chip
    writeRegister(REG_CHIP_EN, 0x01);
    writeRegister(0x001, 0x01);
    writeRegister(0x00D, 0x0B);
    writeRegister(0x010, 0x55);
    writeRegister(0x020, 0x0F);

    // Enable all LED channels
    writeRegister(REG_LED_ENABLE, 0x0F);

    // Set current control for each channel to 10mA
    // Assuming maximum current is set to 25.5mA
    // 10mA / 25.5mA * 255 ≈ 100 (0x64)
    writeRegister(REG_CURRENT_CTRL + RED_CHANNEL, 0xC8);
    writeRegister(REG_CURRENT_CTRL + GREEN_CHANNEL, 0xC8);
    writeRegister(REG_CURRENT_CTRL + BLUE_CHANNEL, 0xC8);

    writeRegister(REG_PWM_CTRL + RED_CHANNEL, red);
    writeRegister(REG_PWM_CTRL + GREEN_CHANNEL, green);
    writeRegister(REG_PWM_CTRL + BLUE_CHANNEL, blue);
}

bool Station2::isPassed()
{
    return passed;
}