#ifndef PRESSKEYCOMMAND_H
#define PRESSKEYCOMMAND_H

#include "Command.h"
#include "ProcessManager.h"

namespace RRRBot
{
	namespace Commands
	{
		class CPressKeyCommand : public CCommand
		{
		public:
			CPressKeyCommand(CProcessManager* processManager)
				:	m_pProcessManager(processManager),
					m_nextStep(true)
			{ }

			virtual std::string name() const;
			virtual void parseInput(std::istream& is);
			virtual void commandStep();
			virtual bool hasNextStep();
		private:
			CProcessManager* m_pProcessManager;
			bool m_nextStep;
			char m_key;
		};
	}
}

#endif