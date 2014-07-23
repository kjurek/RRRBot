#include <cmath>
#include "Core.h"
#include "stdafx.h"

namespace RRRBot
{
    namespace Core
    {
        // Getters
        Common::PlayerInfo Core::getPlayerInfo()
        {
            Common::PlayerInfo playerInfo;
            unsigned int baseAddress = m_configurator.getOffsets().m_baseAddress;
            playerInfo.x = readMemory<float>(baseAddress + m_configurator.getOffsets().m_player.x);
            playerInfo.y = readMemory<float>(baseAddress + m_configurator.getOffsets().m_player.y);
            playerInfo.z = readMemory<float>(baseAddress + m_configurator.getOffsets().m_player.z);
            // pointer to pointer :p fucking inception
            playerInfo.angle =
                    readMemory<float>(readMemory<unsigned int>(baseAddress + m_configurator.getOffsets().m_player.angle));
            return playerInfo;
        }

        Common::Inventory Core::getInventory()
        {
            Common::Inventory inventory;
            // todo
            return inventory;
        }

        // Actions
        void Core::goToXY(unsigned int x, unsigned int y)
        {

        }

        void Core::mouseClick(unsigned int x, unsigned int y)
        {
            unsigned int baseAddress = m_configurator.getOffsets().m_baseAddress;
            writeMemory<unsigned int>(baseAddress + m_configurator.getOffsets().m_mouse.x, x);
            writeMemory<unsigned int>(baseAddress + m_configurator.getOffsets().m_mouse.y, y);
            PostMessage(m_configurator.getProcessInfo().windowHandle, WM_LBUTTONDBLCLK, MK_LBUTTON, NULL);
        }

        void Core::pressKey(unsigned char virtualKeyCode)
        {
            PostMessage(m_configurator.getProcessInfo().windowHandle, WM_KEYDOWN, virtualKeyCode, 1);
        }
    }
}
