#ifndef PICODMX_RGBOUTPUT_SPEEDCONTROL_H_
#define PICODMX_RGBOUTPUT_SPEEDCONTROL_H_

#include <Arduino.h>

class SpeedControl
{
  public:
    /**
       @return (counter == 0)

       The method decreases the counter, if the counter
       has the value zero, true is returned.
    */
    bool count();
    //
    //  void set_counter(uint8_t counter) { counter_ = counter; }
    //  uint8_t counter_() { return counter_; }

    //  /**@param number of the LED*/
    //  void setNumber(uint8_t);
    //  /**@return number of the LED*/
    //  uint8_t getNumber();

    void set_duration(uint8_t duration) {
      duration_ = duration;
    }

    uint8_t duration() const {
      return duration_;
    }

    void set_counter(uint8_t counter) {
      counter_ = counter;
    }
    
    uint8_t counter() const {
      return counter_;
    }

  private:
    uint8_t counter_ = 1;
    uint8_t duration_ = 1;
};

#endif  // PICODMX_RGBOUTPUT_SPEEDCONTROL_H_
