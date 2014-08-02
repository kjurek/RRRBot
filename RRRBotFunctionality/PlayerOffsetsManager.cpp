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

		DWORD CPlayerOffsetsManager::angleAddr()
		{
			return m_pProcessManager->readMemory<DWORD>(gameDllAddress + m_playerOffsets.angle);
		}

		DWORD CPlayerOffsetsManager::moveAddr()
		{
			return m_pProcessManager->readMemory<DWORD>(m_playerOffsets.base + m_playerOffsets.move[0]) + m_playerOffsets.move[1];
		}
	}
}