#include "OffsetsManager.h"

namespace RRRBot
{
	namespace OffsetManagers
	{
		void COffsetsManager::configure(
			CProcessManager& processManager,
			Offsets::PlayerOffsets& playerOffsets,
			Offsets::MouseOffsets& mouseOffsets,
			Offsets::TargetOffsets& targetOffsets
		)
		{
			m_mouseOffsetsManager.configure(&processManager, mouseOffsets);
			m_playerOffsetsManager.configure(&processManager, playerOffsets);
			m_targetOffsetsManager.configure(&processManager, targetOffsets);
		}
	}
}