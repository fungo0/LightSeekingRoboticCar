#ifndef __FORWARD_H__
#define __FORWARD_H__

#include "BForward.h"

class Forward : public BForward {
public:
  virtual void init();
  virtual void execute();
};

#endif
