#include "play_of_light.h"

#include <Arduino.h>

#include "led.h"

PlayOfLight::PlayOfLight()
{
  rgb_led_control[0].Init(kAddressRgb0);
  rgb_led_control[1].Init(kAddressRgb1);
  rgb_led_control[2].Init(kAddressRgb2);

  randomSeed(analogRead(0));
}

void PlayOfLight::UpdateIntensities(void)
{
  for (uint8_t i = 0; i < kNumberOfRgbs; i++)
  {
    for (uint8_t j = 0; j < kNumberOfLeds; j++)
    {
      rgb_led_control[i].Update();
    }
  }
}

void PlayOfLight::UpdateProperties(void)
{
  for (uint8_t j = 0; j < kNumberOfLeds; j++)
  {
    for (uint8_t i = 0; i < kNumberOfRgbs; i++)
    {
      rgb_led_control[i].LoadProperties(scene_);
    }
  }
}

void PlayOfLight::IncreaseScene(void)
{
  scene_ ++;
  if (scene_ >= kNumberOfScenes)
  {
    scene_ = 0;
  }
}
