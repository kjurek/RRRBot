#include <iostream>
#include <google/protobuf/rpc/rpc_client.h>
#include "core_api.pb.h"

int main(int argc, char** argv)
{
	::google::protobuf::rpc::Client client("127.0.0.1", 1337);
	CoreApi::Stub coreStub(&client);
	Coords coords;
	Empty empty;
	::google::protobuf::rpc::Error err;

	coords.set_x(200);
	coords.set_y(300);
	err = coreStub.MouseClick(&coords, &empty);
	if (!err.IsNil())
	{
		std::cout << "Error! " << err.String();
	}
}