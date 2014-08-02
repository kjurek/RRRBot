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
			void configure(
				CProcessManager& processManager,
				Offsets::PlayerOffsets& playerOffsets,
				Offsets::MouseOffsets& mouseOffsets
			);

			CPlayerOffsetsManager m_playerOffsetsManager;
			CMouseOffsetsManager m_mouseOffsetsManager;
		};
	}
}

#endif