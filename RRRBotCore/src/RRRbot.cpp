#include <future>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include "RRRBot.h"
#include "Core.h"

namespace RRRBot
{
    CRRRBot::CRRRBot() :
        m_isRunning(false)
    {
		AllocConsole();

		m_hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		int hCrt = _open_osfhandle((long)m_hConsoleOut, _O_TEXT);
		FILE* hf_out = _fdopen(hCrt, "w");
		setvbuf(hf_out, NULL, _IONBF, 1);
		*stdout = *hf_out;

		m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
		hCrt = _open_osfhandle((long)m_hConsoleIn, _O_TEXT);
		FILE* hf_in = _fdopen(hCrt, "r");
		setvbuf(hf_in, NULL, _IONBF, 128);
		*stdin = *hf_in;
	}

    CRRRBot& CRRRBot::getInstance()
    {
        static CRRRBot instance;
        return instance;
    }

    void CRRRBot::run()
    {
		std::async(&CRRRBot::mainLoop, this);
    }

    void CRRRBot::mainLoop()
    {

		try 
		{
			std::cout << m_core.getConfigurator().getConfigLog() << std::endl;
			int menu = 0;

			while (1)
			{
				std::cout << "1. print player info" << std::endl;
				std::cout << "2. go to (x,y)" << std::endl;
				std::cout << "3. open quests tab" << std::endl;
				std::cin >> menu;

				switch (menu)
				{
				case 1:
				{
					auto playerInfo = m_core.GetPlayerInfo();
					std::cout << "Player Info: " << std::endl;
					std::cout << "Player X: " << playerInfo.x << std::endl;
					std::cout << "Player Y: " << playerInfo.y << std::endl;
					std::cout << "Player Z: " << playerInfo.z << std::endl;
					std::cout << "Player Rotate Angle: " << playerInfo.rotAngle << std::endl;
					break;
				}
				case 2:
				{
					int x, y;
					std::cout << "Podaj x: ";
					std::cin >> x;
					std::cout << "Podaj y: ";
					std::cin >> y;
					m_core.GoToXY({ x, y });
					break;
				}
				case 3:
				{
					m_core.PressKey(0x4A);
					break;
				}
				default:
					break;
				}
				std::cout << std::endl;
				std::this_thread::sleep_for(std::chrono::microseconds(100));
			}
		}
		catch(const std::exception & e)
        {
            MsgBox(e.what());
            return;
        }
    }
}

