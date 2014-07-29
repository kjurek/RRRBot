#ifndef RRRBOT_H
#define RRRBOT_H

#include <thread>
#include <mutex>
#include <memory>
#include "Core.h"

namespace RRRBot
{
    class CRRRBot
    {
    public:
		void run();
		void mainLoop();
        static CRRRBot& getInstance();

        CRRRBot(const CRRRBot&) = delete;
        CRRRBot& operator=(const CRRRBot &) = delete;
    protected:
        CRRRBot();
        
		bool m_isRunning;
        HANDLE m_hConsoleIn, m_hConsoleOut;
		Core::Core m_core;
    };
}


#endif // RRRBOT_H
