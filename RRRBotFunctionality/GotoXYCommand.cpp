#include <ctype.h>
#include "GotoXYCommand.h"

namespace RRRBot
{
	namespace Commands
	{
		std::shared_ptr<CCommand> CGotoXYCommand::clone()
		{
			auto copy = std::make_shared<CGotoXYCommand>(m_processManager);
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

		void CGotoXYCommand::commandStep()
		{
			static const float tolerance = 5.0f;
			while (1)
			{
				auto info = getPlayerInfo();
				float dx = m_dest_x - info.x;
				float dy = m_dest_y - info.y;

				if (::abs(dx) < tolerance && ::abs(dy) < tolerance)
				{
					break;
				}

				float th = ::atan(dy / dx) * 57.295f; // hax?

				if (dx < 0) {
					th = -th;
				}
				else {
					th = 180 - th;
				}

			}
		}
	}
}