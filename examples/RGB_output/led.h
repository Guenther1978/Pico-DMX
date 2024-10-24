#ifndef PICODMX_RGBOUTPUT_LED_H_
#define PICODMX_RGBOUTPUT_LED_H_

#include <Arduino.h>
#include "intensities.h"
#include "speed_control.h"

const uint8_t kBitDimmable = 0x01;
const uint8_t kBitNewFactor = 0x02;
const uint8_t kBitNewMinPointerAtMax = 0x04;
const uint8_t kBitNewMaxPointerAtMin = 0x08;
const uint8_t kBitWaitAtMin = 0x10;
const uint8_t kBitWaitAtMax = 0x20;
const uint8_t kBitLedIsOn = 0x40;

const uint8_t kNumberOfScenes = 12;
const uint8_t kNumberOfLeds = 3;

const uint8_t kMaxProgmemIndex = 4;

struct LedDefaultProperties {
  uint8_t default_booleans;
  uint8_t factor;
  uint8_t offset;
  uint8_t pointer_min;
  uint8_t pointer_max;
  uint8_t progmem_index;
};

const uint8_t kSizeOfProperties = sizeof(struct LedDefaultProperties);

class Led
{

  public:

    Led();
    Led(uint8_t);
    Led(uint8_t, uint8_t);

    ///////////////////////////////////////////////////////
    // methods dealing with the pointer to the intensities
    ///////////////////////////////////////////////////////

    /**Increases the pointer to the intensities.

       If the new value of the pointer is equal
       to the size of the array,
       the pointer will be decreased in the next step;
    */
    void IncreasePointer(void);

    /**Decreases the pointer to the intensities.

      If the new value of the pointer is equal
      to zero, the pointer will be increased in the next step.
    */
    void DecreasePointer(void);

    /**Increases or decreases the pointer.

       In dependency of the boolean value of darker the method
       increasePointer or decreasePointer is called.
    */
    void ChangePointer(void);

    ///
    /// Load default properties from the internal eeprom
    ///
    void LoadProperties(uint8_t);

    ////////////////////////////////////////////////
    // methods dealing with the class SpeedControl
    ////////////////////////////////////////////////

    /**@brief Call counter method of class SpeedControl

       The property counter of the aggregated class SpeedControl
       is decreased. If its value is equal to zero, true is returned.
       The variable is the initialized with the duration.
    */
    bool LetSpeedControlCount(void);

    /**@param duration time at one intensity (property of the class SpeedControl)*/
    void SetSpeedControlDuration(uint8_t);

    /**@return duration (the time at one intensity, property of the class SpeedControl)*/
    uint8_t GetSpeedControlDuration(void);

    /**@param counter

       If a longer duration is wanted, the counter can be set to
       a value greater than duration.
    */
    void SetSpeedControlCounter(uint8_t);

    /**@return counter counts from duration to zero*/
    uint8_t GetSpeedControlCounter(void);

    /** @brief copy the content of the PROGMEM array to the intensity

       The array with the intensities is included in the header file
       'intensities.h'. This file has been created by the python
       script 'progmen_creator.py'.
    */
    void Pointer2Int(void);

    ///////////////////////
    // get and set methods
    ///////////////////////

    void set_address(uint8_t address) {
      address_ = address;
    }
    uint8_t address() const { return address_; } 

    void set_pointer_max_limit(uint8_t limit) {
      pointer_max_limit_ = limit;
    }
    uint8_t pointer_max_limit() const {
      return pointer_max_limit_;
    }
    
    void set_pointer_min_limit(uint8_t limit) {
      pointer_min_limit_ = limit;
    }
    uint8_t pointer_min_limit() const {
      return pointer_min_limit_;
    }
    
    void set_factor_default(uint8_t factor) {
      factor_default_ = factor;
    }
    uint8_t factor_default() const {
      return factor_default_;
    }

    /* offset */

    void set_offset(uint8_t offset) {
      offset_ = offset;
    }
    uint8_t offset() const {
      return offset_;
    }

    void set_progmem_index(uint8_t index) {
      progmem_index_ = index;
    }
    uint8_t progmem_index(void) const {
      return progmem_index_;
    }

    void set_wait_at_max(bool wait) {
      wait_at_max_ = wait;
    }
    bool wait_at_max(void) const {
      return wait_at_max_;
    }

    void set_wait_at_min(bool wait) {
      wait_at_min_ = wait;
    }
    bool wait_at_min(void) const {
      return wait_at_min_;
    }

    void set_pointer(uint8_t pointer) {
      pointer_ = pointer;
    }
    uint8_t pointer() const {
      return pointer_;
    }

    void set_pointer_max(uint8_t pointer) {
      pointer_max_ = pointer;
    }
    uint8_t pointer_max() const {
      return pointer_max_;
    }

    void set_new_max_pointer_at_min(bool pointer) {
      new_max_pointer_at_min_ = pointer;
    }
    bool new_max_pointer_at_min() const {
      return new_max_pointer_at_min_;
    }

    void set_min_pointer(uint8_t pointer) {
      pointer_min_ = pointer;
    }
    uint8_t pointer_min() const {
      return pointer_min_;
    }

    void set_new_min_pointer_at_max(bool pointer) {
      new_min_pointer_at_max_ = pointer;
    }
    bool new_min_pointer_at_max() const {
      return new_min_pointer_at_max_;
    }

    void set_pointer_is_changeable(bool changeable) {
      pointer_is_changeable_ = changeable;
    }
    bool pointer_is_changeable() const {
      return pointer_is_changeable_;
    }

    void set_dimmable(bool dimmable) {
      dimmable_ = dimmable;
    }
    bool dimmable(void) const {
      return dimmable_;
    }

    void set_led_is_on(bool on) {
      led_is_on_ = on;
    }
    bool led_is_on(void) const {
      return led_is_on_;
    }

    void set_initialized(bool initialized) {
      initialized_ = initialized;
    }
    bool initialized() {
      return initialized_;
    }

    void set_dimm_factor(uint8_t factor) {
      dimm_factor_ = factor;
    }
    uint8_t dimm_factor() const {
      return dimm_factor_;
    }

    void set_color_factor(uint8_t);
    uint8_t color_factor() const {
      return color_factor_;
    }

    void set_new_factor(bool new_factor) {
      new_factor_ = new_factor;
    }
    bool new_factor() const {
      return new_factor_;
    }

    void set_darker(bool darker) {
      darker_ = darker;
    }
    bool darker() const {
      return darker_;
    }

    bool darker_has_changed() const {
      return darker_has_changed_;
    }

    void set_number(uint8_t number) {
      number_ = number;
    }
    uint8_t number() const {
      return number_;
    }
    
    bool pointer_is_at_max() const {
      return pointer_is_at_max_;
    }

    bool pointer_is_at_min() const {
      return pointer_is_at_min_;
    }

    void set_intensity(uint8_t intensity) {
      intensity_ = intensity;
    }
    uint8_t intensity() const {
      return intensity_;
    }

  private:
    SpeedControl speed_control_;
    uint8_t address_ = 1;
    uint8_t color_factor_ = 0xFF;
    bool darker_ = true;
    bool darker_has_changed_ = false;
    uint8_t dimm_factor_ = 0xFF;
    bool dimmable_ = true;
    uint8_t factor_default_ = 0xFF;
    bool initialized_ = false;
    uint8_t intensity_ = 0x00;
    bool led_is_on_ = true;
    bool new_max_pointer_at_min_ = false;
    bool new_min_pointer_at_max_ = false;
    bool new_factor_ = false;
    uint8_t number_ = 0;
    uint8_t offset_ = 0;
    uint8_t pointer_ = 0;
    bool pointer_is_at_max_ = false;
    bool pointer_is_at_min_ = false;
    bool pointer_is_changeable_ = true;
    uint8_t pointer_max_ = 255;
    uint8_t pointer_min_ = 0;
    uint8_t pointer_max_limit_ = 255;
    uint8_t pointer_min_limit_ = 0;
    uint8_t progmem_index_ = 0;
    bool wait_at_max_ = false;
    bool wait_at_min_ = false;
};

const uint8_t properties[kNumberOfScenes][kNumberOfLeds][kSizeOfProperties] =\
{{{0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00}},\
 {{0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00}},\
 {{0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00}},\
 {{0x40, 0x7F, 0x00, 0x00, 0xFF, 0x00},\
  {0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00}},\
 {{0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x4D, 0xFF, 0x00, 0x5A, 0xFF, 0x00},\
  {0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00}},\
 {{0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00}},\
 {{0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00}},\
 {{0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00}},\
 {{0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00}},\
 {{0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00}},\
 {{0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x40, 0xFF, 0x00, 0x00, 0xFF, 0x00}},\
 {{0x63, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x63, 0xFF, 0x00, 0x00, 0xFF, 0x00},\
  {0x63, 0xFF, 0x00, 0x00, 0xFF, 0x00}}};


#endif    // PICODMX_RGBOUTPUT_LED_H_
