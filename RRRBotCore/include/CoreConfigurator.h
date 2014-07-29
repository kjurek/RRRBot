#ifndef CORECONFIGURATOR_H
#define CORECONFIGURATOR_H

#include <string>
#include <sstream>
#include <json/value.h>
#include <json/reader.h>
#include "Misc.h"

namespace RRRBot
{
    namespace Core
    {
        namespace Config
        {
            struct Offsets
            {
                int m_baseAddress;

                struct Mouse
                {
                    int x, y;
                } m_mouse;

                struct Player
                {
					int base;
                    int hp;
                    int x, y, z;
                    int angle;

					struct Move {
						int offset1;
						int offset2;
					} move;
                } m_player;
            };

            struct ServerSettings
            {
                std::string ip;
                int port;
            };

            struct ProcessInfo
            {
                DWORD processId;
                HWND windowHandle;
            };

            class CoreConfigurator
            {
            public:
                CoreConfigurator();

                std::string getConfigFilePath() const { return m_configFilePath; }
				std::string getConfigLog() const { return m_configLog.str(); }
                bool loadConfig(std::string configFilePath);
                bool isConfigValid() const;

                Offsets getOffsets() { return m_offsets; }
                ServerSettings getServerSettings() { return m_serverSettings; }
                ProcessInfo getProcessInfo() { return m_processInfo; }
            private:
                std::string m_configFilePath;
				std::ostringstream m_configLog;
                Offsets m_offsets;
                ServerSettings m_serverSettings;
                ProcessInfo m_processInfo;

                bool loadOffsets(Json::Value root);
                bool loadServerSettings(Json::Value root);
                bool loadProcessInfo();

                bool checkOffsets();
                bool checkServerSettings();
                bool checkProcessInfo();
            };
        }
    }
}


#endif // CORECONFIGURATOR_H
