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
			int hp, mp, maxHp, maxMp;
			float x, y, z, rotation;
			std::string name;
			Inventory inventory;
		};
	}
}

#endif