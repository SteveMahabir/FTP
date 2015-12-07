#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>

#include <string>

// Needed for Sockets
#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")

using namespace std;

namespace socklib {

	unsigned const PORT = 70007;

	class SocketListener {
	private:
		//unsigned const PORT;
	public:
		SocketListener(unsigned port, std::string ipaddress) {};

		static std::string startListening();
	};

}