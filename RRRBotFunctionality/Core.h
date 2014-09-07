#ifndef CORE_H
#define CORE_H

#include <set>
#include <memory>
#include "Command.h"
#include "OffsetsManager.h"
#include "Player.h"
#include "Target.h"

namespace RRRBot
{
	namespace Core
	{
		class CCore
		{
		public:
			CCore() : m_player({ 0 }) { }
			void registerCommand(std::shared_ptr<CCommand> command);
			void unregisterCommand(std::string commandName);
			std::shared_ptr<CCommand> getCommand(std::string commandName);
			
			GameData::Player getPlayer() const { return m_player; }
			GameData::Target getTarget() const { return m_target; }

			void setPlayer(GameData::Player& player) { m_player = player; }
			void setTarget(GameData::Target& target) { m_target = target; }

			RRRBot::OffsetManagers::COffsetsManager m_offsetManager;
		private:
			class CCommandPtrComparator
			{
			public:
				bool operator()(std::shared_ptr<CCommand> a, std::shared_ptr<CCommand> b) const {
					return *a < *b;
				}
			};
			std::set <std::shared_ptr<CCommand>, CCommandPtrComparator> m_vpCommands;
			GameData::Player m_player;
			GameData::Target m_target;
		};
	}	
}

#endif
