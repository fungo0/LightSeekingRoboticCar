#include "LightSensor.h"

void LightSensor::init()
{

  _LightSensor1.begin();
  _LightSensor2.begin();

  _LightSensor1.SetAddress(Device_Address_H);//Address 0x5C
  _LightSensor2.SetAddress(Device_Address_L);//Address 0x23

  _LightSensor1.SetMode(Continuous_H_resolution_Mode);
  _LightSensor2.SetMode(Continuous_H_resolution_Mode);

}

uint16_t LightSensor::getLuxForHighAddress()
{
  return _LightSensor1.GetLightIntensity();
}

uint16_t LightSensor::getLuxForLowAddress()
{
  return _LightSensor2.GetLightIntensity();
}

LightSensor lightSensor;
