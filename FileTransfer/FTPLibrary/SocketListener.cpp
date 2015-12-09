// ServerSocket.cpp

#include "ServerSocket.h"

#include <thread>
#include <future>


#include <sstream>

namespace socklib
{
	// Only Constructor
	SocketListener::SocketListener(std::string ipaddress, unsigned port) {
		_ip = ipaddress;
		_port = port;
	};

	SocketListener::~SocketListener() {
		// Clean up resources here
	}

	// Function Task
	void func(std::promise<std::string> && p, std::string ip, unsigned port) {
		
		// initialize WSA
		WSAData wsaData;
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			std::cerr << "WSAStartup failed: " << iResult << std::endl;
		}


		// Create the TCP socket
		SOCKET hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		// Create the server address
		sockaddr_in serverAddress = { 0 };
		serverAddress.sin_family = AF_INET;

		serverAddress.sin_port = htons(port);
		serverAddress.sin_addr.s_addr = inet_addr(ip.c_str());

		// HARD CODED
		//serverAddress.sin_port = htons(PORT);
		//serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

		// bind the socket
		if (bind(hSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
			closesocket(hSocket);
			WSACleanup();
			p.set_value("Bind Failed");
			return;
		}


		if (listen(hSocket, 1) == SOCKET_ERROR) {
			closesocket(hSocket);
			WSACleanup();
			p.set_value("Error listening on socket");
			return;
		}

		std::cout << "Waiting for connection\n";
		SOCKET hAccepted = SOCKET_ERROR;
		while (hAccepted == SOCKET_ERROR) {
			hAccepted = accept(hSocket, NULL, NULL);
		}
		std::cout << "Client connected\n";

		int bytesSent;
		char sendbuf[32] = "Thank you for the message!";
		char recvbuf[32] = "";

		int bytesRecv = recv(hAccepted, recvbuf, 32, 0);
		std::cout << "Recv = " << bytesRecv << ": " << recvbuf << std::endl;
		bytesSent = send(hAccepted, sendbuf, strlen(sendbuf) + 1, 0);
		std::cout << "Sent = " << bytesSent << " bytes" << std::endl;

		int i;
		bytesRecv = recv(hAccepted, (char*)&i, 4, 0);
		std::cout << "i = " << i << std::endl;


		closesocket(hSocket);
		WSACleanup();

		p.set_value("Received File!");

	}



	// Implemented Methods
	std::string SocketListener::startListening()
	{
		std::promise<std::string> p;
		auto f = p.get_future();
		std::thread t(&func, std::move(p), _ip, _port);
		t.join();
		// Sleep(1000); // Debugging
		return f.get();

	}

	bool readdata(SOCKET sock, void *buf, int buflen)
	{
		char *pbuf = (char *)buf;

		while (buflen > 0)
		{
			int num = recv(sock, pbuf, buflen, 0);
			if (num == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					// optional: use select() to check for timeout to fail the read
					continue;
				}
				return false;
			}
			else if (num == 0)
				return false;

			pbuf += num;
			buflen -= num;
		}

		return true;
	}

	bool readlong(SOCKET sock, long *value)
	{
		if (!readdata(sock, value, sizeof(value)))
			return false;
		*value = ntohl(*value);
		return true;
	}

	std::string SocketListener::ReadFile()
	{
		// Return statement
		std::stringstream ss;

		// initialize WSA
		WSAData wsaData;
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			ss << "WSAStartup failed: " << iResult << std::endl;
			std::cerr << ss.str();
			return ss.str();
		}


		// Create the TCP socket
		SOCKET hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		// Create the server address
		sockaddr_in serverAddress = { 0 };
		serverAddress.sin_family = AF_INET;
		// Custom Ip and Port!
		serverAddress.sin_port = htons(_port);
		serverAddress.sin_addr.s_addr = inet_addr(_ip.c_str());


		// bind the socket
		if (bind(hSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
			ss << "Could not bind!"<< std::endl;
			std::cerr << ss.str();
			closesocket(hSocket);
			WSACleanup();
			return ss.str();
		}


		if (listen(hSocket, 1) == SOCKET_ERROR) {
			ss << "Server Error listening." << std::endl;
			std::cerr << ss.str();
			closesocket(hSocket);
			WSACleanup();
			return ss.str();
		}

		std::cout << "Server: Waiting for connection\n";
		SOCKET hAccepted = SOCKET_ERROR;
		while (hAccepted == SOCKET_ERROR) {
			hAccepted = accept(hSocket, NULL, NULL);
			std::cout << "Server: Connection establish" << std::endl;
		}

		Sleep(1000);
		return false;

		FILE *f;
		long filesize;

		// Quick Check
		if (!readlong(hAccepted, &filesize))
			return false;

		if (filesize > 0)
		{
			char buffer[1024];
			do
			{
				int num = min(filesize, sizeof(buffer));
				if (!readdata(hAccepted, buffer, num))
					return false;
				int offset = 0;
				do
				{
					size_t written = fwrite(&buffer[offset], 1, num - offset, f);
					if (written < 1)
						return false;
					offset += written;
				} while (offset < num);
				filesize -= num;
			} while (filesize > 0);
		}


		// Finished!
		closesocket(hSocket);
		WSACleanup();
		ss << "File Sent";
		return ss.str();
	}

}