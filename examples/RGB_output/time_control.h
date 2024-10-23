/** @file */

#ifndef PICODMX_RGBOUTPUT_TIMECONTROL_H_
#define PICODMX_RGBOUTPUT_TIMECONTROL_H_

#include <Arduino.h>

class TimeControl
{
  public:
    TimeControl();
    TimeControl(unsigned long);

    void Start(void);
    bool Compare(void);
    unsigned long GetTime(void);
    void WaitMilliseconds(void);
    void WaitMilliseconds(unsigned long);

    void set_delay_time(unsigned long time) { delay_time_ = time; }
    unsigned long delay_time() const { return delay_time_; }
    
    void set_old_millis(unsigned long time) { old_millis_ = time; }
    unsigned long old_millis() const { return old_millis_; }

    bool time_has_elapsed() const {return time_has_elapsed_; }

  private:
    unsigned long delay_time_ = 50;  // in ms
    unsigned long old_millis_ = 0;   // in ms
    bool time_has_elapsed_ = false;
};

#endif  // PICODMX_RGBOUTPUT_TIMECONTROL_H_
