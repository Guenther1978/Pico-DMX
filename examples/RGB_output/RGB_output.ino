/*
   Copyright (c) 2021 Jostein Løwer

   SPDX-License-Identifier: BSD-3-Clause

   Description:
   Starts a DMX Output on GPIO pin 0 and sets all channels to max (255)
*/

#include <Arduino.h>
#include <DmxOutput.h>
#include "led.h"
#include "time_control.h"
#include "play_of_light.h"

// Declare an instance of the DMX Output
DmxOutput dmx;

//Button button;
TimeControl trigger_dmx;
TimeControl scene_timer;
PlayOfLight play_of_light;

// Create a universe that we want to send.
// The universe must be maximum 512 bytes + 1 byte of start code
#define UNIVERSE_LENGTH 512
uint8_t universe[UNIVERSE_LENGTH + 1];

void setup()
{
  trigger_dmx.set_old_millis(millis());
  scene_timer.set_old_millis(millis());

  play_of_light.Init();

  // Start the DMX Output on GPIO-pin 4
  dmx.begin(4);

  // Clear all channels in the universe (512)
  for (int i = 1; i < UNIVERSE_LENGTH + 1; i++)
  {
    universe[i] = 0;
  }
  // Send out universe on GPIO-pin 1
  dmx.write(universe, UNIVERSE_LENGTH);

  play_of_light.UpdateProperties();
}

void loop()
{
  trigger_dmx.WaitMilliseconds(100);

  if (play_of_light.CurrentTimeChooseScene(scene_timer.GetTime()))
  {
    play_of_light.UpdateProperties();
    Serial.print("Neue Szene zum Zeitpunkt: ");
    Serial.println(scene_timer.GetTime());
  }
  play_of_light.UpdateIntensities();

  // Send out universe on GPIO-pin 1
  dmx.write(universe, UNIVERSE_LENGTH);

  while (dmx.busy())
  {
    /* Do nothing while the DMX frame transmits */
  }

  // delay a millisecond for stability (Not strictly necessary)
  delay(1);
}
