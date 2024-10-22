#include "rgb_led.h"
#include "button.h"
#include "led.h"

void RgbLedControl::Init(uint8_t address)
{
  for (uint8_t i = 0; i < kNumberOfLeds; i ++)
  {
    led[i].set_address(address + i);
  }
  // read current default play of light
  //readEeprom();
  //playOfLight = defaultPlayOfLight;

  // read led properties for default play of light
  //readEeprom(playOfLight);

  //oldMillis = millis();

  //randomSeed(analogRead(0));

  //  Serial.begin(9600);
  //  while (!Serial);
  //  Serial.print(F("Size of RGB Control default properties: "));
  //  Serial.println(sizeof(RgbDefaultProperties));
  //  Serial.print(F("Size of Led default properties: "));
  //  Serial.println(sizeof(LedDefaultProperties));
  //  Serial.print(F("Size of play of light: "));
  //  Serial.println((1 + NUMBER_OF_LEDS * sizeof(LedDefaultProperties)));
  //  Serial.println("Setup completed");
  //  Serial.println();
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
//  if (uint8_t duration_of_pressing = button.GetDurationOfPressing())
//  {
//    if (duration_of_pressing > 1)
//    {
//      playOfLight ++;
//      if (playOfLight >= numberOfPlays)
//      {
//        playOfLight = 0;
//      }
//      for (int i = 0; i < NUMBER_OF_LEDS; i ++)
//      {
//        led[i].set_pointer_is_changeable(true);
//        led[i].set_dimm_factor(0xff);
//        led[i].set_pointer(0x00);
//      }
//      //     // readEeprom(playOfLight);
//      //      for (int i = 0; i < NUMBER_OF_LEDS; i ++)
//      //      {
//      //        if (led[i].getLedIsOn()) {
//      //          led[i].set_intensity(0xFF);
//      //        }
//      //        else {
//      //          led[i].set_intensity(0x00);
//      //        }
//      //        led[i].int2output();
//      //      }
//    }
//  }
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

//  unsigned char RgbLedControl::getPlayOfLight(void)
//  {
//    return playOfLight;
//  }
//
//  void RgbLedControl::setPlayOfLight(bool bt)
//  {
//    byte incomingByte = 0;
//    if (!bt)
//    {
//      incomingByte = (byte)getNumber();
//      if (incomingByte <= numberOfPlays)
//      {
//        playOfLight = incomingByte - 1;
//      }
//    }
//
//    for (int i = 0; i < NUMBER_OF_LEDS; i ++)
//    {
//      led[i].setPointerIsChangeable(true);
//      led[i].setFactor(0xff);
//      led[i].setPointer(0xff);
//    }
//    readEeprom(playOfLight);
//    for (int i = 0; i < NUMBER_OF_LEDS; i ++)
//    {
//      if (led[i].getLedIsOn()) {
//        led[i].setIntensity(0xFF);
//      }
//      else {
//        led[i].setIntensity(0x00);
//      }
//      led[i].int2output();
//    }
//  }
//
//  unsigned char RgbLedControl::getDefaultPlayOfLight(void)
//  {
//    return defaultPlayOfLight;
//  }
//
//  void RgbLedControl::setDefaultPlayOfLight(bool bt)
//  {
//    byte incomingByte = 0;
//    if (!bt)
//    {
//      incomingByte = (byte)getNumber();
//      if (incomingByte < numberOfPlays)
//      {
//        defaultPlayOfLight = incomingByte;
//        writeEeprom();
//      }
//    }
//
//    for (int i = 0; i < NUMBER_OF_LEDS; i ++)
//    {
//      led[i].setPointerIsChangeable(true);
//      led[i].setFactor(0xff);
//      led[i].setPointer(0xff);
//    }
//    readEeprom(playOfLight);
//  }
//
//  unsigned char RgbLedControl::getNumberOfPlays(void)
//  {
//    return numberOfPlays;
//  }
//
//  void RgbLedControl::setNumberOfPlays(void)
//  {
//    byte incomingByte = 0;
//    incomingByte = (byte)getNumber();
//    if (incomingByte < NUMBER_OF_PLAYS)
//    {
//      numberOfPlays = incomingByte;
//    }
//    writeEeprom();
//  }
//
//
//
//  void RgbLedControl::changeLoopDuration(bool bt)
//  {
//    uint8_t newCycleTime = 0;
//    byte incomingByte = ' ';
//
//    if (bt)
//    {
//      //   if (bluetoothCommunicator.available())
//      //   {
//      //     incomingByte = bluetoothCommunicator.read() - ASCII_OFFSET;
//      //   }
//    }
//    else
//    {
//      incomingByte = getNumber();
//    }
//
//    if ((incomingByte > 0) && (incomingByte < 16))
//    {
//      newCycleTime = incomingByte * 5;
//      cycleTime = (unsigned long)newCycleTime;
//    }
//  }
