// Socket.cpp
// compile with: cl /c /EHsc MathFuncsLib.cpp
// post-build command: lib MathFuncsLib.obj

#include "ClientSocket.h"

#include <stdexcept>
#include <sstream>
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
		Disconnect();
	}

	void SocketSender::Connect() {

		// initialize WSA
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
			Disconnect();
			return;
		}

	}

	void SocketSender::Disconnect() {
		closesocket(hSocket);
		WSACleanup();
	}


	// Implement Methods Here
	std::string SocketSender::sendMessage(std::string message)
	{
		// Return Stream
		std::stringstream ss;

		// initialize WSA
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			ss << "WSAStartup failed: " << iResult << endl;
			cerr << ss.str();
			return ss.str();
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
			ss << "connect() failed" << endl;
			cerr << ss.str();
			Disconnect();
			return ss.str();
		}

		char sendbuf[32] = "Hello"; // message;
		const char* messagebuff = message.c_str();

		char recvbuf[32] = "";
		
		
		int bytesSent = send(hSocket, messagebuff, strlen(messagebuff) + 1, 0);


		//int bytesSent = send(hSocket, sendbuf, strlen(sendbuf) + 1, 0);
		cout << "Client Sent = " << bytesSent << " bytes" << endl;

		int bytesRecv = recv(hSocket, recvbuf, 32, 0);
		cout << "Client Recv = " << bytesRecv << ": " << recvbuf << endl;

		int i = 42;
		send(hSocket, (char*)&i, sizeof(i), 0);

		
		ss << recvbuf;

		return ss.str();

	}


	bool senddata(SOCKET sock, void *buf, int buflen)
	{
		char *pbuf = (char *)buf;

		while (buflen > 0)
		{
			int num = send(sock, pbuf, buflen, 0);
			if (num == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					// optional: use select() to check for timeout to fail the send
					continue;
				}
				return false;
			}

			pbuf += num;
			buflen -= num;
		}

		return true;
	}

	bool sendlong(SOCKET sock, long value)
	{
		value = htonl(value);
		return senddata(sock, &value, sizeof(value));
	}

	bool SocketSender::SendFile(std::string filename)
	{
		// initialize WSA
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			cerr << "WSAStartup failed: " << iResult << endl;
			return false;
		}

		// Create the TCP socket
		SOCKET hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		// Create the server address
		sockaddr_in serverAddress = { 0 };
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(_port);
		serverAddress.sin_addr.s_addr = inet_addr(_ip.c_str());

		// connect the socket
		if (connect(hSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
			cerr << "connect() failed" << endl;
			Disconnect();
			return false;
		}

		FILE* f;
		f = fopen(filename.c_str(), "rb");

		fseek(f, 0, SEEK_END);
		long filesize = ftell(f);
		rewind(f);
		if (filesize == EOF)
			return false;
		if (!sendlong(hSocket, filesize))
			return false;
		if (filesize > 0)
		{
			char buffer[1024];
			do
			{
				size_t num = min(filesize, sizeof(buffer));
				num = fread(buffer, 1, num, f);
				if (num < 1)
					return false;
				if (!senddata(hSocket, buffer, num))
					return false;
				filesize -= num;
			} while (filesize > 0);
		}

		fclose(f);
		return true;
	}


	SOCKET SocketSender::getSocket() {
		return hSocket;
	}
}
