#include "RRRBot.h"
#include "Core.h"
#include <google/protobuf/rpc/rpc_server.h>

namespace RRRBot
{
    CRRRBot::CRRRBot() :
        m_isRunning(false)
    { }

    CRRRBot& CRRRBot::getInstance()
    {
        static CRRRBot instance;
        return instance;
    }

    void CRRRBot::run()
    {
        if(!m_isRunning)
        {
			m_pMainLoopThread = std::make_unique<std::thread>(&CRRRBot::mainLoop, this);
        }        
    }

    void CRRRBot::mainLoop()
    {
        try {
			::google::protobuf::rpc::Server server;
			Core::Core core;
			server.AddService(&core, true);
			server.BindAndServe(core.getConfigurator().getServerSettings().port);
        }
        catch(const std::exception & e)
        {
            MsgBox(e.what());
            return;
        }
    }
}

