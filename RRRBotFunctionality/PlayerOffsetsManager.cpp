#include <thread>
#include "PlayerOffsetsManager.h"

namespace RRRBot
{
	namespace OffsetManagers
	{
		CPlayerOffsetsManager::CPlayerOffsetsManager()
			:
			m_gameDllAddress(0),
			m_baseAddress(0),
			m_pProcessManager(nullptr),
			m_playerOffsets({ 0 })
		{ }

		void CPlayerOffsetsManager::configure(CProcessManager* processManager, Offsets::PlayerOffsets& playerOffsets)
		{
			m_pProcessManager = processManager;
			m_playerOffsets = playerOffsets;
			m_gameDllAddress = reinterpret_cast<DWORD>(m_pProcessManager->getModuleAddress("Game.dll"));
			initBaseAddress();
		}

		bool CPlayerOffsetsManager::isBaseAddressValid() const
		{
			if (0 == m_baseAddress)
			{
				return false;
			}

			return m_pProcessManager->readMemory<DWORD>(m_baseAddress + 4) != INVALID_BASE;
		}

		void CPlayerOffsetsManager::initBaseAddress()
		{
			int numberOfTriesLeft = 10;
			while (numberOfTriesLeft--)
			{
				m_baseAddress = m_pProcessManager->readMemory<DWORD>(m_playerOffsets.base);
				if (isBaseAddressValid())
				{
					return;
				}
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}	
			throw "Could not init player base address after 10 tries";
		}

		DWORD CPlayerOffsetsManager::baseAddr()
		{
			if (!isBaseAddressValid())
			{
				initBaseAddress();
			}
			return m_baseAddress;
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