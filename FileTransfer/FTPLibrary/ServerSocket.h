#pragma once
/*
	ServerSocket.h

	Header file for controlling the Server Socket Listener
	Steve Mahabir and Kevin Postma

	11/Dec/2015
*/


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
		SocketListener(std::string ipaddress, unsigned port, std::string save_directory);
		~SocketListener();

		// Methods
		std::string Listen();

		// Message Identifier
		enum Type {
			MESSAGES,
			FILES
		};

	private:
		// Core Socket Data
		SOCKET hSocket;
		WSAData wsaData;

		// Ip address and Port Number - assigned in the Constructor, never changed!
		std::string _ip;
		unsigned _port;
		std::string _directory;

	};

}