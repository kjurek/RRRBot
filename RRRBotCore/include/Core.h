#ifndef CORE_H
#define CORE_H

#include "ICoreApi.h"
#include "CoreConfigurator.h"

namespace RRRBot
{
    namespace Core
    {
        class Core : public ICoreApi
        {
        public:
            Core();
            virtual ~Core() { }

            // Getters
            virtual Common::PlayerInfo getPlayerInfo();
            virtual Common::Inventory getInventory();

            // Actions
            virtual void goToXY(unsigned int x, unsigned int y);
            virtual void mouseClick(unsigned int x, unsigned int y);
            virtual void pressKey(unsigned char virtualKeyCode);
        private:
            Config::CoreConfigurator m_configurator;

            template<class T>
            T readMemory(unsigned int address)
            {
                return *reinterpret_cast<T*>(address);
            }

            template<class T>
            void writeMemory(unsigned int address, T value)
            {
                *reinterpret_cast<T*>(address) = value;
            }

        };
    }
}

#endif
