#include "CommandPausedState.h"
#include "CommandRunningState.h"
#include "CommandCompletedState.h"

CCommandState* CCommandPausedState::instance()
{
	static CCommandPausedState inst;
	return &inst;
}

void CCommandPausedState::step(CCommand* command)
{
	return;
}

void CCommandPausedState::pause(CCommand* command)
{
	return;
}

void CCommandPausedState::resume(CCommand* command)
{
	command->m_pState = CCommandRunningState::instance();
}

void CCommandPausedState::abort(CCommand* command)
{
	command->m_pState = CCommandCompletedState::instance();
}