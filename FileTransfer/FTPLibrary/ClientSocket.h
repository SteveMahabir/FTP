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

	class SocketSender {

	public:
		SocketSender(std::string ipaddress, unsigned port);
		~SocketSender();

		void sendMessage();

		SOCKET getSocket();

	private:
		SOCKET hSocket;
		std::string _ip;
		unsigned _port;
	};


}