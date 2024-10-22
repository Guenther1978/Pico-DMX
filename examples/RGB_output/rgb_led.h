/**@file */

#ifndef RGB_LED_CONTROL_H
#define RGB_LED_CONTROL_H

#include <stdint.h>
#include <Arduino.h>
#include "led.h"
#include "speed_control.h"
//#include "PwmSource.h"
//#include "button.h"

/* Constants for EEPROM  */
#define ADDRESS_NUMBER_OF_DEFAULT_PLAY 0
#define ADDRESS_NUMBER_OF_PLAYS 1
#define LENGTH_OF_LED_PROPERTIES 14
#define LENGTH_OF_PLAY_PROPERTIES 2 + (3 * LENGTH_OF_LED_PROPERTIES)
#define OFFSET_RED 2
#define OFFSET_GREEN OFFSET_RED + LENGTH_OF_LED_PROPERTIES
#define OFFSET_BLUE OFFSET_GREEN + LENGTH_OF_LED_PROPERTIES
#define OFFSET_LOOP_DURATION 0
#define OFFSET_GLOBAL_FACTOR 1
#define OFFSET_COLOR_PROGMEM_INDEX 1

/* Constants */
#define NUMBER_OF_PROGMEMS 6
#define MAX_NUMBER_OF_PLAYS 10
#define LINEAR 5
#define NUMBER_OF_PLAYS 12
#define DEFAULT_PROGMEM_NUMBER 0
#define DEFAULT_PLAY_OF_LIGHT 0
#define DEFAULT_GLOBAL_FACTOR 0xFF
#define DELAY_TIME 20
#define DURATION_MAX 3
#define FULL_INTENSITY 255
#define DELAY_TEST 1000
#define ASCII_OFFSET 48

//struct RgbDefaultProperties {
//  uint8_t number_of_plays;
//  uint8_t play_at_por;
//  uint8_t number_of_leds;
//  unsigned char format_of_numbers;
//  unsigned char language;
//  unsigned char button_pressed;
//};

//const uint8_t kNumberOfLeds = 3;

class RgbLedControl
{
  public:
    void Init(uint8_t);

    /**@brief This function repeats the updates of
       the intensites of the leds.

       Every element of the Led Class is called. Their
       intensities are updated and at the min or max value
       a new duration of the speed is evaluated.
    */
    void Update();

    void LoadProperties(uint8_t);

  private:
    Led led[kNumberOfLeds]; /**< Array of instances of the class Led */
    uint8_t address_;  // address of first led
};

#endif
