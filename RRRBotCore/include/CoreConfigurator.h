#ifndef CORECONFIGURATOR_H
#define CORECONFIGURATOR_H

#include <string>
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
                unsigned int m_baseAddress;

                struct Mouse
                {
                    unsigned int x, y;
                } m_mouse;

                struct Player
                {
                    unsigned int hp;
                    unsigned int x, y, z;
                    unsigned int angle;
                } m_player;
            };

            struct ServerSettings
            {
                std::string ip;
                unsigned int port;
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
                bool loadConfig(std::string configFilePath);
                bool isConfigValid() const;

                Offsets getOffsets() { return m_offsets; }
                ServerSettings getServerSettings() { return m_serverSettings; }
                ProcessInfo getProcessInfo() { return m_processInfo; }
            private:
                std::string m_configFilePath;
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
