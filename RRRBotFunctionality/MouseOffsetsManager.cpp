#include "MouseOffsetsManager.h"

namespace RRRBot
{
	namespace OffsetManagers
	{
		void CMouseOffsetsManager::configure(CProcessManager* processManager, Offsets::MouseOffsets& mouseOffsets)
		{
			m_pProcessManager = processManager;
			m_mouseOffsets = mouseOffsets;
			gameDllAddress = reinterpret_cast<DWORD>(m_pProcessManager->getModuleAddress("Game.dll"));
		}

		DWORD CMouseOffsetsManager::xAddr()
		{
			return gameDllAddress + m_mouseOffsets.x;
		}

		DWORD CMouseOffsetsManager::yAddr()
		{
			return gameDllAddress + m_mouseOffsets.y;
		}
	}
}
