#include "MouseClickCommand.h"

namespace RRRBot
{
	namespace Commands
	{
		CMouseClickCommand::CMouseClickCommand(
			CProcessManager* processManager, 
			OffsetManagers::COffsetsManager* offsetsManager
		)
			:	m_pProcessManager(processManager),
				m_pOffsetsManager(offsetsManager)
		{ }

		std::string CMouseClickCommand::name() const
		{
			return "MouseClick";
		}

		void CMouseClickCommand::parseInput(std::istream& is)
		{
			if ( (is >> m_x >> m_y).rdstate() & std::ios::failbit )
			{
				throw CCommandException("Invalid input while parsing MouseClickCommand arguments");
			}
		}

		void CMouseClickCommand::commandStep()
		{
			m_pProcessManager->writeMemory(m_pOffsetsManager->m_mouseOffsetsManager.xAddr(), m_x);
			m_pProcessManager->writeMemory(m_pOffsetsManager->m_mouseOffsetsManager.yAddr(), m_y);

			SendMessage(
				m_pProcessManager->getWindowHandle(),
				WM_LBUTTONDBLCLK,
				MK_LBUTTON,
				NULL
				);
			m_nextStep = false;
		}

		bool CMouseClickCommand::hasNextStep()
		{
			return m_nextStep;
		}
	}
}

