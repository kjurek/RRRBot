#ifndef PLAYEROFFSETS_H
#define PLAYEROFFSETS_H

#include <vector>

namespace RRRBot
{
	namespace Offsets
	{
		struct PlayerOffsets
		{
			std::vector<unsigned int> base;
			unsigned int x, y, z;
			unsigned int flightTime, maxFlightTime;
			unsigned int hp, maxHp;
			unsigned int mp, maxMp;
			unsigned int rotH, rotV;
			unsigned int move;
			unsigned int name;
		};
	}
}

#endif