#include <thread>
#include "PlayerOffsetsManager.h"

namespace RRRBot
{
	namespace OffsetManagers
	{
		void CPlayerOffsetsManager::configure(CProcessManager* processManager, Offsets::PlayerOffsets& playerOffsets)
		{
			m_pProcessManager = processManager;
			m_playerOffsets = playerOffsets;
			m_gameDllAddress = reinterpret_cast<DWORD>(m_pProcessManager->getModuleAddress("Game.dll"));
		}

		bool CPlayerOffsetsManager::isBaseAddressValid(DWORD baseAddress) const
		{
			return m_pProcessManager->readMemory<DWORD>(
				m_pProcessManager->readMemory<DWORD>(baseAddress + 4) +
				0x254) == baseAddress;
		}

		DWORD CPlayerOffsetsManager::baseAddr()
		{
			DWORD base = m_gameDllAddress;

			for (auto& offset : m_playerOffsets.base)
			{
				base = m_pProcessManager->readMemory<DWORD>(base + offset);
			}
			
			if (!isBaseAddressValid(base))
			{
				throw "Could not init base address";
			}
			return base;
		}

		DWORD CPlayerOffsetsManager::xAddr()
		{
			return m_gameDllAddress + m_playerOffsets.x;
		}

		DWORD CPlayerOffsetsManager::yAddr()
		{
			return m_gameDllAddress + m_playerOffsets.y;
		}

		DWORD CPlayerOffsetsManager::zAddr()
		{
			return m_gameDllAddress + m_playerOffsets.z;
		}

		DWORD CPlayerOffsetsManager::flightTimeAddr()
		{
			return m_gameDllAddress + m_playerOffsets.flightTime;
		}

		DWORD CPlayerOffsetsManager::maxFlightTimeAddr()
		{
			return m_gameDllAddress + m_playerOffsets.maxFlightTime;
		}

		DWORD CPlayerOffsetsManager::nameAddr()
		{
			return baseAddr() + m_playerOffsets.name;
		}

		DWORD CPlayerOffsetsManager::hpAddr()
		{
			return m_gameDllAddress + m_playerOffsets.hp;
		}

		DWORD CPlayerOffsetsManager::maxHpAddr()
		{
			return m_gameDllAddress + m_playerOffsets.maxHp;
		}

		DWORD CPlayerOffsetsManager::mpAddr()
		{
			return m_gameDllAddress + m_playerOffsets.mp;
		}

		DWORD CPlayerOffsetsManager::maxMpAddr()
		{
			return m_gameDllAddress + m_playerOffsets.maxMp;
		}

		DWORD CPlayerOffsetsManager::rotHAddr()
		{
			return m_gameDllAddress + m_playerOffsets.rotH;
		}

		DWORD CPlayerOffsetsManager::rotVAddr()
		{
			return m_gameDllAddress + m_playerOffsets.rotV;
		}

		DWORD CPlayerOffsetsManager::moveAddr()
		{
			return baseAddr() + m_playerOffsets.move;
		}
	}
}