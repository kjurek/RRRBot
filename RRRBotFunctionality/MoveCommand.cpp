#include <ctype.h>
#include "MoveCommand.h"
#include "ProcessManager.h"

namespace RRRBot
{
	namespace Commands
	{
		std::shared_ptr<CCommand> CMoveCommand::clone()
		{
			auto copy = std::make_shared<CMoveCommand>(m_processManager, m_core);
			copy->m_nextStep = m_nextStep;
			copy->m_dest_x = m_dest_x;
			copy->m_dest_y = m_dest_y;
			copy->m_dest_z = m_dest_z;
			return copy;
		}

		std::string CMoveCommand::name() const
		{
			return "Move";
		}

		void CMoveCommand::parseInput(std::istream& is)
		{
			std::string x;
			std::string y;
			if ((is >> m_dest_x >> m_dest_y >> m_dest_z).rdstate() & std::ios::failbit)
			{
				throw CCommandException("Invalid input while parsing MoveCommand arguments");
			}
		}

		bool CMoveCommand::hasNextStep()
		{
			return m_nextStep;
		}

		void CMoveCommand::commandStep()
		{
			static const float tolerance = 5.0f;
			static const float RAD_TO_DEG = 57.295f;
			static auto pom = m_core.m_offsetManager.m_playerOffsetsManager;
			m_core.getCommand("UpdatePlayerInfo")->execute();
			auto info = m_core.getPlayer();
			float dx = m_dest_x - info.x;
			float dy = m_dest_y - info.y;
			float dz = m_dest_z - info.z;
			float distance = std::sqrt(dx*dx + dy*dy + dz*dz);

			if ( distance < tolerance )
			{
				m_processManager.writeMemory<char>(
					m_core.m_offsetManager.m_playerOffsetsManager.moveAddr(),
					0
				);
				m_nextStep = false;
				return;
			}

			float horizontalAngle = ::atan(dy / dx) * RAD_TO_DEG;
			float verticalAngle = ::atan(dz / std::sqrt(dx*dx + dy*dy)) * RAD_TO_DEG;

			if (dx < 0) {
				horizontalAngle = -horizontalAngle;
			}
			else {
				horizontalAngle = 180 - horizontalAngle;
			}

			if ( ((dz < 0) && (verticalAngle < 0)) || ((dz > 0) && (verticalAngle > 0)) )
			{
				verticalAngle = -verticalAngle;
			}
			
			m_processManager.writeMemory<float>(
				m_core.m_offsetManager.m_playerOffsetsManager.rotHAddr(),
				horizontalAngle
				);

			m_processManager.writeMemory<float>(
				m_core.m_offsetManager.m_playerOffsetsManager.rotVAddr(),
				verticalAngle
				);
			
			m_processManager.writeMemory<char>(
				m_core.m_offsetManager.m_playerOffsetsManager.moveAddr(),
				7
				);

			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
}