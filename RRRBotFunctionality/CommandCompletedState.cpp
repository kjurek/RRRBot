#include "CommandCompletedState.h"
#include "CommandPausedState.h"

CCommandState* CCommandCompletedState::instance()
{
	static CCommandCompletedState inst;
	return &inst;
}

void CCommandCompletedState::step(CCommand* command)
{
	if (!command->m_completed)
	{
		command->m_completed = true;
	}
}

void CCommandCompletedState::pause(CCommand* command)
{
	if (!command->m_completed)
	{
		command->m_completed = true;
	}
}

void CCommandCompletedState::resume(CCommand* command)
{
	if (!command->m_completed)
	{
		command->m_completed = true;
	}
}

void CCommandCompletedState::abort(CCommand* command)
{
	if (!command->m_completed)
	{
		command->m_completed = true;
	}
}