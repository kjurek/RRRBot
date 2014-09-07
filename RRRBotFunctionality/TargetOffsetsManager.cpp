#include "TargetOffsetsManager.h"

namespace RRRBot
{
	namespace OffsetManagers
	{
		void CTargetOffsetsManager::configure(CProcessManager* processManager, Offsets::TargetOffsets& targetOffsets)
		{
			m_pProcessManager = processManager;
			m_targetOffsets = targetOffsets;
			m_gameDllAddress = reinterpret_cast<DWORD>(m_pProcessManager->getModuleAddress("Game.dll"));
		}

		DWORD CTargetOffsetsManager::baseAddr()
		{
			return m_pProcessManager->readMemory<DWORD>(
				m_pProcessManager->readMemory<DWORD>(m_gameDllAddress + m_targetOffsets.base[0]) +
				m_targetOffsets.base[1]);
		}

		DWORD CTargetOffsetsManager::hasTargetAddr()
		{
			return m_gameDllAddress + m_targetOffsets.base[0] + 8;
		}

		DWORD CTargetOffsetsManager::nameAddr()
		{
			return baseAddr() + m_targetOffsets.name;
		}

		DWORD CTargetOffsetsManager::hpAddr()
		{
			return baseAddr() + m_targetOffsets.hp;
		}

		DWORD CTargetOffsetsManager::maxHpAddr()
		{
			return baseAddr() + m_targetOffsets.maxHp;
		}
	}
}
