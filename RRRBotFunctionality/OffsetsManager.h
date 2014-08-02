#ifndef OFFSETSMANAGER_H
#define OFFSETSMANAGER_H

#include "ProcessManager.h"
#include "MouseOffsetsManager.h"
#include "PlayerOffsetsManager.h"

namespace RRRBot
{
	namespace OffsetManagers
	{
		class COffsetsManager
		{
		public:
			COffsetsManager(
				CProcessManager* processManager,
				Offsets::PlayerOffsets* playerOffsets,
				Offsets::MouseOffsets* mouseOffsets
			)
				:	m_playerOffsetsManager(processManager, playerOffsets),
					m_mouseOffsetsManager(processManager, mouseOffsets)
			{ }

			CPlayerOffsetsManager m_playerOffsetsManager;
			CMouseOffsetsManager m_mouseOffsetsManager;
		};
	}
}

#endif