#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Item.h"

namespace RRRBot
{
	namespace GameData
	{
		struct Inventory
		{
			int maxCapacity;
			std::vector<Item> items;
		};
	}
}

#endif