#include <ctype.h>
#include "GotoXYCommand.h"
#include "ProcessManager.h"

namespace RRRBot
{
	namespace Commands
	{
		std::shared_ptr<CCommand> CGotoXYCommand::clone()
		{
			auto copy = std::make_shared<CGotoXYCommand>(m_processManager, m_core);
			copy->m_nextStep = m_nextStep;
			copy->m_dest_x = m_dest_x;
			copy->m_dest_y = m_dest_y;
			return copy;
		}

		std::string CGotoXYCommand::name() const
		{
			return "GotoXY";
		}

		void CGotoXYCommand::parseInput(std::istream& is)
		{
			std::string x;
			std::string y;
			if ((is >> x >> y).rdstate() & std::ios::failbit)
			{
				throw CCommandException("Invalid input while parsing PressKeyCommand arguments");
			}

			m_dest_x = ::atof(x.c_str());
			m_dest_y = ::atof(y.c_str());
		}

		bool CGotoXYCommand::hasNextStep()
		{
			return m_nextStep;
		}

		void CGotoXYCommand::commandStep()
		{
			static const float tolerance = 5.0f;
			static auto pom = m_core.m_offsetManager.m_playerOffsetsManager;
			auto c = m_core.getCommand("UpdatePlayerInfo");
			c->execute();
			auto info = m_core.getPlayer();
			float dx = m_dest_x - info.x;
			float dy = m_dest_y - info.y;

			if (::abs(dx) < tolerance && ::abs(dy) < tolerance)
			{
				m_processManager.writeMemory<char>(
					m_core.m_offsetManager.m_playerOffsetsManager.moveAddr(),
					0
				);
				m_nextStep = false;
				return;
			}

			float th = ::atan(dy / dx) * 57.295f; // hax?

			if (dx < 0) {
				th = -th;
			}
			else {
				th = 180 - th;
			}
			m_processManager.writeMemory<float>(
				m_core.m_offsetManager.m_playerOffsetsManager.angleAddr(),
				th
				);

			m_processManager.writeMemory<char>(
				m_core.m_offsetManager.m_playerOffsetsManager.moveAddr(),
				7
				);

			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
}