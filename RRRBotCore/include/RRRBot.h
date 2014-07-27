#ifndef RRRBOT_H
#define RRRBOT_H

#include <thread>
#include <mutex>
#include <memory>

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
        std::unique_ptr<std::thread> m_pMainLoopThread;
    };
}


#endif // RRRBOT_H
