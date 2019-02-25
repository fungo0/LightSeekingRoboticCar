#ifndef __STOP_H__
#define __STOP_H__

#include "BStop.h"

class Stop : public BStop {
public:
  virtual void init();
  virtual void execute();
};

#endif
