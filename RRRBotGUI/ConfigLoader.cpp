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
			QJsonObject targetOffsets = offsets["Target"].toObject();

			bool ok;

			QJsonArray playerBaseArray = playerOffsets["base"].toArray();
			for (auto& offset : playerBaseArray)
			{
				m_playerOffsets.base.push_back(offset.toString().toUInt(&ok, 16));
			}		
			m_playerOffsets.x = playerOffsets["x"].toString().toUInt(&ok, 16);
			m_playerOffsets.y = playerOffsets["y"].toString().toUInt(&ok, 16);
			m_playerOffsets.z = playerOffsets["z"].toString().toUInt(&ok, 16);
			m_playerOffsets.flightTime = playerOffsets["flightTime"].toString().toUInt(&ok, 16);
			m_playerOffsets.maxFlightTime = playerOffsets["maxFlightTime"].toString().toUInt(&ok, 16);
			m_playerOffsets.hp = playerOffsets["hp"].toString().toUInt(&ok, 16);
			m_playerOffsets.maxHp = playerOffsets["maxHp"].toString().toUInt(&ok, 16);
			m_playerOffsets.mp = playerOffsets["mp"].toString().toUInt(&ok, 16);
			m_playerOffsets.maxMp = playerOffsets["maxMp"].toString().toUInt(&ok, 16);
			m_playerOffsets.rotH = playerOffsets["rotH"].toString().toUInt(&ok, 16);
			m_playerOffsets.rotV = playerOffsets["rotV"].toString().toUInt(&ok, 16);
			m_playerOffsets.move = playerOffsets["move"].toString().toUInt(&ok, 16);
			m_playerOffsets.name = playerOffsets["name"].toString().toUInt(&ok, 16);
			
			QJsonArray targetBaseArray = targetOffsets["base"].toArray();
			for (auto offset : targetBaseArray)
			{
				m_targetOffsets.base.push_back(offset.toString().toUInt(&ok, 16));
			}
			m_targetOffsets.hp = targetOffsets["hp"].toString().toUInt(&ok, 16);
			m_targetOffsets.maxHp = targetOffsets["maxHp"].toString().toUInt(&ok, 16);
			m_targetOffsets.name = targetOffsets["name"].toString().toUInt(&ok, 16);

			QJsonObject mouseOffsets = offsets["Mouse"].toObject();
			m_mouseOffsets.x = mouseOffsets["x"].toString().toUInt(&ok, 16);
			m_mouseOffsets.y = mouseOffsets["y"].toString().toUInt(&ok, 16);
		}
	}
}