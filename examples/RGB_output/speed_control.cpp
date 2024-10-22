#include "speed_control.h"

bool SpeedControl::count()
{
  bool counter_is_zero = false;
  counter_ --;
  if (counter_ <= 0)
  {
    counter_ = duration_;
    counter_is_zero = true;
  }
  return counter_is_zero;
}
