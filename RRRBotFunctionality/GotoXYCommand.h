#ifndef GOTOXYCOMMAND_H
#define GOTOXYCOMMAND_H

#include "Command.h"
#include "ProcessManager.h"

namespace RRRBot
{
	namespace Commands
	{
		class CGotoXYCommand : public CCommand
		{
		public:
			CGotoXYCommand(CProcessManager& processManager)
				: m_processManager(processManager),
				m_nextStep(true)
			{ }
			virtual std::shared_ptr<CCommand> clone();
			virtual std::string name() const;
			virtual void parseInput(std::istream& is);
			virtual void commandStep();
			virtual bool hasNextStep();
		private:
			CProcessManager& m_processManager;
			bool m_nextStep;
			float m_dest_x;
			float m_dest_y;
		};
	}
}
#endif