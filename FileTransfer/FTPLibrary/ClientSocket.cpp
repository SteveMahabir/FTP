/*
	ClientSocket.cpp 

	Implementation of the Client.
	Since this is a library users should never see this code

	Steve Mahabir and Kevin Postma

	11/Dec/2015
*/
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


		// Send the message idenfier
		size_t type = Type::MESSAGES;
		size_t identifierBytesSent = send(hSocket, (char*)&type, sizeof(type), 0);
		
		// Send the Message
		const char* messagebuff = message.c_str();
		size_t messageBytesSent = send(hSocket, messagebuff, strlen(messagebuff) + 1, 0);
		cout << "Client Sent = " << messageBytesSent << " bytes" << endl;

		// Receive the Confirmation
		char recvbuf[32] = "";
		size_t bytesRecv = recv(hSocket, recvbuf, 32, 0);
		cout << "Client Recv = " << bytesRecv << ": " << recvbuf << endl;

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

	bool SocketSender::SendFile(std::string path, std::string filename)
	{
		std::cout << "Path = " << path << endl;
		std::cout << "Filename = " << filename << std::endl;
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

		// Send the File Identifer
		int type = Type::FILES;
		int bytesSent = send(hSocket, (char*)&type, sizeof(type), 0);
		cout << "Client: FileIdentifier sent = " << bytesSent << " bytes" << endl;

		// Send the File Name Length
		int filename_length = strlen(filename.c_str());
		int filename_length_buffer_sent = send(hSocket, (char*)& filename_length, 4, 0);
		cout << "Client: Type::Filename length sent = " << filename_length_buffer_sent << " bytes" << endl;

		// Send the File Name
		const char* filename_buffer = filename.c_str();
		int filename_buffer_sent = send(hSocket, filename_buffer, strlen(filename_buffer) + 1, 0);
		cout << "Client: Filename Sent = " << filename_buffer_sent << " bytes" << endl;

		FILE* f;
		f = fopen(path.c_str(), "rb");

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
