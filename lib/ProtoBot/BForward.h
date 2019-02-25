#ifndef __BFORWARD_H__
#define __BFORWARD_H__
#define __BFORWARD_H__DEBUG 1

#include "MotorDriver.h"
#include "Behavior.h"

class BForward: public Behavior
{
private:

public:
	BForward();
	virtual void init();
  virtual void execute();
};

#endif
