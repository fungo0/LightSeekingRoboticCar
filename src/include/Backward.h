#ifndef __BACKWARD_H__
#define __BACKWARD_H__

#include "BBackward.h"

class Backward : public BBackward {
public:
  virtual void init();
  virtual void execute();
};

#endif
