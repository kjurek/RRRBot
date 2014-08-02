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
			m_playerOffsets.base = playerOffsets["base"].toInt();
			m_playerOffsets.x = playerOffsets["x"].toInt();
			m_playerOffsets.y = playerOffsets["y"].toInt();
			m_playerOffsets.z = playerOffsets["z"].toInt();
			m_playerOffsets.angle = playerOffsets["angle"].toInt();

			QJsonArray moveOffsetsArray = playerOffsets["move"].toArray();
			for (int i = 0; i < moveOffsetsArray.size(); ++i)
			{
				m_playerOffsets.move.push_back(moveOffsetsArray[i].toInt());
			}

			QJsonObject mouseOffsets = offsets["Mouse"].toObject();
			m_mouseOffsets.x = mouseOffsets["x"].toInt();
			m_mouseOffsets.y = mouseOffsets["y"].toInt();
		}
	}
}