#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

// Needed for Sockets
#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")


namespace socklib {
	 
	class SocketListener {
	
	public:

		// Constructors
		SocketListener(std::string ipaddress, unsigned port);
		~SocketListener();

		// Methods
		std::string Listen();

		enum Type {
			MESSAGES,
			FILES
		};

	private:
		// Data Members
		SOCKET hSocket;
		std::string _ip;
		unsigned _port;

	};

}