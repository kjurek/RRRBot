#include <ctype.h>
#include "PressKeyCommand.h"

namespace RRRBot
{
	namespace Commands
	{
		std::string CPressKeyCommand::name() const
		{
			return "PressKey";
		}

		void CPressKeyCommand::parseInput(std::istream& is)
		{
			if ( (is >> m_key).rdstate() & std::ios::failbit )
			{
				throw CCommandException("Invalid input while parsing PressKeyCommand arguments");
			}

			m_key = tolower(m_key);

			if (m_key >= '0' && m_key <= '9')
			{
				// convert number to virtual key
				m_key = m_key - '0' + 0x30;
			}
			else if (m_key >= 'a' && m_key <= 'z')
			{
				m_key = m_key - 'a' + 0x41;
			}
			else
			{
				throw CCommandException(m_key + " is not supported yet by PressKeyCommand");
			}
		}
		
		void CPressKeyCommand::commandStep()
		{
			SendMessage(
				m_pProcessManager->getWindowHandle(),
				WM_KEYDOWN,
				m_key,
				1
			);
			m_nextStep = false;
		}
		
		bool CPressKeyCommand::hasNextStep()
		{
			return m_nextStep;
		}
	}
}