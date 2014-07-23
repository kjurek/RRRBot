#ifndef RRRBOT_H
#define RRRBOT_H

#include <thread>
#include <mutex>
#include <memory>

class CRRrBot
{
public:
    void stop();
    void start();
    void mainLoop();

    bool isRunning() const;

    static CRRrBot& getInstance();

    CRRrBot(const CRRrBot&) = delete;
    CRRrBot& operator=(const CRRrBot &) = delete;
protected:
    CRRrBot();
    bool m_isRunning;
    std::unique_ptr<std::thread> m_pMainLoopThread;
};

#endif // RRRBOT_H
