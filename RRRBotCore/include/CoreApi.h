#ifndef COREAPI_H
#define COREAPI_H_

#include <vector>

namespace RRRBot
{
	namespace Core
	{
		struct PlayerInfo
		{
			int hp;
			float x, y, z;
			float rotAngle;
		};

		struct Coords
		{
			int x, y;
		};

		struct Item
		{
			int id;
			int count;
		};

		struct Inventory
		{
			std::vector<Item> items;
			int maxCapacity;
		};

		class CoreApi
		{
		public:
			virtual PlayerInfo GetPlayerInfo() = 0;
			virtual Inventory GetInventory() = 0;
			virtual void GoToXY(Coords coords) = 0;
			virtual void MouseClick(Coords coords) = 0;
			virtual void PressKey(unsigned int virtualKeyCode) = 0;
		};
	}
}

#endif