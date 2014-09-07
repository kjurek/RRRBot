#ifndef TARGET_H
#define TARGET_H

#include <string>

namespace RRRBot
{
	namespace GameData
	{
		struct Target
		{
			int hp, maxHp;
			std::wstring name;
			bool exists;
		};
	}
}

#endif