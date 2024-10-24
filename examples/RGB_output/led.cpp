#include <Arduino.h>
//#include <EEPROM.h>

#include "led.h"

Led::Led()
{
  address_ = 2;
}

Led::Led(uint8_t address)
{
  address_ = address;
}

Led::Led(uint8_t address, uint8_t number)
{
  address_ = address;
  number_ = number;
}

///////////////////////////////////////////////////////
// methods dealing with the pointer to the intensities
///////////////////////////////////////////////////////

void Led::IncreasePointer()
{
  pointer_ ++;
  if (pointer_ == pointer_max_)
  {
    pointer_is_at_min_ = false;
    pointer_is_at_max_ = true;
    darker_ = true;
    darker_has_changed_ = true;
  }
}

void Led::DecreasePointer()
{
  pointer_ --;
  if (pointer_ == pointer_min_)
  {
    pointer_is_at_min_ = true;
    pointer_is_at_max_ = false;
    darker_ = false;
    darker_has_changed_ = true;
  }
}

void Led::ChangePointer()
{
  if (dimmable_ && pointer_is_changeable_)
  {
    darker_has_changed_ = false;
    if (darker_)
    {
      DecreasePointer();
    }
    else
    {
      IncreasePointer();
    }
  }
}

void Led::LoadProperties(uint8_t scene) {
  //  LedDefaultProperties content;
  //  EEPROM.get (address, content);

  dimmable_ = properties[scene][number_][0] & kBitDimmable;
  new_factor_ = properties[scene][number_][0] & kBitNewFactor;
  new_min_pointer_at_max_ = properties[scene][number_][0] & kBitNewMinPointerAtMax;
  new_max_pointer_at_min_ = properties[scene][number_][0] & kBitNewMaxPointerAtMin;
  wait_at_min_ = properties[scene][number_][0] & kBitWaitAtMin;
  wait_at_max_ = properties[scene][number_][0] & kBitWaitAtMax;
  led_is_on_ = properties[scene][number_][0] & kBitLedIsOn;
  color_factor_ = properties[scene][number_][1];
  offset_ = properties[scene][number_][2];
  pointer_min_limit_ = properties[scene][number_][3];
  pointer_max_limit_ = properties[scene][number_][4];
  progmem_index_ = properties[scene][number_][5];

  if (led_is_on_) {
    pointer_max_ = pointer_max_limit_;
  }
  else {
    pointer_min_ = pointer_min_limit_;
  }
  
  initialized_ = false;
}

////////////////////////////////////////////////
// methods dealing with the class SpeedControl
////////////////////////////////////////////////

bool Led::LetSpeedControlCount()
{
  return speed_control_.count();
}

void Led::SetSpeedControlDuration(uint8_t duration)
{
  speed_control_.set_duration(duration);
}

uint8_t Led::GetSpeedControlDuration()
{
  return speed_control_.duration();
}

void Led::SetSpeedControlCounter(uint8_t counter)
{
  speed_control_.set_counter(counter);
}

uint8_t Led::GetSpeedControlCounter()
{
  return speed_control_.counter();
}

void Led::Pointer2Int()
{
  uint8_t content;
  uint8_t product;
  uint8_t sum;

  if (progmem_index_ > kMaxProgmemIndex)
  {
    switch (progmem_index_)
    {
      case 0:
        content = pgm_read_word_near(intensities_8bit_0 + pointer_);
        break;
      case 1:
        content = pgm_read_word_near(intensities_8bit_1 + pointer_);
        break;
      case 2:
        content = pgm_read_word_near(intensities_8bit_2 + pointer_);
        break;
      case 3:
        content = pgm_read_word_near(intensities_8bit_3 + pointer_);
        break;
      case 4:
        content = pgm_read_word_near(intensities_8bit_4 + pointer_);
        break;

      default:
        break;
    }
  }
  else
  {
    content = pointer_;
  }

  product = (uint8_t)((255 - content) * dimm_factor_) >> 8;
  sum = (255 -  product) * (255 - offset_) >> 8;
  sum += offset_;
  intensity_ = (uint8_t)((color_factor_ * sum) >> 8);
}
