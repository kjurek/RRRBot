#ifndef UPDATEPLAYERINFOCOMMAND_H
#define UPDATEPLAYERINFOCOMMAND_H

#include "Command.h"
#include "ProcessManager.h"
#include "Core.h"

namespace RRRBot
{
	namespace Commands
	{
		class CUpdatePlayerInfoCommand : public CCommand
		{
		public:
			CUpdatePlayerInfoCommand(
				CProcessManager& processManager,
				RRRBot::Core::CCore& core
			)
				:	m_processManager(processManager),
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
			bool m_nextStep;
		};
	}
}

#endif