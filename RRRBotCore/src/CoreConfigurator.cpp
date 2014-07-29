#include <sstream>
#include <fstream>
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
                m_configFilePath += "\\RRRBot\\config";
				m_configLog << "config file path: " << m_configFilePath << std::endl;
                loadConfig(m_configFilePath);
            }

            bool CoreConfigurator::loadConfig(std::string configFilePath)
            {
                Json::Value root;
                Json::Reader reader;
				std::ifstream configFile(m_configFilePath);

				if (!reader.parse(configFile, root))
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

				if (!loadProcessInfo())
				{
					MsgBox("Could not load process information");
					return false;
				}
                return true;
            }

            bool CoreConfigurator::loadOffsets(Json::Value root)
            {
				m_configLog << "Loading mouse offsets" << std::endl;
                m_offsets.m_mouse.x = root["Mouse"].get("x", -1).asInt();
				m_configLog << "Mouse X offset: " << m_offsets.m_mouse.x << std::endl;
                m_offsets.m_mouse.y = root["Mouse"].get("y", -1).asInt();
				m_configLog << "Mouse Y offset: " << m_offsets.m_mouse.y << std::endl;

				m_configLog << "Loading Player offsets" << std::endl;
				m_offsets.m_player.base = root["Player"].get("base", -1).asInt();
				m_configLog << "Player Base offset: " << m_offsets.m_player.base << std::endl;
				m_offsets.m_player.x = root["Player"].get("x", -1).asInt();
				m_configLog << "Player X offset: " << m_offsets.m_player.x << std::endl;
				m_offsets.m_player.y = root["Player"].get("y", -1).asInt();
				m_configLog << "Player Y offset: " << m_offsets.m_player.y << std::endl;
				m_offsets.m_player.z = root["Player"].get("z", -1).asInt();
				m_configLog << "Player Z offset: " << m_offsets.m_player.z << std::endl;
				m_offsets.m_player.angle = root["Player"].get("angle", -1).asInt();
				m_configLog << "Player Rotate Angle offset: " << m_offsets.m_player.angle << std::endl;

				m_configLog << "Player move offsets: " << std::endl;
				m_offsets.m_player.move.offset1 = root["Player"]["move"][0].asInt();
				m_configLog << "move offset1: " << m_offsets.m_player.move.offset1 << std::endl;
				m_offsets.m_player.move.offset2 = root["Player"]["move"][1].asInt();
				m_configLog << "move offset2: " << m_offsets.m_player.move.offset2 << std::endl;

				m_offsets.m_baseAddress = reinterpret_cast<unsigned int>(GetModuleHandle("Game.dll"));
				m_configLog << "Game.dll Address: " << m_offsets.m_baseAddress << std::endl;
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
				m_configLog << "Loading process information" << std::endl;
                m_processInfo.processId = GetCurrentProcessId();
				m_configLog << "process id: " << m_processInfo.processId << std::endl;
                m_processInfo.windowHandle = FindWindowFromProcessId(m_processInfo.processId);
				m_configLog << "window handle: " << m_processInfo.windowHandle << std::endl;

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
                    if(offset == -1)
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
				checkOffset(m_offsets.m_player.base, "Player base");
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


