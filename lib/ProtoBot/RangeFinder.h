#ifndef __RANGEFINDER_H__
#define __RANGEFINDER_H__
#define __RANGEFINDER_H__DEBUG 1
#define PING_TIMEOUT 10000
#define PING_SAMPLES 4


#include <Arduino.h>

class RangeFinder
{
  private:
		long calcDistance(long time, int flag);
		long ping();
		long filterRange(long samples[]);

  public:
		int transmitPin, echoPin;

		void init(int tp, int ep);
		virtual long getDistance();
};

extern RangeFinder rangeFinder;

#endif
