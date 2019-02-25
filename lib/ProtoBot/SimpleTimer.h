#ifndef __SIMPLETIMER_H__
#define __SIMPLETIMER_H__

#include <Arduino.h>

class SimpleTimer
{
  private:
  	unsigned long time, lastTime, bootTime, elapsedTick;

  public:
  	void init();
  	void update();
  	unsigned long getTime();
  	unsigned long getBootTime();
  	unsigned long getElapsedTick();
};

extern SimpleTimer simpleTimer;

#endif