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
			CPlayerOffsetsManager();

			void configure(CProcessManager* processManager, Offsets::PlayerOffsets& playerOffsets);
			void setPlayerOffsets(Offsets::PlayerOffsets& playerOffsets) { m_playerOffsets = playerOffsets; }
			Offsets::PlayerOffsets getPlayerOffsets() const { return m_playerOffsets; }
			
			DWORD baseAddr();
			DWORD xAddr();
			DWORD yAddr();
			DWORD zAddr();
			DWORD flightTimeAddr();
			DWORD maxFlightTimeAddr();
			DWORD nameAddr();
			DWORD hpAddr();
			DWORD maxHpAddr();
			DWORD mpAddr();
			DWORD maxMpAddr();
			DWORD rotHAddr();
			DWORD rotVAddr();
			DWORD moveAddr();
		private:
			CProcessManager* m_pProcessManager;
			Offsets::PlayerOffsets m_playerOffsets;
			DWORD m_gameDllAddress;
			DWORD m_baseAddress;

			void initBaseAddress();
			bool isBaseAddressValid() const;
			static const DWORD INVALID_BASE = 0xCDCDCDCD;
		};
	}
}

#endif