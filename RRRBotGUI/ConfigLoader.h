#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <string>
#include <stdexcept>
#include "MouseOffsets.h"
#include "PlayerOffsets.h"
#include "TargetOffsets.h"

namespace RRRBot
{
	namespace Config
	{
		class CConfigLoaderException : public std::runtime_error
		{
		public:
			CConfigLoaderException(std::string message)
				: std::runtime_error(message)
			{ }
		};

		class CConfigLoader
		{
		public:
			void load(std::string configFilePath);

			Offsets::MouseOffsets getMouseOffsets() { return m_mouseOffsets; }
			Offsets::PlayerOffsets getPlayerOffsets() { return m_playerOffsets; }
			Offsets::TargetOffsets getTargetOffsets() { return m_targetOffsets; }
		private:
			Offsets::MouseOffsets m_mouseOffsets;
			Offsets::PlayerOffsets m_playerOffsets;
			Offsets::TargetOffsets m_targetOffsets;
		};
	}
}

#endif