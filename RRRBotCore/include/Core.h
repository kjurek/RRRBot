#ifndef CORE_H
#define CORE_H

#include "core_api.pb.h"
#include "CoreConfigurator.h"

namespace RRRBot
{
    namespace Core
    {
        class Core : public CoreApi
        {
        public:
			virtual ~Core() { }

			virtual const ::google::protobuf::rpc::Error GetPlayerInfo(
				const ::Empty* request,
				::PlayerInfo* response);

			virtual const ::google::protobuf::rpc::Error GetInventory(
				const ::Empty* request,
				::Inventory* response);

			virtual const ::google::protobuf::rpc::Error GoToXY(
				const ::Coords* request,
				::Empty* response);

			virtual const ::google::protobuf::rpc::Error MouseClick(
				const ::Coords* request,
				::Empty* response);

			virtual const ::google::protobuf::rpc::Error PressKey(
				const ::Key* request,
				::Empty* response);

            Config::CoreConfigurator getConfigurator() const { return m_configurator; }
        private:
            Config::CoreConfigurator m_configurator;

            template<class T>
            T readMemory(unsigned int address)
            {
                return *reinterpret_cast<T*>(address);
            }

            template<class T>
            void writeMemory(unsigned int address, T value)
            {
                *reinterpret_cast<T*>(address) = value;
            }
        };
    }
}

#endif
