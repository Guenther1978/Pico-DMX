#include "play_of_light.h"

#include <Arduino.h>

#include "led.h"

void PlayOfLight::Init()
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

void PlayOfLight::CurrentTimeChooseScene(unsigned long time)
{
  if ((time >= seconds[0]) && (time < seconds[1]))
  {
    scene_ = 1;
  }
  else if ((time >= seconds[1]) && (time < seconds[2]))
  {
    scene_ = 2;
  }
  else if ((time >= seconds[2]) && (time < seconds[3]))
  {
    scene_ = 3;
  }
  else if ((time >= seconds[3]) && (time < seconds[4]))
  {
    scene_ = 4;
  }
  else if ((time >= seconds[4]) && (time < seconds[5]))
  {
    scene_ = 5;
  }
  else if ((time >= seconds[5]) && (time < seconds[6]))
  {
    scene_ = 6;
  }
  else if ((time >= seconds[6]) && (time < seconds[7]))
  {
    scene_ = 7;
  }
  else if ((time >= seconds[7]) && (time < seconds[8]))
  {
    scene_ = 8;
  }
  if ((time >= seconds[8]) && (time < seconds[9]))
  {
    scene_ = 9;
  }
  if ((time >= seconds[9]) && (time < seconds[10]))
  {
    scene_ = 10;
  }
  if ((time >= seconds[10]) && (time < seconds[11]))
  {
    scene_ = 11;
  }
  else
  {
    scene_ = 0;
  }
}
