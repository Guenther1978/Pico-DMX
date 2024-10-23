#include "rgb_led.h"
#include "button.h"
#include "led.h"

void RgbLedControl::Init(uint8_t address)
{
  for (uint8_t i = 0; i < kNumberOfLeds; i ++)
  {
    led[i].set_address(address + i);
    led[i].set_number(i);
  }
}

void RgbLedControl::LoadProperties(uint8_t scene)
{
  for (uint8_t i = 0; i < kNumberOfLeds; i++)
  {
    led[i].LoadProperties(scene);
  }
}

void RgbLedControl::Update()
{
  for (uint8_t i = 0; i < kNumberOfLeds; i ++)
  {
    if (led[i].initialized())
    {
      if (led[i].dimmable())
      {
        if (led[i].LetSpeedControlCount())
        {
          led[i].ChangePointer();
          led[i].Pointer2Int();
          if (led[i].darker_has_changed())
          {
            led[i].SetSpeedControlDuration(random(DURATION_MAX) + 1);
            if (led[i].pointer_is_at_max())
            {
              if (led[i].new_factor())
              {
                led[i].set_dimm_factor((uint8_t)random(0xFF));
              }
              if (led[i].new_min_pointer_at_max())
              {
                uint8_t number = (uint8_t)random(0xFF);
                if ((number < led[i].pointer()) && (number >= led[i].pointer_min_limit()))
              {
                led[i].set_min_pointer(number);
                }
              }
              if (led[i].wait_at_max())
              {
                if (random(2))
                {
                  for (uint8_t j = 0; j < kNumberOfLeds; j ++)
                  {
                    if (j == i)
                    {
                      led[j].set_pointer_is_changeable(false);
                    }
                    else
                    {
                      if (!(led[j].pointer_is_at_min()))
                      {
                        led[j].set_pointer_is_changeable(true);
                      }
                    }
                  }
                }
              }
            }
            else if (led[i].pointer_is_at_min())
            {
              if (led[i].new_max_pointer_at_min())
              {
                uint8_t number = (uint8_t)random(0xFF);
                if ((number > led[i].pointer()) && (number < led[i].pointer_max_limit()))
                {
                  led[i].set_pointer_max(number);
                }
              }
              if (led[i].wait_at_min())
              {
                if (random(2))
                {
                  for (uint8_t j = 0; j < kNumberOfLeds; j ++)
                  {
                    if (j == i)
                    {
                      led[j].set_pointer_is_changeable(false);
                    }
                    else
                    {
                      if (!(led[j].pointer_is_at_max()))
                      {
                        led[j].set_pointer_is_changeable(true);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else
    {
      if (led[i].led_is_on())

      {
        if (led[i].pointer() < led[i].pointer_max_limit())
        {
          led[i].IncreasePointer();
        }
        else if (led[i].pointer() > led[i].pointer_max_limit())
        {
          led[i].DecreasePointer();
        }
        else  // pointer == pointer_max_limit
        {
          led[i].set_initialized(true);
        }
      }
      else
      {
        if (led[i].pointer() > led[i].pointer_min_limit())
        {
          led[i].DecreasePointer();
        }
        else if (led[i].pointer() < led[i].pointer_min_limit())
        {
          led[i].IncreasePointer();
        }
        else  // pointer == pointer_min_limit
        {
          led[i].set_initialized(true);
        }
      }
    }
    led[i].Pointer2Int();
  }
}
