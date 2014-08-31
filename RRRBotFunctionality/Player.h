#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Inventory.h"

namespace RRRBot
{
	namespace GameData
	{
		struct Player
		{
			int hp, mp, maxHp, maxMp, flightTime, maxFlightTime;
			float x, y, z, rotH, rotV;
			std::wstring name;
			Inventory inventory;
		};
	}
}

#endif