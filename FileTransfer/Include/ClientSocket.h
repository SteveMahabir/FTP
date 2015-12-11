#pragma once

/*
	ClientSocket.h

	Used for Controlling the Client Socket Calls

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

using namespace std;

namespace socklib {

	class SocketSender {

	public:
		// Constructor and Destructor
		SocketSender(std::string ipaddress, unsigned port);
		~SocketSender();

		// Sends a Message to the Server
		std::string sendMessage(std::string message);

		// Sends a File to the Server
		bool SendFile(std::string path, std::string filename);

		// Gets the Current Socket
		SOCKET getSocket();

		enum Type {
			MESSAGES,
			FILES
		};

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