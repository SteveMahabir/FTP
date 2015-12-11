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
	void task_listen(std::promise<std::string> && p, std::string ip, unsigned port) {

		std::stringstream ss;

		// initialize WSA
		WSAData wsaData;
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			ss << "Server: WSAStartup failed: " << iResult << std::endl;
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

		// bind the socket
		if (bind(hSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
			closesocket(hSocket);
			WSACleanup();
			p.set_value("Server: Bind Failed");
			return;
		}


		if (listen(hSocket, 1) == SOCKET_ERROR) {
			closesocket(hSocket);
			WSACleanup();
			p.set_value("Server: Error listening on socket");
			return;
		}

		std::cout << "Server: Waiting for connection\n";

		SOCKET hAccepted = SOCKET_ERROR;
		while (hAccepted == SOCKET_ERROR) {
			hAccepted = accept(hSocket, NULL, NULL);
		}
		std::cout << "Server: Client connected\n";

		
		// Receive Socket Identifier
		int messageIdentifer;
		int bytesRecv = recv(hAccepted, (char*)&messageIdentifer, 4, 0);
		std::cout << "Server: Message Identifier Recieved [" << bytesRecv << "]: " << messageIdentifer << std::endl;


		char receivedMessage[32] = "";
		int confirmationMessageSent;
		int messageBufferSize;
		char sendbuf[32] = "Thank you for the message!";

		switch (messageIdentifer) 
		{
			case SocketListener::Type::MESSAGES:

				// Receive Message
				messageBufferSize = recv(hAccepted, receivedMessage, 32, 0);
				std::cout << "Server: Recieved Message [" << messageBufferSize << "]: " << receivedMessage << std::endl;
			
				// Set the return string with the message received
				ss << receivedMessage;

				// Send the Confirmation of Receival
				confirmationMessageSent = send(hAccepted, sendbuf, strlen(sendbuf) + 1, 0);
				std::cout << "Sent = " << confirmationMessageSent << " bytes" << std::endl;

				break;
		case SocketListener::Type::FILES:
			// Somewhere to put the file!
			FILE *f = fopen("test.txt", "wb");
			if (f == NULL) {
				ss << "Server: Error creating file";
				std::cerr << ss.str() << std::endl;
				p.set_value(ss.str());
				return;
			}

			// Quick Check
			long filesize;
			if (!readlong(hAccepted, &filesize)) {
				ss << "Server: Error converting (readlong) file";
				std::cerr << ss.str() << std::endl;
				p.set_value(ss.str());
				return;
			}
			std::cout << "Server: ReadLong successful" << std::endl;

			if (filesize > 0)
			{
				std::cout << "Server: filesize > 0" << std::endl;
				char buffer[1024];

				do
				{
					int num = min(filesize, sizeof(buffer));
					std::cout << "Server: FileSize = " << num << std::endl;

					if (!readdata(hAccepted, buffer, num)) {
						ss << "Server: Error reading file";
						std::cerr << ss.str() << std::endl;
						p.set_value(ss.str());
						return;
					}

					int offset = 0;
					do
					{

						size_t written = fwrite(&buffer[offset], 1, num - offset, f);
						std::cout << "Server: File Writing to Buffer - " << offset << std::endl;
						if (written < 1) {
							ss << "Server: Error writing file to buffer";
							std::cerr << ss.str() << std::endl;
							p.set_value(ss.str());
							return;
						}
						offset += written;

					} while (offset < num);

					std::cout << "Server: Finished writing to buffer" << std::endl;
					filesize -= num;
				} while (filesize > 0);

				std::cout << "Server: File finished writing to buffer" << std::endl;
			}
			else
				std::cout << "Server: Empty File" << std::endl;

			ss << "File Recieved!";
			break;
		}

		// Return Value
		p.set_value(ss.str());

		// Clean up
		closesocket(hSocket);
		WSACleanup();
	}


	std::string SocketListener::Listen() {
		std::promise<std::string> p;
		auto f = p.get_future();
		std::thread t(&task_listen, std::move(p), _ip, _port);
		t.join();
		// Sleep(1000); return "Finished"; // Debugging
		return f.get();
	}

}