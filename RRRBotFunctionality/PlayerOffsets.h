#ifndef PLAYEROFFSETS_H
#define PLAYEROFFSETS_H

#include <vector>

namespace RRRBot
{
	namespace Offsets
	{
		struct PlayerOffsets
		{
			std::vector<int> base;
			int x, y, z;
			int flightTime, maxFlightTime;
			int hp, maxHp;
			int mp, maxMp;
			int rotH, rotV;
			int move;
			int name;
		};
	}
}

#endif