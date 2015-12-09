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

		std::string sendMessage(std::string message);

		bool SendFile(std::string filename);

		SOCKET getSocket();

	private:

		// Socket Connection Managers
		void Connect();
		void Disconnect();

		// Core Socket Data
		SOCKET hSocket;
		WSAData wsaData;

		// Ip address and Port Number - assigned in the Constructor, never changed!
		std::string _ip;
		unsigned _port;
	};


}