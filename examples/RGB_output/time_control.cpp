#include "time_control.h"

TimeControl::TimeControl(void)
  {
  }

TimeControl::TimeControl(unsigned long time)
  {
    delay_time_ = time;
  }

void TimeControl::Start()
{
	time_has_elapsed_ = false;
	old_millis_ = millis();
}

bool TimeControl::Compare()
{
	time_has_elapsed_ = (millis() - old_millis_) > delay_time_;
	return time_has_elapsed_;
}

unsigned long TimeControl::GetTime()
{
	unsigned long elapsed_time = (millis() - old_millis_) / 1000;
	return elapsed_time;
}

void TimeControl::WaitMilliseconds()
{
  old_millis_ = millis();
  while ((millis() - old_millis_) < delay_time_);
}

void TimeControl::WaitMilliseconds(unsigned long time)
{
	old_millis_ = millis();
	while ((millis() - old_millis_) < time);
}
