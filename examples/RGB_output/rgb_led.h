/**@file */

#ifndef RGB_LED_CONTROL_H
#define RGB_LED_CONTROL_H

#include <stdint.h>
#include <Arduino.h>
#include "led.h"
#include "speed_control.h"
//#include "PwmSource.h"
//#include "Button.hpp"

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
#define NUMBER_OF_LEDS 3
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

struct RgbDefaultProperties {
  uint8_t number_of_plays;
  uint8_t play_at_por;
  uint8_t number_of_leds;
  unsigned char format_of_numbers;
  unsigned char language;
  unsigned char button_pressed;
};

class RgbLedControl
{
  private:
    Led8bit led[NUMBER_OF_LEDS]; /**< Array of instances of the class Led */
//    Button button;
    unsigned char playOfLight;
    unsigned char numberOfPlays;
    unsigned char defaultPlayOfLight;
    unsigned long cycleTime;
    unsigned long loopDuration;
    unsigned long oldMillis;
    byte incomingByte;
  public:
    /**@brief This function initializes the LightSnake class.

       The class contains one instance of the class
       Adafruit_PWMServoDriver and an array of the
       class Led. The random generator and the class
       Serial will be initialized, too.
    */
    void setup();

    /**@brief This function repeats the updates of
       the intensites of the leds.

       Every element of the Led Class is called. Their
       intensities are updated and at the min or max value
       a new duration of the speed is evaluated. The new
       intensities are send via the I2C bus to the PCA9685.
    */
    void loop();

    /** @return playOfLight */
    unsigned char getPlayOfLight(void);

    /**@brief sets the play of light*/
    void setPlayOfLight(bool);

    /** @return defaultplayOfLight */
    unsigned char getDefaultPlayOfLight(void);

    /**@brief sets the play of light*/
    void setDefaultPlayOfLight(bool);

    /** @return playOfLight */
    unsigned char getNumberOfPlays(void);

    /**@brief sets the play of light*/
    void setNumberOfPlays(void);

    /**@brief This method sets a new duration time for the loop.

       The time sets the duration for the loop. If this value is
       to small, the function will not wait and start immediately
       with the next cycle.
       After each cycle the methods waits till the duration of
       a cycle is over. A loop duration can be set with a
       char. This character represent a hexadecimal digit.
       Hexadecimal number are used (0..9, A, B, C, D, E, F).
       The new duration time is this digit multiplied by 5 ms.
       At the end of the loop, the output of millis() is polled.
       If the value 0 is choosen, the next loop starts immediately.
    */
    void changeLoopDuration(bool);

    /**@brief This method sets the beginning of an array.

       There can be different arrays containing the intensities.
       With this method the index of the progmem is set globally
       for all LEDs.
    */
    void setIndex(bool);

    /**@brief This method sets if a LED is dimmable */
    void setDimmable(void);

    /**@brief This method sets if a LED is on or off */
    void setLedIsOn(void);

    /**@brief This method sets if a LED is initialized */
    void SetInialized(void);

    /**@brief This method sets the offset of the brightness of a LED.*/
    void setOffset(bool);

    /**@brief This method sets if the factor changes.*/
    void setNewFactor(void);

    /**@brief This mehtod sets if the pointer chages at min. position.*/
    void setNewMinPointerAtMax(void);

    /**@brief This mehtod sets if the pointer chages at max. position.*/
    void setNewMaxPointerAtMin(void);

    /**@brief This mehtod sets min. pointer.*/
    void setMinPointer(void);

    /**@brief This mehtod sets max. pointer.*/
    void setMaxPointer(void);

    /**@brief This method sers if waiting or not at the max. pointer */
    void setWaitAtMax(void);

    /**@brief This method sets if waiting or not at the min. pointer */
    void setWaitAtMin(void);

    /**@brief Sets the colorfactors */
    void setColorFactors(void);


};

#endif
