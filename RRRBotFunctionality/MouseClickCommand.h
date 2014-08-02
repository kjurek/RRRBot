#ifndef MOUSECLICKCOMMAND_H
#define MOUSECLICKCOMMAND_H

#include "Command.h"
#include "ProcessManager.h"
#include "Core.h"

namespace RRRBot
{
	namespace Commands
	{
		class CMouseClickCommand : public CCommand
		{
		public:
			CMouseClickCommand(
				CProcessManager& processManager,
				RRRBot::Core::CCore& core
			)	:	m_processManager(processManager),
					m_core(core),
					m_nextStep(true)
			{ }

			virtual std::shared_ptr<CCommand> clone();
			virtual std::string name() const;
			virtual void parseInput(std::istream& is);
			virtual void commandStep();
			virtual bool hasNextStep();
		private:
			CProcessManager& m_processManager;
			RRRBot::Core::CCore& m_core;
			int m_x, m_y;
			bool m_nextStep;
		};
	}
}

#endif