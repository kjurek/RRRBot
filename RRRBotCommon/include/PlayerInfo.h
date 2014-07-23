#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <vector>

namespace RRRBot
{
    namespace Common
    {
        struct PlayerInfo
        {
            float x, y, z, angle;
            unsigned int hp, mp, maxHp, maxMp;
        };

        struct Item
        {
            unsigned int id, count;
        };

        struct Inventory
        {
            std::vector<Item> items;
            unsigned int currentCapacity, maxCapacity;
        };
    }
}

#endif // PLAYERINFO_H
