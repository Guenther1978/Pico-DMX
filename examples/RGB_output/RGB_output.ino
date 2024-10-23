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

Button button;
TimeControl trigger_dmx;
PlayOfLight play_of_light;

// Create a universe that we want to send.
// The universe must be maximum 512 bytes + 1 byte of start code
#define UNIVERSE_LENGTH 512
uint8_t universe[UNIVERSE_LENGTH + 1];

void setup()
{
  trigger_dmx.set_old_millis(millis());

  // Start the DMX Output on GPIO-pin 4
  dmx.begin(4);

  // Clear all channels in the universe (512)
  for (int i = 1; i < UNIVERSE_LENGTH + 1; i++)
  {
    universe[i] = 0;
  }
  // Send out universe on GPIO-pin 1
  dmx.write(universe, UNIVERSE_LENGTH);

//  while ((button.GetDurationOfPressing()) < 1);

  play_of_light.UpdateProperties();
}

void loop()
{
  trigger_dmx.WaitMilliseconds(100);

  play_of_light.UpdateIntensities();  


  for (uint8_t i = 0; i < kNumberOfRgbs; i ++)
  {
    for (uint8_t j = 0; j < kNumberOfLeds; j ++)
    {
      universe[play_of_light.rgb_led_control[i].led[j].address()] = play_of_light.rgb_led_control[i].led[j].intensity();
    }
  }
//  universe[9] = intensity;

  // Send out universe on GPIO-pin 1
  dmx.write(universe, UNIVERSE_LENGTH);

  while (dmx.busy())
  {
    /* Do nothing while the DMX frame transmits */
  }

  // delay a millisecond for stability (Not strictly necessary)
  delay(1);

//  if (uint8_t durationOfPressing = button.GetDurationOfPressing())
//  {
//    if (durationOfPressing > 1)
//    {
//      play_of_light.IncreaseScene();
//      play_of_light.UpdateProperties();
//    }
//  }
}
