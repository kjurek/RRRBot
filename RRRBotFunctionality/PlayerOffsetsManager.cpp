#include "PlayerOffsetsManager.h"

namespace RRRBot
{
	namespace OffsetManagers
	{
		DWORD CPlayerOffsetsManager::xAddr()
		{
			return gameDllAddress + m_pPlayerOffsets->x;
		}

		DWORD CPlayerOffsetsManager::yAddr()
		{
			return gameDllAddress + m_pPlayerOffsets->y;
		}

		DWORD CPlayerOffsetsManager::zAddr()
		{
			return gameDllAddress + m_pPlayerOffsets->z;
		}

		DWORD CPlayerOffsetsManager::angleAddr()
		{
			return m_pProcessManager->readMemory<DWORD>(gameDllAddress + m_pPlayerOffsets->angle);
		}

		DWORD CPlayerOffsetsManager::moveAddr()
		{
			return m_pProcessManager->readMemory<DWORD>(m_pPlayerOffsets->base + m_pPlayerOffsets->move[0]) + m_pPlayerOffsets->move[1];
		}
	}
}