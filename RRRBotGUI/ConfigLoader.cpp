#include <qfile.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "ConfigLoader.h"

namespace RRRBot
{
	namespace Config
	{
		void CConfigLoader::load(std::string configFilePath)
		{
			QFile configFile(configFilePath.c_str());
			if (false == configFile.open(QIODevice::ReadOnly))
			{
				throw CConfigLoaderException("Could not open: " + configFilePath);
			}
			QByteArray configData = configFile.readAll();
			QJsonDocument configDoc(QJsonDocument::fromJson(configData));
			QJsonObject root(configDoc.object());
			QJsonObject offsets = root["Offsets"].toObject();
			QJsonObject playerOffsets = offsets["Player"].toObject();
						
			QJsonArray playerBaseOffsetsArray = playerOffsets["base"].toArray();
			for (int i = 0; i < playerBaseOffsetsArray.size(); ++i)
			{
				m_playerOffsets.base.push_back(playerBaseOffsetsArray[i].toInt());
			}
			m_playerOffsets.x = playerOffsets["x"].toInt();
			m_playerOffsets.y = playerOffsets["y"].toInt();
			m_playerOffsets.z = playerOffsets["z"].toInt();
			m_playerOffsets.flightTime = playerOffsets["flightTime"].toInt();
			m_playerOffsets.maxFlightTime = playerOffsets["maxFlightTime"].toInt();
			m_playerOffsets.hp = playerOffsets["hp"].toInt();
			m_playerOffsets.maxHp = playerOffsets["maxHp"].toInt();
			m_playerOffsets.mp = playerOffsets["mp"].toInt();
			m_playerOffsets.maxMp = playerOffsets["maxMp"].toInt();
			m_playerOffsets.rotH = playerOffsets["rotH"].toInt();
			m_playerOffsets.rotV = playerOffsets["rotV"].toInt();
			m_playerOffsets.move = playerOffsets["move"].toInt();
			m_playerOffsets.name = playerOffsets["name"].toInt();
			
			QJsonObject mouseOffsets = offsets["Mouse"].toObject();
			m_mouseOffsets.x = mouseOffsets["x"].toInt();
			m_mouseOffsets.y = mouseOffsets["y"].toInt();
		}
	}
}