#ifndef __CRANGEFINDER_H__
#define __CRANGEFINDER_H__

#include "RangeFinder.h"
#include <Thread.h>
#include <sensors/PingUltrasonic.h>

class cRangeFinder : public RangeFinder {
public:
  virtual long getDistance(PingUltrasonic* sensor);
};


#endif
