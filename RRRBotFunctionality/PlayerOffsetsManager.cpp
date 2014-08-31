#include "PlayerOffsetsManager.h"

namespace RRRBot
{
	namespace OffsetManagers
	{
		void CPlayerOffsetsManager::configure(CProcessManager* processManager, Offsets::PlayerOffsets& playerOffsets)
		{
			m_pProcessManager = processManager;
			m_playerOffsets = playerOffsets;
			gameDllAddress = reinterpret_cast<DWORD>(m_pProcessManager->getModuleAddress("Game.dll"));
		}

		DWORD CPlayerOffsetsManager::baseAddr()
		{
			DWORD addr = gameDllAddress;
			for (auto offset : m_playerOffsets.base)
			{
				addr = m_pProcessManager->readMemory<DWORD>(addr + offset);
			}
			return addr;			
		}

		DWORD CPlayerOffsetsManager::xAddr()
		{
			return gameDllAddress + m_playerOffsets.x;
		}

		DWORD CPlayerOffsetsManager::yAddr()
		{
			return gameDllAddress + m_playerOffsets.y;
		}

		DWORD CPlayerOffsetsManager::zAddr()
		{
			return gameDllAddress + m_playerOffsets.z;
		}

		DWORD CPlayerOffsetsManager::flightTimeAddr()
		{
			return gameDllAddress + m_playerOffsets.flightTime;
		}

		DWORD CPlayerOffsetsManager::maxFlightTimeAddr()
		{
			return gameDllAddress + m_playerOffsets.maxFlightTime;
		}

		DWORD CPlayerOffsetsManager::nameAddr()
		{
			return baseAddr() + m_playerOffsets.name;
		}

		DWORD CPlayerOffsetsManager::hpAddr()
		{
			return gameDllAddress + m_playerOffsets.hp;
		}

		DWORD CPlayerOffsetsManager::maxHpAddr()
		{
			return gameDllAddress + m_playerOffsets.maxHp;
		}

		DWORD CPlayerOffsetsManager::mpAddr()
		{
			return gameDllAddress + m_playerOffsets.mp;
		}

		DWORD CPlayerOffsetsManager::maxMpAddr()
		{
			return gameDllAddress + m_playerOffsets.maxMp;
		}

		DWORD CPlayerOffsetsManager::rotHAddr()
		{
			return gameDllAddress + m_playerOffsets.rotH;
		}

		DWORD CPlayerOffsetsManager::rotVAddr()
		{
			return gameDllAddress + m_playerOffsets.rotV;
		}

		DWORD CPlayerOffsetsManager::moveAddr()
		{
			return baseAddr() + m_playerOffsets.move;
		}
	}
}