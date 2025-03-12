#ifndef Constants_h
#define Constants_h

#include <Arduino.h>

enum S1_W
{
    S1_W_BLUE = 13,
    S1_W_RED = 12,
    S1_W_ORANGE = 11,
    S1_W_GREEN = 16,
    S1_W_YELLOW = 15,
    S1_W_WHITE = 14
};

enum S3_BTN
{
    S3_BTN_BLUE = 3,
    S3_BTN_RED = 1,
    S3_BTN_GREEN = 0,
    S3_BTN_YELLOW = 2
};

enum S4_BTN
{
    BINDS = 28,
    ATP = 26,
    HYDROXYL = 21,
    PHOSPHATE = 27,
    DNA = 20,
    BOND = 22
};

enum S3_LED
{
    S3_LED_BLUE = 0,
    S3_LED_RED = 1,
    S3_LED_GREEN = 2,
    S3_LED_YELLOW = 3,
};

namespace PINS
{
    constexpr uint8_t SPI_CLK = 18,
                      SPI_TX = 19,
                      LATCH = 17,
                      SDA = 4,
                      SCL = 5;

    constexpr uint8_t SEVEN_SEG[4] = {7, 10, 9, 8};

    constexpr uint8_t S1_WIRE[6] = {S1_W_BLUE,
                                    S1_W_RED,
                                    S1_W_ORANGE,
                                    S1_W_GREEN,
                                    S1_W_YELLOW,
                                    S1_W_WHITE};
    constexpr uint8_t S1_CORRECT = S1_W_ORANGE;
    constexpr uint8_t S2_BUTTON = 6;
    constexpr uint8_t S3_BUTTON[4] = {3, 2, 1, 0};
    constexpr uint8_t S4_BUTTON[6] = {22, 21, 20, 26, 27, 28};
    constexpr uint8_t S3_SEQUENCE[4] = {S3_BTN_GREEN, S3_BTN_RED, S3_BTN_YELLOW, S3_BTN_BLUE};
    constexpr uint8_t S4_SEQUENCE[6] = {BINDS, ATP, HYDROXYL, PHOSPHATE, DNA, BOND};
}

namespace TLC59281
{
    constexpr uint8_t S3_LED = 5;
    constexpr uint8_t S3_BUTTON_LED[4] = {0, 1, 2, 3};
    constexpr uint8_t S4_BUTTON_LED[6] = {13, 12, 11, 8, 9, 10};
}

namespace SEVENSEG
{
    constexpr uint8_t CODE[4] = {2, 5, 3, 6};
}

namespace TIMING
{
    constexpr unsigned long S1_TIME_TO_HOLD_MILLIS = 5000;
}

#endif