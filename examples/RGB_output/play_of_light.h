#ifndef PICODMX_RGBOUTPUT_PLAYOFLIGHT_H_
#define PICODMX_RGBOUTPUT_PLAYOFLIGHT_H_

#include <Arduino.h>

#include "led.h"
#include "rgb_led.h"

const uint8_t kNumberOfRgbs = 3;
const uint8_t kAddressRgb0 = 8;
const uint8_t kAddressRgb1 = 16;
const uint8_t kAddressRgb2 = 24;
const uint8_t kNumberOfScenes = 11;

uint8_t properties[kNumberOfScenes][kNumberOfLeds][kSizeOfProperties];

class PlayOfLight
{
  public:
  PlayOfLight();
  
  void UpdateProperties(void);
  void UpdateIntensities(void);

  void IncreaseScene(void);

  void set_individual(bool individual) { individual_ = individual; }
  bool individual() const { return individual_; }

  void set_scene(uint8_t scene) { scene_ = scene; }
  uint8_t scene() const { return scene_; }
  
  private:
  RgbLedControl rgb_led_control[kNumberOfRgbs];
  bool individual_ = true;
  uint8_t scene_ = 0;
};

//const uint8_t kBitDimmable = 0x01;
//const uint8_t kBitNewFactor = 0x02;
//const uint8_t kBitNewMinPointerAtMax = 0x04;
//const uint8_t kBitNewMaxPointerAtMin = 0x08;
//const uint8_t kBitWaitAtMin = 0x10;
//const uint8_t kBitWaitAtMax = 0x20;
//const uint8_t kBitLedIsOn = 0x40;
//
//struct LedDefaultProperties {
//  uint8_t default_booleans;
//  uint8_t factor;
//  uint8_t offset;
//  uint8_t pointer_min;
//  uint8_t pointer_max;
//  uint8_t progmem_index;
//};














#endif  // PICODMX_RGBOUTPUT_PLAYOFLIGHT_H_
