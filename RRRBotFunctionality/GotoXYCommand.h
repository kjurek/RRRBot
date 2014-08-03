#ifndef GOTOXYCOMMAND_H
#define GOTOXYCOMMAND_H

#include "Command.h"
#include "ProcessManager.h"
#include "Core.h"

namespace RRRBot
{
	namespace Commands
	{
		using namespace RRRBot::Core;
		class CGotoXYCommand : public CCommand
		{
		public:
			CGotoXYCommand(CProcessManager& processManager, CCore& core)
				: m_processManager(processManager),
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
			CCore& m_core;
			bool m_nextStep;
			float m_dest_x;
			float m_dest_y;
		};
	}
}
#endif