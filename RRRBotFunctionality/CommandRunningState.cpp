#include "CommandRunningState.h"
#include "CommandCompletedState.h"
#include "CommandPausedState.h"

CCommandState* CCommandRunningState::instance()
{
	static CCommandRunningState inst;
	return &inst;
}

void CCommandRunningState::step(CCommand* command)
{
	if (command->hasNextStep())
	{
		command->commandStep();
	}
	else
	{
		command->m_pState = CCommandCompletedState::instance();
	}
}

void CCommandRunningState::pause(CCommand* command)
{
	command->m_pState = CCommandPausedState::instance();
}

void CCommandRunningState::resume(CCommand* command)
{
	return;
}

void CCommandRunningState::abort(CCommand* command)
{
	command->m_pState = CCommandCompletedState::instance();
}