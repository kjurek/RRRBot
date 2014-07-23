#ifndef ICOREAPI_H
#define ICOREAPI_H

#include <playerinfo.h>

namespace RRRBot
{
    namespace Core
    {
        class ICoreApi
        {
        public:
            // Getters
            virtual Common::PlayerInfo getPlayerInfo() = 0;
            virtual Common::Inventory getInventory() = 0;

            // Actions
            virtual void goToXY(unsigned int x, unsigned int y) = 0;
            virtual void mouseClick(unsigned int x, unsigned int t) = 0;
            virtual void pressKey(unsigned char virtualKeyCode) = 0;
        };
    }
}



#endif // ICOREAPI_H
