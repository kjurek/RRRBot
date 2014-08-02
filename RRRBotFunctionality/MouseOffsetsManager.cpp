#include "MouseOffsetsManager.h"

namespace RRRBot
{
	namespace OffsetManagers
	{
		DWORD CMouseOffsetsManager::xAddr()
		{
			return gameDllAddress + m_pMouseOffsets->x;
		}

		DWORD CMouseOffsetsManager::yAddr()
		{
			return gameDllAddress + m_pMouseOffsets->y;
		}
	}
}
