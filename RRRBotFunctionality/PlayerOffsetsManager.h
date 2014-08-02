#ifndef PLAYEROFFSETSMAPPER_H
#define PLAYEROFFSETSMAPPER_H

#include "PlayerOffsets.h"
#include "ProcessManager.h"

namespace RRRBot
{
	namespace OffsetManagers
	{
		class CPlayerOffsetsManager
		{
		public:
			CPlayerOffsetsManager(CProcessManager* processManager, Offsets::PlayerOffsets* playerOffsets) 
				:	m_pProcessManager(processManager),
					m_pPlayerOffsets(playerOffsets)
			{
				gameDllAddress = reinterpret_cast<DWORD>(m_pProcessManager->getModuleAddress("Game.dll"));
			}
			
			DWORD xAddr();
			DWORD yAddr();
			DWORD zAddr();
			DWORD angleAddr();
			DWORD moveAddr();
		private:
			CProcessManager* m_pProcessManager;
			Offsets::PlayerOffsets* m_pPlayerOffsets;
			DWORD gameDllAddress;
		};
	}
}

#endif