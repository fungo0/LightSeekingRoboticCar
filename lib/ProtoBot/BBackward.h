#ifndef __BBACKWARD_H__
#define __BBACKWARD_H__
#define __BBACKWARD_H__DEBUG 1

#include "MotorDriver.h"
#include "Behavior.h"

class BBackward: public Behavior
{
private:

public:
	BBackward();
	virtual void init();
    virtual void execute();
};

#endif
