#ifndef CORE_H
#define CORE_H

#include <set>
#include "Command.h"

namespace RRRBot
{
	class CCore
	{
	public:
		void registerCommand(CCommand* command);
		void unregisterCommand(std::string commandName);
		CCommand* getCommand(std::string commandName);
	private:
		class CCommandPtrComparator
		{
		public:
			bool operator()(const CCommand* a, const CCommand* b) const {
				return *a < *b;
			}
		};
		std::set <CCommand*, CCommandPtrComparator> m_vpCommands;
	};
}

#endif
