#include "Command.h"
#include "CommandState.h"
#include "CommandCompletedState.h"
#include "CommandRunningState.h"

CCommand::CCommand()
	:	m_completed(false),
		m_pState(nullptr)
{

}

CCommand::~CCommand()
{
	m_pState = CCommandCompletedState::instance();
}

void CCommand::execute()
{
	m_pState = CCommandRunningState::instance();
	while (!isCompleted())
	{
		m_pState->step(this);
	}
}

bool operator==(const CCommand& a, const CCommand& b)
{
	return a.name() == b.name();
}

bool operator<(const CCommand& a, const CCommand& b)
{
	return a.name() < b.name();
}

void CCommand::pause()
{
	m_pState->pause(this);
}

void CCommand::resume()
{
	m_pState->resume(this);
}

void CCommand::abort()
{
	m_pState->abort(this);
}