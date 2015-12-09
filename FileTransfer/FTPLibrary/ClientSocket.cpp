// Socket.cpp
// compile with: cl /c /EHsc MathFuncsLib.cpp
// post-build command: lib MathFuncsLib.obj

#include "ClientSocket.h"

#include <stdexcept>

using namespace std;

namespace socklib
{

	// Custom Constructor
	SocketSender::SocketSender(std::string ipaddress, unsigned port) {
		_ip = ipaddress;
		_port = port;
	}

	SocketSender::~SocketSender() {
		// Clean up resources here
	}


	// Implement Methods Here
	void SocketSender::sendMessage()
	{
		{
			cout << "TCPClient\n";

			// initialize WSA
			WSAData wsaData;
			int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (iResult != 0) {
				cerr << "WSAStartup failed: " << iResult << endl;
				return;
			}

			// Create the TCP socket
			//SOCKET hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			SOCKET hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

			// Create the server address
			sockaddr_in serverAddress = { 0 };
			serverAddress.sin_family = AF_INET;
			serverAddress.sin_port = htons(_port);
			serverAddress.sin_addr.s_addr = inet_addr(_ip.c_str());

			// connect the socket
			if (connect(hSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
				cerr << "connect() failed" << endl;
				closesocket(hSocket);
				WSACleanup();
				return;
			}


			char sendbuf[32] = "Hello";
			char recvbuf[32] = "";

			int bytesSent = send(hSocket, sendbuf, strlen(sendbuf) + 1, 0);
			cout << "Sent = " << bytesSent << " bytes" << endl;
			int bytesRecv = recv(hSocket, recvbuf, 32, 0);
			cout << "Recv = " << bytesRecv << ": " << recvbuf << endl;

			int i = 42;
			send(hSocket, (char*)&i, sizeof(i), 0);

		}
	}



	SOCKET SocketSender::getSocket() {
		return hSocket;
	}
}
