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
	// Helper Methods

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


	// Function Task
	void task_MessageListener(std::promise<std::string> && p, std::string ip, unsigned port) {
		
		std::stringstream ss;

		// initialize WSA
		WSAData wsaData;
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			ss << "WSAStartup failed: " << iResult << std::endl;
			std::cerr << ss.str();
			p.set_value(ss.str());
			return;
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

		// Return Value
		ss << recvbuf;
		p.set_value(ss.str());

		// Clean up
		closesocket(hSocket);
		WSACleanup();
	}

	// Function Task
	std::string task_FileListener(std::promise<std::string> && p, std::string ip, unsigned port)
	{
		try
		{
			// Return statement
			std::stringstream ss;

			// initialize WSA
			WSAData wsaData;
			int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (iResult != 0) {
				ss << "WSAStartup failed: " << iResult << std::endl;
				std::cerr << ss.str();
				p.set_value(ss.str());
			}


			// Create the TCP socket
			SOCKET hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

			// Create the server address
			sockaddr_in serverAddress = { 0 };
			serverAddress.sin_family = AF_INET;
			// Custom Ip and Port!
			serverAddress.sin_port = htons(port);
			serverAddress.sin_addr.s_addr = inet_addr(ip.c_str());


			// bind the socket
			if (bind(hSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
				ss << "Could not bind!" << std::endl;
				std::cerr << ss.str();
				closesocket(hSocket);
				WSACleanup();
				p.set_value(ss.str());
				return ss.str();
			}


			if (listen(hSocket, 1) == SOCKET_ERROR) {
				ss << "Server Error listening." << std::endl;
				std::cerr << ss.str();
				closesocket(hSocket);
				WSACleanup();
				p.set_value(ss.str());
				return ss.str();
			}

			std::cout << "Server: Waiting for connection\n";
			SOCKET hAccepted = SOCKET_ERROR;
			while (hAccepted == SOCKET_ERROR) {
				hAccepted = accept(hSocket, NULL, NULL);
				std::cout << "Server: Connection establish" << std::endl;
			}


			// Somewhere to put the file!
			FILE *f = fopen("test.txt", "wb");
			if (f == NULL)
				return "Server: Error creating file";

			// Quick Check
			long filesize;
			if (!readlong(hAccepted, &filesize))
				return ss.str();

			std::cout << "Server: ReadLong successful" << std::endl;

			if (filesize > 0)
			{
				std::cout << "Server: filesize > 0" << std::endl;
				char buffer[1024];

				do
				{
					int num = min(filesize, sizeof(buffer));
					std::cout << "Server: FileSize = " << num << std::endl;


					if (!readdata(hAccepted, buffer, num))
						return ss.str();

					int offset = 0;
					do
					{

						size_t written = fwrite(&buffer[offset], 1, num - offset, f);
						std::cout << "Server: File Writing to Buffer - " << offset << std::endl;
						if (written < 1)
							return ss.str();
						offset += written;

					} while (offset < num);

					std::cout << "Server: Finished writing to buffer" << std::endl;
					filesize -= num;
				} while (filesize > 0);

				std::cout << "Server: File finished writing to buffer" << std::endl;
			}
			else
				std::cout << "Server: Empty File" << std::endl;


			// Finished!
			fclose(f);
			closesocket(hSocket);
			WSACleanup();
			ss << "File Recieved!";
			p.set_value(ss.str());
			return ss.str();
		}
		catch (std::exception ex) {
			return ex.what();
		}
	}

	// Implemented Methods
	std::string SocketListener::ListenForMessage()
	{
		std::promise<std::string> p;
		auto f = p.get_future();
		std::thread t(&task_MessageListener, std::move(p), _ip, _port);
		t.join();
		// Sleep(1000); // Debugging
		return f.get();

	}

	std::string SocketListener::ListenForFile()
	{
		std::promise<std::string> p;
		auto f = p.get_future();
		std::thread t(&task_FileListener, std::move(p), _ip, _port);
		t.join();
		// Sleep(1000); // Debugging
		return f.get();

	}

}