#include <cmath>
#include "Core.h"
#include "stdafx.h"

namespace RRRBot
{
    namespace Core
    {
		const ::google::protobuf::rpc::Error Core::GetPlayerInfo(
			const ::Empty* request,
			::PlayerInfo* response)
		{
			unsigned int baseAddress = m_configurator.getOffsets().m_baseAddress;
			response->set_x(readMemory<float>(baseAddress + m_configurator.getOffsets().m_player.x));
			response->set_y(readMemory<float>(baseAddress + m_configurator.getOffsets().m_player.y));
			response->set_z(readMemory<float>(baseAddress + m_configurator.getOffsets().m_player.z));
			response->set_angle(readMemory<float>(readMemory<unsigned int>(baseAddress + m_configurator.getOffsets().m_player.angle)));
			MsgBox("Player info");
			return ::google::protobuf::rpc::Error::Nil();
		}

		const ::google::protobuf::rpc::Error Core::GetInventory(
			const ::Empty* request,
			::Inventory* response)
		{
			MsgBox("Get Inventory");
			return ::google::protobuf::rpc::Error::Nil();
		}

		const ::google::protobuf::rpc::Error Core::GoToXY(
			const ::Coords* request,
			::Empty* response)
		{
			MsgBox("Go to xy");
			return ::google::protobuf::rpc::Error::Nil();
		}

		const ::google::protobuf::rpc::Error Core::MouseClick(
			const ::Coords* request,
			::Empty* response)
		{
			MsgBox("Mouse click");
			unsigned int baseAddress = m_configurator.getOffsets().m_baseAddress;
			writeMemory<unsigned int>(baseAddress + m_configurator.getOffsets().m_mouse.x, request->x());
			writeMemory<unsigned int>(baseAddress + m_configurator.getOffsets().m_mouse.y, request->y());
			PostMessage(m_configurator.getProcessInfo().windowHandle, WM_LBUTTONDBLCLK, MK_LBUTTON, NULL);
			return ::google::protobuf::rpc::Error::Nil();
		}

		const ::google::protobuf::rpc::Error Core::PressKey(
			const ::Key* request,
			::Empty* response)
		{
			MsgBox("Press key");
			PostMessage(m_configurator.getProcessInfo().windowHandle,
				WM_KEYDOWN,
				*request->key().c_str(),
				1);
			return ::google::protobuf::rpc::Error::Nil();
		}
    }
}
