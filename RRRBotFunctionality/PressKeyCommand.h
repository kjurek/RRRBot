#ifndef PRESSKEYCOMMAND_H
#define PRESSKEYCOMMAND_H

#include <vector>
#include "Command.h"
#include "ProcessManager.h"

namespace RRRBot
{
	namespace Commands
	{
		class CPressKeyCommand : public CCommand
		{
		public:
			CPressKeyCommand(CProcessManager& processManager)
				:	m_processManager(processManager),
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
			std::vector<std::string> m_keys;

			void keyToKeyDownMessage(const std::string& key);
			void keyToKeyUpMessage(const std::string& key);
		};
	}
}

#endif