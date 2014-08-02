#ifndef COMMANDSTATE_H
#define COMMANDSTATE_H

#include "Command.h"

class CCommandState
{
public:
	virtual void step(CCommand* command) = 0;
	virtual void pause(CCommand* command) = 0;
	virtual void resume(CCommand* command) = 0;
	virtual void abort(CCommand* command) = 0;
};

#endif