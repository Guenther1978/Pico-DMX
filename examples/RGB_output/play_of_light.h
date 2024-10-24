#ifndef PICODMX_RGBOUTPUT_PLAYOFLIGHT_H_
#define PICODMX_RGBOUTPUT_PLAYOFLIGHT_H_

#include <Arduino.h>

#include "led.h"
#include "rgb_led.h"
#include "button.h"
#include "time_control.h"

const uint8_t kNumberOfRgbs = 3;
const uint8_t kAddressRgb0 = 8;
const uint8_t kAddressRgb1 = 16;
const uint8_t kAddressRgb2 = 24;
//const uint8_t kNumberOfScenes = 12;

const uint16_t seconds[kNumberOfScenes] =  {18, 45, 70, 133, 195, 380, 442, 522, 593, 657, 738, 915};

class PlayOfLight
{
  public:
    void Init();

    void UpdateProperties(void);
    void UpdateIntensities(void);

    void IncreaseScene(void);
    bool CurrentTimeChooseScene(unsigned long);

    void set_individual(bool individual) {
      individual_ = individual;
    }
    bool individual() const {
      return individual_;
    }

    void set_scene(uint8_t scene) {
      scene_ = scene;
    }
    uint8_t scene() const {
      return scene_;
    }

    RgbLedControl rgb_led_control[kNumberOfRgbs];

  private:

    bool individual_ = true;
    uint8_t scene_ = 0;
};

#endif  // PICODMX_RGBOUTPUT_PLAYOFLIGHT_H_
