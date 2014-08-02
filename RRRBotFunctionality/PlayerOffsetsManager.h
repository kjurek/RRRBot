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
			void configure(CProcessManager* processManager, Offsets::PlayerOffsets& playerOffsets);
			void setPlayerOffsets(Offsets::PlayerOffsets& playerOffsets) { m_playerOffsets = playerOffsets; }
			Offsets::PlayerOffsets getPlayerOffsets() const { return m_playerOffsets; }
			
			DWORD xAddr();
			DWORD yAddr();
			DWORD zAddr();
			DWORD angleAddr();
			DWORD moveAddr();
		private:
			CProcessManager* m_pProcessManager;
			Offsets::PlayerOffsets m_playerOffsets;
			DWORD gameDllAddress;
		};
	}
}

#endif