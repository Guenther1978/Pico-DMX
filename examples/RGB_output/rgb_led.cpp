#include "rgb_led.h"

//SoftwareSerial bluetoothCommunicator(2, 3);

void RgbLedControl::setup()
{
  uint8_t index;

  // read current default play of light
  readEeprom();
  playOfLight = defaultPlayOfLight;

  // read led properties for default play of light
  readEeprom(playOfLight);

  oldMillis = millis();

  randomSeed(analogRead(0));

  //  bluetoothCommunicator.begin(9600);

#ifdef PCA9685
  pwm.begin();
#endif

  Serial.begin(9600);
  while (!Serial);
  Serial.print(F("Size of RGB Control default properties: "));
  Serial.println(sizeof(RgbDefaultProperties));
  Serial.print(F("Size of Led default properties: "));
  Serial.println(sizeof(LedDefaultProperties));
  Serial.print(F("Size of play of light: "));
  Serial.println((1 + NUMBER_OF_LEDS * sizeof(LedDefaultProperties)));
  Serial.println("Setup completed");
  Serial.println();

void RgbLedControl::loop()
{
  if (uint8_t durationOfPressing = button.getDurationOfPressing())
  {
    if (durationOfPressing > 4)
    {
      writeEeprom();
    }
    else
    {
      playOfLight ++;
      if (playOfLight >= numberOfPlays)
      {
        playOfLight = 0;
      }
      for (int i = 0; i < NUMBER_OF_LEDS; i ++)
      {
        led[i].setPointerIsChangeable(true);
        led[i].setFactor(0xff);
        led[i].setPointer(0xff);
      }
      readEeprom(playOfLight);
      for (int i = 0; i < NUMBER_OF_LEDS; i ++)
      {
        if (led[i].getLedIsOn()) {
          led[i].setIntensity(0xFF);
        }
        else {
          led[i].setIntensity(0x00);
        }
        led[i].int2output();
      }
    }
  }
  for (uint8_t i = 0; i < NUMBER_OF_LEDS; i ++)
  {
    if led[i].getInitialized()
    {
      if (led[i].getDimmable())
      {
        if (led[i].letSpeedControlCount())
        {
          led[i].changePointer();
          led[i].pointer2int();
          if (led[i].getDarkerHasChanged())
          {
            led[i].setSpeedControlDuration(random(DURATION_MAX) + 1);
            if (led[i].getPointerIsAtMax())
            {
              if (led[i].getNewFactor())
              {
                led[i].setFactor((uint8_t)random(0xFF));
              }
              if (led[i].getNewMinPointerAtMax())
              {
                uint8_t number = (uint8_t)random(0xFF);
                if (number < led[i].getPointer())
                {
                  led[i].setMinPointer(number);
                }
              }
              if (led[i].getWaitAtMax())
              {
                if (random(2))
                {
                  for (uint8_t j = 0; j < NUMBER_OF_LEDS; j ++)
                  {
                    if (j == i)
                    {
                      led[j].setPointerIsChangeable(false);
                    }
                    else
                    {
                      if (!(led[j].getPointerIsAtMin()))
                      {
                        led[j].setPointerIsChangeable(true);
                      }
                    }
                  }
                }
              }
            }
            else if (led[i].getPointerIsAtMin())
            {
              if (led[i].getNewMaxPointerAtMin())
              {
                uint8_t number = (uint8_t)random(0xFF);
                if (number > led[i].getPointer())
                {
                  led[i].setMaxPointer(number);
                }
              }
              if (led[i].getWaitAtMin())
              {
                if (random(2))
                {
                  for (uint8_t j = 0; j < NUMBER_OF_LEDS; j ++)
                  {
                    if (j == i)
                    {
                      led[j].setPointerIsChangeable(false);
                    }
                    else
                    {
                      if (!(led[j].getPointerIsAtMax()))
                      {
                        led[j].setPointerIsChangeable(true);
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
          if (led[i].getLedIsOn)
        }
#ifdef PCA9685
      pwm.setPWM(led[i].getNumber(), 0, led[i].getIntensity());
#else
      led[i].int2output();
#endif
      }
      loopDuration = millis() - oldMillis;
      while (millis() < (oldMillis + cycleTime));
      oldMillis = millis();

    unsigned char RgbLedControl::getPlayOfLight(void)
    {
      return playOfLight;
    }

    void RgbLedControl::setPlayOfLight(bool bt)
    {
      byte incomingByte = 0;
      if (!bt)
      {
        incomingByte = (byte)getNumber();
        if (incomingByte <= numberOfPlays)
        {
          playOfLight = incomingByte - 1;
        }
      }

      for (int i = 0; i < NUMBER_OF_LEDS; i ++)
      {
        led[i].setPointerIsChangeable(true);
        led[i].setFactor(0xff);
        led[i].setPointer(0xff);
      }
      readEeprom(playOfLight);
      for (int i = 0; i < NUMBER_OF_LEDS; i ++)
      {
        if (led[i].getLedIsOn()) {
          led[i].setIntensity(0xFF);
        }
        else {
          led[i].setIntensity(0x00);
        }
        led[i].int2output();
      }
    }

    unsigned char RgbLedControl::getDefaultPlayOfLight(void)
    {
      return defaultPlayOfLight;
    }

    void RgbLedControl::setDefaultPlayOfLight(bool bt)
    {
      byte incomingByte = 0;
      if (!bt)
      {
        incomingByte = (byte)getNumber();
        if (incomingByte < numberOfPlays)
        {
          defaultPlayOfLight = incomingByte;
          writeEeprom();
        }
      }

      for (int i = 0; i < NUMBER_OF_LEDS; i ++)
      {
        led[i].setPointerIsChangeable(true);
        led[i].setFactor(0xff);
        led[i].setPointer(0xff);
      }
      readEeprom(playOfLight);
    }

    unsigned char RgbLedControl::getNumberOfPlays(void)
    {
      return numberOfPlays;
    }

    void RgbLedControl::setNumberOfPlays(void)
    {
      byte incomingByte = 0;
      incomingByte = (byte)getNumber();
      if (incomingByte < NUMBER_OF_PLAYS)
      {
        numberOfPlays = incomingByte;
      }
      writeEeprom();
    }

 

    void RgbLedControl::changeLoopDuration(bool bt)
    {
      uint8_t newCycleTime = 0;
      byte incomingByte = ' ';

      if (bt)
      {
        //   if (bluetoothCommunicator.available())
        //   {
        //     incomingByte = bluetoothCommunicator.read() - ASCII_OFFSET;
        //   }
      }
      else
      {
        incomingByte = getNumber();
      }

      if ((incomingByte > 0) && (incomingByte < 16))
      {
        newCycleTime = incomingByte * 5;
        cycleTime = (unsigned long)newCycleTime;
      }
    }
