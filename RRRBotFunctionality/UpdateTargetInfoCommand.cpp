#include "UpdateTargetInfoCommand.h"

namespace RRRBot
{
	namespace Commands
	{
		std::shared_ptr<CCommand> CUpdateTargetInfoCommand::clone()
		{
			auto copy = std::make_shared<CUpdateTargetInfoCommand>(m_processManager, m_core);
			copy->m_nextStep = m_nextStep;
			return copy;
		}

		std::string CUpdateTargetInfoCommand::name() const
		{
			return "UpdateTargetInfo";
		}

		void CUpdateTargetInfoCommand::parseInput(std::istream& is)
		{
			// nothing to parse
		}

		void CUpdateTargetInfoCommand::commandStep()
		{
			RRRBot::GameData::Target target;
			auto& targetOffsetManager = m_core.m_offsetManager.m_targetOffsetsManager;

			bool hasTarget = m_processManager.readMemory<bool>(targetOffsetManager.hasTargetAddr());

			if (hasTarget)
			{
				target.hp = m_processManager.readMemory<int>(targetOffsetManager.hpAddr());
				target.maxHp = m_processManager.readMemory<int>(targetOffsetManager.maxHpAddr());
				target.name = m_processManager.readWString(targetOffsetManager.nameAddr(), 20);
				target.exists = true;
			}
			else
			{
				target.exists = false;
			}
			m_core.setTarget(target);
			m_nextStep = false;
		}

		bool CUpdateTargetInfoCommand::hasNextStep()
		{
			return m_nextStep;
		}
	}
}

