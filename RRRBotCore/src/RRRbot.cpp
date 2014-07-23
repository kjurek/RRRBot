#include "RRRBot.h"

CRRrBot::CRRrBot() :
    m_isRunning(false)
{ }

CRRrBot& CRRrBot::getInstance()
{
    static CRRrBot instance;
    return instance;
}

void CRRrBot::start()
{
    if(m_isRunning)
    {
        stop();
    }
    m_pMainLoopThread = std::make_unique<std::thread>(&CRRrBot::mainLoop, this);
}

void CRRrBot::stop()
{
    m_isRunning = false;
    if(m_pMainLoopThread.get() != nullptr)
    {
        m_pMainLoopThread->join();
        m_pMainLoopThread.reset(nullptr);
    }
}

void CRRrBot::mainLoop()
{
    while(m_isRunning)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
