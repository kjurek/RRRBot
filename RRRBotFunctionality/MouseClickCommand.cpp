#include "MouseClickCommand.h"

namespace RRRBot
{
	namespace Commands
	{
		std::shared_ptr<CCommand> CMouseClickCommand::clone()
		{
			auto copy = std::make_shared<CMouseClickCommand>(m_processManager, m_core);
			copy->m_nextStep = m_nextStep;
			copy->m_x = m_x;
			copy->m_y = m_y;
			return copy;
		}

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
			m_processManager.writeMemory(m_core.m_offsetManager.m_mouseOffsetsManager.xAddr(), m_x);
			m_processManager.writeMemory(m_core.m_offsetManager.m_mouseOffsetsManager.yAddr(), m_y);

			SendMessage(
				m_processManager.getWindowHandle(),
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

