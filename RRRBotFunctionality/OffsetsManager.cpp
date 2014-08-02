#include "OffsetsManager.h"

namespace RRRBot
{
	namespace OffsetManagers
	{
		void COffsetsManager::configure(
			CProcessManager& processManager,
			Offsets::PlayerOffsets& playerOffsets,
			Offsets::MouseOffsets& mouseOffsets
		)
		{
			m_mouseOffsetsManager.configure(&processManager, mouseOffsets);
			m_playerOffsetsManager.configure(&processManager, playerOffsets);
		}
	}
}