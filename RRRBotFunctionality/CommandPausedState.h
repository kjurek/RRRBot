#ifndef COMMANDPAUSEDSTATE_H
#define COMMANDPAUSEDSTATE_H

#include "CommandState.h"

class CCommandPausedState : public CCommandState
{
public:
	static CCommandState* instance();
	virtual void step(CCommand* command);
	virtual void pause(CCommand* command);
	virtual void resume(CCommand* command);
	virtual void abort(CCommand* command);
};

#endif