#ifndef PLAYEROFFSETS_H
#define PLAYEROFFSETS_H

#include <vector>

namespace RRRBot
{
	namespace Offsets
	{
		struct PlayerOffsets
		{
			int base;
			int x, y, z;
			int rotH, rotV;
			std::vector<int> move;
		};
	}
}

#endif