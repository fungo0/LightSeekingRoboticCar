#ifndef __BRIGHT_H__
#define __BRIGHT_H__
#define __BRIGHT_H__DEBUG 1


#include "Behavior.h"
#include "MotorDriver.h"

class BRight: public Behavior
{
private:

public:
	BRight();
    virtual void execute();
};

#endif
