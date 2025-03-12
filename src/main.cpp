#include <Arduino.h>
#include <SPI.h>
#include "Constants.h"
#include "stations/StationBase.h"
#include "stations/Station1.h"
#include "stations/Station2.h"
#include "stations/Station3.h"
#include "stations/Station4.h"
#include "devices/FRC7902SevenSeg.h"
#include "devices/FRC7902TLCDriver.h"

FRC7902TLCDriver LEDDriver;
FRC7902SevenSeg m_numberDisplay(PINS::SEVEN_SEG[0], PINS::SEVEN_SEG[1], PINS::SEVEN_SEG[2], PINS::SEVEN_SEG[3]);
Station1 m_Station1;
Station2 m_Station2;
Station3 m_Station3(&LEDDriver);
Station4 m_Station4(&LEDDriver);

StationBase *station[] = {
    &m_Station1,
    &m_Station2,
    &m_Station3,
    &m_Station4};

int stationIndex = 0;

StationBase *currentStation = station[stationIndex];

void setup()
{
  // clear display
  m_numberDisplay.displayNumber(10);

  Serial.begin(115200);

  for (int i = 0; i < 6; i++)
  {
    pinMode(PINS::S1_WIRE[i], INPUT);
  }

  Serial.begin(115200);

  m_Station2.setLEDColour(0, 0, 0);
  currentStation->init();
  currentStation->periodic();

  while (m_Station1.isPassed() || m_Station1.isFailed())
  {
    m_Station2.setLEDColour(255, 120, 0);
    m_Station1.init();
    currentStation->periodic();
  }

  // Turn LED off an re-init
  m_Station2.setLEDColour(0, 0, 0);
  currentStation->init();
  currentStation->periodic();
}

void loop()
{

  // m_Station3.periodic();
  currentStation->periodic();

  // If the current station has passed
  if (currentStation->isPassed())
  {
    // Set the LED to green
    m_Station2.setLEDColour(0, 255, 0);
    m_numberDisplay.displayNumber(SEVENSEG::CODE[stationIndex]);

    // Move onto the next station if there is one
    if (stationIndex < 3)
    {
      stationIndex++;
      currentStation = station[stationIndex];
      delay(1000);
      m_Station2.setLEDColour(0, 0, 0); // turn LED off
      currentStation->init();
    }
    else
    {
      // Set the LED to green
      while (!m_Station2.buttonPressed() || m_Station1.isPassed())
      {
        m_Station2.setLEDColour(0, 255, 0);
        delay(100);
        m_Station2.setLEDColour(0, 255, 20);
        delay(100);
        m_Station2.setLEDColour(0, 255, 40);
        delay(100);
        m_Station2.setLEDColour(0, 255, 0);
        delay(100);
        m_Station2.setLEDColour(0, 255, 20);
        delay(100);
        m_Station1.periodic();
      }
      // Restart
      m_Station2.setLEDColour(0, 0, 0);
      LEDDriver.clearAllLEDs();
      m_numberDisplay.displayNumber(10);
      stationIndex = 0;
      delay(500);
      currentStation = station[stationIndex];
      currentStation->init();

      //Wait until button no longer pressed
      while (m_Station2.buttonPressed())
      {
      }
    }
  }

  if (currentStation->isFailed())
  {
    
    // Turn 7-seg off
    m_numberDisplay.displayNumber(10);

    // Blink LED red
    for (int i = 0; i < 5; i++)
    {
      m_Station2.setLEDColour(255, 0, 0);
      delay(200);
      m_Station2.setLEDColour(0, 0, 0);
      delay(200);
    }
    m_Station2.setLEDColour(255, 0, 0);
    LEDDriver.clearAllLEDs();

    delay(1000);

    // Restart
    m_Station2.setLEDColour(0, 0, 0);
    stationIndex = 0;
    currentStation = station[stationIndex];
    currentStation->init();
  }
}
