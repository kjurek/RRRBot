#ifndef COMMANDSOMPLITEDSTATE_H
#define COMMANDSOMPLITEDSTATE_H

#include "CommandState.h"

class CCommandCompletedState : CCommandState
{
public:
	static CCommandState* instance();
	virtual void step(CCommand* command);
	virtual void pause(CCommand* command);
	virtual void resume(CCommand* command);
	virtual void abort(CCommand* command);
};

#endif