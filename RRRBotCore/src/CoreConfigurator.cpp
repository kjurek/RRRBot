#include <sstream>
#include "CoreConfigurator.h"

namespace RRRBot
{
    namespace Core
    {
        namespace Config
        {
            CoreConfigurator::CoreConfigurator()
            {
                m_configFilePath = GetAppDataFolderPath();
                if(m_configFilePath.empty())
                {
                    throw "Could not find AppData folder!";
                }
                m_configFilePath += "RRRBot\\config";
                loadConfig(m_configFilePath);
            }

            bool CoreConfigurator::loadConfig(std::string configFilePath)
            {
                Json::Value root;
                Json::Reader reader;

                if(!reader.parse(configFilePath, root))
                {
                    MsgBox(reader.getFormattedErrorMessages().c_str());
                    return false;
                }

                if(!loadOffsets(root["Core"]["Offsets"]))
                {
                    MsgBox("Could not load offsets");
                    return false;
                }

                if(!loadServerSettings(root["Core"]["Server"]))
                {
                    MsgBox("Could not load server settings");
                    return false;
                }
                return true;
            }

            bool CoreConfigurator::loadOffsets(Json::Value root)
            {
                m_offsets.m_mouse.x = root["Mouse"].get("x", 0xDEADBEEF).asInt();
                m_offsets.m_mouse.y = root["Mouse"].get("y", 0xDEADBEEF).asInt();
                m_offsets.m_player.x = root["Player"].get("x", 0xDEADBEEF).asInt();
                m_offsets.m_player.y = root["Player"].get("y", 0xDEADBEEF).asInt();
                m_offsets.m_player.z = root["Player"].get("z", 0xDEADBEEF).asInt();
                m_offsets.m_player.angle = root["Player"].get("angle", 0xDEADBEEF).asInt();
                m_offsets.m_baseAddress = reinterpret_cast<unsigned int>(GetModuleHandle("Game.dll"));
                return checkOffsets();
            }

            bool CoreConfigurator::loadServerSettings(Json::Value root)
            {
                m_serverSettings.ip = root.get("ip", "localhost").asString();
                m_serverSettings.port = root.get("port", 1337).asInt();
                return checkServerSettings();
            }

            bool CoreConfigurator::loadProcessInfo()
            {
                m_processInfo.processId = GetCurrentProcessId();
                m_processInfo.windowHandle = FindWindowFromProcessId(m_processInfo.processId);
                return checkProcessInfo();
            }

            bool CoreConfigurator::checkOffsets()
            {
                if(NULL == m_offsets.m_baseAddress)
                {
                    MsgBox("Invalid Base Address");
                    return false;
                }

                std::ostringstream os;
                bool validOffsets = true;
                auto checkOffset = [this, &os, &validOffsets](unsigned int offset, std::string name) {
                    if(offset == 0xDEADBEEF)
                    {
                        os << "offset " << name << " is not set." << std::endl;
                        validOffsets = false;
                    }
                    else if(!IsMemoryReadable(reinterpret_cast<void*>(m_offsets.m_baseAddress + offset), 4))
                    {
                        os << "offset " << name << " points to non readable location." << std::endl;
                        validOffsets = false;
                    }
                };

                checkOffset(m_offsets.m_mouse.x, "Mouse.X");
                checkOffset(m_offsets.m_mouse.y, "Mouse.Y");
                checkOffset(m_offsets.m_player.x, "Player.X");
                checkOffset(m_offsets.m_player.y, "Player.Y");
                checkOffset(m_offsets.m_player.z, "Player.Z");
                checkOffset(m_offsets.m_player.angle, "Player.Angle");
                if(!validOffsets)
                {
                    MsgBox(os.str().c_str());
                }
                return validOffsets;
            }

            bool CoreConfigurator::checkServerSettings()
            {
                return true;
            }

            bool CoreConfigurator::checkProcessInfo()
            {
                return (NULL != m_processInfo.processId != NULL) && (NULL != m_processInfo.windowHandle);
            }
        }
    }
}


