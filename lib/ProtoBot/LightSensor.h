#ifndef __LIGHTSENSOR_H__
#define __LIGHTSENSOR_H__
#define __LIGHTSENSOR_H__DEBUG 1

#include <Arduino.h>
#include "../BH1750FVI/BH1750FVI.h" // Sensor Library
#include <Wire.h> // I2C Library

class LightSensor
{
  private:
    BH1750FVI _LightSensor1;
    BH1750FVI _LightSensor2;

  public:
		void init();
    uint16_t getLuxForHighAddress();
		uint16_t getLuxForLowAddress();
};

extern LightSensor lightSensor;

#endif
