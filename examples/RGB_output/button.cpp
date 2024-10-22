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
    pinMode(pin_, INPUT);
  }

bool Button::GetIsPressed(void)
  {
    is_pressed_ = digitalRead(pin_);    
    return is_pressed_;
  }

uint8_t Button::GetDurationOfPressing(void)
  {
    unsigned long startTime = 0;
    unsigned long stopTime = 0;

    if(GetIsPressed())
      {
        startTime = millis();
        while(GetIsPressed());
        stopTime = millis();
      }

    duration_of_pressing_ = (stopTime - startTime) / 1000;

    return duration_of_pressing_;
  }
