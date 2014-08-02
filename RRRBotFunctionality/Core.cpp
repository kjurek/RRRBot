#include "Core.h"

namespace RRRBot
{
	void CCore::registerCommand(CCommand* command)
	{
		m_vpCommands.insert(command);
	}

	void CCore::unregisterCommand(std::string commandName)
	{
		//m_vpCommands.erase(;
	}

	CCommand* CCore::getCommand(std::string commandName)
	{

	}
}



/*
PlayerInfo Core::GetPlayerInfo()
{
	PlayerInfo result;
	auto offsets = m_configurator.getOffsets();
			
	result.x = readMemory<float>(offsets.m_baseAddress, offsets.m_player.x);
	result.y = readMemory<float>(offsets.m_baseAddress, offsets.m_player.y);
	result.z = readMemory<float>(offsets.m_baseAddress, offsets.m_player.z);
	result.rotAngle = readMemory<float>(offsets.m_baseAddress, offsets.m_player.angle, 0);
			
	return result;
}


Inventory Core::GetInventory()
{
	Inventory result;
	return result;
}

void Core::GoToXY(Coords coords)
{
	auto offsets = m_configurator.getOffsets();
	float tolerance = 5.0f;

	while (1)
	{
		auto info = GetPlayerInfo();
		float dx = coords.x - info.x;
		float dy = coords.y - info.y;
				
		std::cout << "actual: (" << info.x << "," << info.y << ")" << std::endl;
		std::cout << "delta: (" << std::abs(dx) << "," << std::abs(dy) << ")" << std::endl << std::endl;
				
		if (std::abs(dx) < tolerance && std::abs(dy) < tolerance)
		{
			break;
		}

		// * 57.295 -> radians to degrees
		float theta = atan(dy / dx) * 57.295f;

		if (dx < 0)
		{
			theta = -theta;
		}
		else {
			theta = 180 - theta;
		}

		writeMemory<float>(
			theta,
			readMemory<int>(offsets.m_baseAddress + offsets.m_player.angle)
		);				

		writeMemory<char>(
			7,
			readMemory<int>(offsets.m_player.base, offsets.m_player.move.offset1)
			+
			offsets.m_player.move.offset2
		);

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	writeMemory<char>(
		0,
		readMemory<int>(offsets.m_player.base, offsets.m_player.move.offset1)
		+
		offsets.m_player.move.offset2
	);
}

void Core::MouseClick(Coords coords)
{
	unsigned int baseAddress = m_configurator.getOffsets().m_baseAddress;
	writeMemory<unsigned int>(baseAddress + m_configurator.getOffsets().m_mouse.x, coords.x);
	writeMemory<unsigned int>(baseAddress + m_configurator.getOffsets().m_mouse.y, coords.y);
	SendMessage(
		m_configurator.getProcessInfo().windowHandle, 
		WM_LBUTTONDBLCLK, 
		MK_LBUTTON, 
		NULL);
}

void Core::PressKey(unsigned int virtualKeyCode)
{
	SendMessage(
		m_configurator.getProcessInfo().windowHandle,
		WM_KEYDOWN,
		virtualKeyCode,
		1);
}
*/