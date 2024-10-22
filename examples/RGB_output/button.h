/** @file */

#ifndef PICODMX_RGBOUTPUT_BUTTON_H_
#define PICODMX_RGBOUTPUT_BUTTON_H_

#include <Arduino.h>

class Button
{
  public:
    Button();
    Button(uint8_t);

    /**@return isPressed*/
    bool GetIsPressed(void);

    /**@return durationOfPresseing*/
    uint8_t GetDurationOfPressing(void);

    void set_pin(uint8_t);
    uint8_t pin(void);

  private:
    uint8_t pin_ = 2;
    bool is_pressed_;
    uint8_t duration_of_pressing_;
};

#endif  // PICODMX_RGBOUTPUT_BUTTON_H_
