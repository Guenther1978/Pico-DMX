/*
   Copyright (c) 2021 Jostein Løwer

   SPDX-License-Identifier: BSD-3-Clause

   Description:
   Starts a DMX Output on GPIO pin 0 and sets all channels to max (255)
*/

#include <Arduino.h>
#include <DmxOutput.h>
#include "led/led.h"

// Declare an instance of the DMX Output
DmxOutput dmx;

const uint16_t loop_duration = 500;  // in ms
uint8_t intensity = 0;
bool darker = false;
uint16_t current_duration = 0;
uint16_t old_millis;

// Create a universe that we want to send.
// The universe must be maximum 512 bytes + 1 byte of start code
#define UNIVERSE_LENGTH 512
uint8_t universe[UNIVERSE_LENGTH + 1];

void setup()
{
  // Initialize Serial port
  Serial.begin(9600);
//  while (!Serial);
  Serial.println(F("Serial port initialized."));

  old_millis = millis();

  // Start the DMX Output on GPIO-pin 4
  dmx.begin(4);

  // Clear all channels in the universe (512)
  for (int i = 1; i < UNIVERSE_LENGTH + 1; i++)
  {
    universe[i] = 0;
  }
}

void loop()
{
  while (millis() < (old_millis + loop_duration));
  old_millis = millis();

  unsigned char incoming_byte = ' ';
  if (Serial.available())
  {
    incoming_byte = Serial.read();
    Serial.write(incoming_byte);
    Serial.println();
  }
  else
  {
    Serial.println("Nichts empfangen.");
  }

  if (darker == false)
  {
    if (intensity >= 255)
    {
      darker = true;
    }
    else
    {
      intensity ++;
    }
  }
  else
  {
    if (intensity <= 1)
    {
      darker = false;
    }
    else
    {
      intensity --;
    }
  }

  universe[9] = intensity;

  // Send out universe on GPIO-pin 1
  dmx.write(universe, UNIVERSE_LENGTH);

  while (dmx.busy())
  {
    /* Do nothing while the DMX frame transmits */
  }

  // delay a millisecond for stability (Not strictly necessary)
  delay(1);
}
