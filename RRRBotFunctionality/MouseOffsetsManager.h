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
			void configure(CProcessManager* processManager, Offsets::MouseOffsets& mouseOffsets);
			void setMouseOffsets(Offsets::MouseOffsets& mouseOffsets) { m_mouseOffsets = mouseOffsets; }
			Offsets::MouseOffsets getMouseOffsets() const { return m_mouseOffsets; }

			DWORD xAddr();
			DWORD yAddr();
		private:
			CProcessManager* m_pProcessManager;
			Offsets::MouseOffsets m_mouseOffsets;
			DWORD gameDllAddress;
		};
	}
}

#endif