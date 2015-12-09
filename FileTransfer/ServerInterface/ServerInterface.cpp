// This is the main DLL file.

#include "stdafx.h"

#include "ServerInterface.h"

namespace ServerInterface
{
	ServerSocket::ServerSocket(System::String^ ip, unsigned port) {
		_ipaddress = ip;
		_port = port;
	}

	void RecieveFile() {
	}
}
