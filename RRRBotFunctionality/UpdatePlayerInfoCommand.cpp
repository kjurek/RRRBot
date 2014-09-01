#include "UpdatePlayerInfoCommand.h"

namespace RRRBot
{
	namespace Commands
	{
		std::shared_ptr<CCommand> CUpdatePlayerInfoCommand::clone()
		{
			auto copy = std::make_shared<CUpdatePlayerInfoCommand>(m_processManager, m_core);
			copy->m_nextStep = m_nextStep;
			return copy;
		}

		std::string CUpdatePlayerInfoCommand::name() const
		{
			return "UpdatePlayerInfo";
		}

		void CUpdatePlayerInfoCommand::parseInput(std::istream& is)
		{
			// nothing to parse
		}

		void CUpdatePlayerInfoCommand::commandStep()
		{
			RRRBot::GameData::Player player;
			auto& playerOffsetManager = m_core.m_offsetManager.m_playerOffsetsManager;

			player.x = m_processManager.readMemory<float>(playerOffsetManager.xAddr());
			player.y = m_processManager.readMemory<float>(playerOffsetManager.yAddr());
			player.z = m_processManager.readMemory<float>(playerOffsetManager.zAddr());
			player.hp = m_processManager.readMemory<int>(playerOffsetManager.hpAddr());
			player.maxHp = m_processManager.readMemory<int>(playerOffsetManager.maxHpAddr());
			player.mp = m_processManager.readMemory<int>(playerOffsetManager.mpAddr());
			player.maxMp = m_processManager.readMemory<int>(playerOffsetManager.maxMpAddr());
			player.flightTime = m_processManager.readMemory<int>(playerOffsetManager.flightTimeAddr());
			player.maxFlightTime = m_processManager.readMemory<int>(playerOffsetManager.maxFlightTimeAddr());
			player.rotH = m_processManager.readMemory<float>(playerOffsetManager.rotHAddr());
			player.rotV = m_processManager.readMemory<float>(playerOffsetManager.rotVAddr());
			player.name = m_processManager.readWString(playerOffsetManager.nameAddr(), 20);
			m_core.setPlayer(player);
			m_nextStep = false;
		}

		bool CUpdatePlayerInfoCommand::hasNextStep()
		{
			return m_nextStep;
		}
	}
}

