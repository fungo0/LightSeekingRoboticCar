#include "include/cRangeFinder.h"
#include <ArduinoSensors.h>

long cRangeFinder::getDistance(PingUltrasonic* sensor) {
  return sensor->readDistance()-10.0;
}
