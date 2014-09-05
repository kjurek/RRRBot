#include <ctype.h>
#include <algorithm>
#include "PressKeyCommand.h"

namespace RRRBot
{
	namespace Commands
	{
		std::shared_ptr<CCommand> CPressKeyCommand::clone()
		{
			auto copy = std::make_shared<CPressKeyCommand>(m_processManager);
			copy->m_nextStep = m_nextStep;
			copy->m_keys = m_keys;
			return copy;
		}

		std::string CPressKeyCommand::name() const
		{
			return "PressKey";
		}

		void CPressKeyCommand::parseInput(std::istream& is)
		{
			std::string input;
			while (std::getline(is, input, '+'))
			{
				input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
				if ( (input.length() == 1 && input[0] >= 'A' && input[0] <= 'Z') ||
					 (input.length() == 1 && input[0] >= '0' && input[0] <= '9') )
				{
					m_keys.push_back(input);
				}
				else
				{					
					throw CCommandException(input + " is not supported yet by PressKeyCommand");
				}				
			}
		}
		
		void CPressKeyCommand::commandStep()
		{
			for (auto& key : m_keys)
			{
				keyToKeyDownMessage(key);
			}

			for (auto& key : m_keys)
			{
				keyToKeyUpMessage(key);
			}
			m_nextStep = false;
		}
		
		bool CPressKeyCommand::hasNextStep()
		{
			return m_nextStep;
		}

		void CPressKeyCommand::keyToKeyDownMessage(const std::string& key)
		{
			if (key.empty())
			{
				return;
			}

			const char VK_0 = 0x30;
			const char VK_A = 0x41;

			if (key[0] >= 'A' && key[0] <= 'Z')
			{
				char keyCode = key[0] - 'A' + VK_A;
				::SendMessage(
					m_processManager.getWindowHandle(),
					WM_KEYDOWN,
					keyCode,
					0
					);
			}
			else if (key[0] >= '0' && key[0] <= '9')
			{
				char keyCode = key[0] - '0' + VK_0;
				::SendMessage(
					m_processManager.getWindowHandle(),
					WM_KEYDOWN,
					keyCode,
					0
					);
			}
		}

		void CPressKeyCommand::keyToKeyUpMessage(const std::string& key)
		{
			if (key.empty())
			{
				return;
			}

			const char VK_0 = 0x30;
			const char VK_A = 0x41;

			if (key[0] >= 'A' && key[0] <= 'Z')
			{
				char keyCode = key[0] - 'A' + VK_A;
				::SendMessage(
					m_processManager.getWindowHandle(),
					WM_KEYUP,
					keyCode,
					0
					);
			}
			else if (key[0] >= '0' && key[0] <= '9')
			{
				char keyCode = key[0] - '0' + VK_0;
				::SendMessage(
					m_processManager.getWindowHandle(),
					WM_KEYUP,
					keyCode,
					0
					);
			}
		}
	}
}