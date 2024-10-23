#include "button.h"

Button::Button(void)
  {
    pinMode(pin_, INPUT);
  }

Button::Button(uint8_t pin)
  {
    pin_ = pin;
    pinMode(pin_, INPUT);
  }

uint8_t Button::pin(void)
  {
    return pin_;
  }

void Button::set_pin(uint8_t pin)
  {
    pin_ = pin;
    pinMode(pin_, INPUT_PULLUP);
  }

bool Button::GetIsPressed(void)
  {
    is_pressed_ = !digitalRead(pin_);    
    return is_pressed_;
  }

uint8_t Button::GetDurationOfPressing(void)
  {
    unsigned long start_time = 0;
    unsigned long stop_time = 0;

    if(GetIsPressed())
      {
        start_time = millis();
        while(GetIsPressed());
        stop_time = millis();
      }

    duration_of_pressing_ = (stop_time - start_time) / 1000;

    return duration_of_pressing_;
  }
