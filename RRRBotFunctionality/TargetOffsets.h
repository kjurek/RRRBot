#ifndef TARGETOFFSETS_H
#define TARGETOFFSETS_H

#include <vector>

namespace RRRBot
{
	namespace Offsets
	{
		struct TargetOffsets
		{
			std::vector<unsigned int> base;
			unsigned int hp, maxHp;
			unsigned int name;
		};
	}
}

#endif