#ifndef OFFSETSMANAGER_H
#define OFFSETSMANAGER_H

#include "ProcessManager.h"
#include "MouseOffsetsManager.h"
#include "PlayerOffsetsManager.h"
#include "TargetOffsetsManager.h"

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
				Offsets::MouseOffsets& mouseOffsets,
				Offsets::TargetOffsets& targetOffsets
			);

			CPlayerOffsetsManager m_playerOffsetsManager;
			CMouseOffsetsManager m_mouseOffsetsManager;
			CTargetOffsetsManager m_targetOffsetsManager;
		};
	}
}

#endif