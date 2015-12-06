// Socket.cpp
// compile with: cl /c /EHsc MathFuncsLib.cpp
// post-build command: lib MathFuncsLib.obj

#include "Socket.h"

#include <stdexcept>

using namespace std;

namespace socklib
{
	// Implement Methods Here

	std::string SocketListener::startListening()
	{
			// initialize WSA
			WSAData wsaData;
			int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (iResult != 0) {
				cerr << "WSAStartup failed: " << iResult << endl;
			}


			// Create the TCP socket
			SOCKET hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

			// Create the server address
			sockaddr_in serverAddress = { 0 };
			serverAddress.sin_family = AF_INET;
			serverAddress.sin_port = htons(PORT);
			serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

			// bind the socket
			if (bind(hSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
				closesocket(hSocket);
				WSACleanup();
				return "Bind Failed";
			}


			if (listen(hSocket, 1) == SOCKET_ERROR) {
				closesocket(hSocket);
				WSACleanup();
				return "Error listening on socket";
			}

			cout << "Waiting for connection\n";
			SOCKET hAccepted = SOCKET_ERROR;
			while (hAccepted == SOCKET_ERROR) {
				hAccepted = accept(hSocket, NULL, NULL);
			}
			cout << "Client connected\n";

			int bytesSent;
			char sendbuf[32] = "Goodbye";
			char recvbuf[32] = "";

			int bytesRecv = recv(hAccepted, recvbuf, 32, 0);
			cout << "Recv = " << bytesRecv << ": " << recvbuf << endl;
			bytesSent = send(hAccepted, sendbuf, strlen(sendbuf) + 1, 0);
			cout << "Sent = " << bytesSent << " bytes" << endl;

			int i;
			bytesRecv = recv(hAccepted, (char*)&i, 4, 0);
			cout << "i = " << i << endl;
			

			closesocket(hSocket);
			WSACleanup();

			return "Received File!";;
	}

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
			SOCKET hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

			// Create the server address
			sockaddr_in serverAddress = { 0 };
			serverAddress.sin_family = AF_INET;
			serverAddress.sin_port = htons(PORT);
			serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

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

}