#ifndef MOUSEOFFSETSMAPPER_H
#define MOUSEOFFSETSMAPPER_H

#include "MouseOffsets.h"
#include "ProcessManager.h"

namespace RRRBot
{
	namespace OffsetManagers
	{
		class CMouseOffsetsManager
		{
		public:
			CMouseOffsetsManager(CProcessManager* processManager, Offsets::MouseOffsets* mouseOffsets)
				:	m_pProcessManager(processManager),
					m_pMouseOffsets(mouseOffsets)
			{
				gameDllAddress = reinterpret_cast<DWORD>(m_pProcessManager->getModuleAddress("Game.dll"));
			}

			DWORD xAddr();
			DWORD yAddr();
		private:
			CProcessManager* m_pProcessManager;
			Offsets::MouseOffsets* m_pMouseOffsets;
			DWORD gameDllAddress;
		};
	}
}

#endif