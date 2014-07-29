#ifndef CORE_H
#define CORE_H


//#include "core_api.pb.h"
#include <vector>
#include "CoreApi.h"
#include "CoreConfigurator.h"

namespace RRRBot
{
	namespace Core
	{
		class Core : public CoreApi
		{
		public:
			virtual PlayerInfo GetPlayerInfo();
			virtual Inventory GetInventory();
			virtual void GoToXY(Coords coords);
			virtual void MouseClick(Coords coords);
			virtual void PressKey(unsigned int virtualKeyCode);

			Config::CoreConfigurator& getConfigurator() { return m_configurator; }
		private:

			Config::CoreConfigurator m_configurator;

			template<typename T, typename... Args>
			T readMemory(int base, int offset, Args... args)
			{
				if (sizeof...(args) == 0)
				{
					return readMemory<T>(base + offset);
				}
				else
				{
					return readMemory<T>(readMemory<int>(base + offset), args...);
				}
			}

			template<typename T>
			T readMemory(int addr)
			{
				return *reinterpret_cast<T*>(addr);
			}

			template<typename T>
			void writeMemory(T value, int address)
			{
				*reinterpret_cast<T*>(address) = value;
			}
		};
	}
}

#endif
