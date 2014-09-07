#ifndef TARGETOFFSETSMAPPER_H
#define TARGETOFFSETSMAPPER_H

#include "TargetOffsets.h"
#include "ProcessManager.h"

namespace RRRBot
{
	namespace OffsetManagers
	{
		class CTargetOffsetsManager
		{
		public:
			void configure(CProcessManager* processManager, Offsets::TargetOffsets& targetOffsets);
			void setPlayerOffsets(Offsets::TargetOffsets& targetOffsets) { m_targetOffsets = targetOffsets; }
			Offsets::TargetOffsets getTargetOffsets() const { return m_targetOffsets; }

			DWORD baseAddr();
			DWORD hasTargetAddr();
			DWORD nameAddr();
			DWORD hpAddr();
			DWORD maxHpAddr();
		private:
			CProcessManager* m_pProcessManager;
			Offsets::TargetOffsets m_targetOffsets;
			DWORD m_gameDllAddress;
		};
	}
}

#endif