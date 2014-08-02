#ifndef MOUSECLICKCOMMAND_H
#define MOUSECLICKCOMMAND_H

#include "Command.h"
#include "ProcessManager.h"
#include "OffsetsManager.h"

namespace RRRBot
{
	namespace Commands
	{
		class CMouseClickCommand : public CCommand
		{
		public:
			CMouseClickCommand(
				CProcessManager* processManager,
				OffsetManagers::COffsetsManager* offsetsManager
			);

			virtual std::string name() const;
			virtual void parseInput(std::istream& is);
			virtual void commandStep();
			virtual bool hasNextStep();
		private:
			CProcessManager* m_pProcessManager;
			OffsetManagers::COffsetsManager* m_pOffsetsManager;
			int m_x, m_y;
			bool m_nextStep;
		};
	}
}

#endif