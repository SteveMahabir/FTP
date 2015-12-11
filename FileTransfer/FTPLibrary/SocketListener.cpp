/*
	SocketListener.cpp

	Implementation of the Server.
	Since this is a library users should never see this code

	Steve Mahabir and Kevin Postma

	11/Dec/2015
*/

#include "ServerSocket.h"

#include <thread>
#include <future>
#include <sstream>

namespace socklib
{
	// Only Constructor
	SocketListener::SocketListener(std::string ipaddress, unsigned port, std::string save_directory) {
		_ip = ipaddress;
		_port = port;
		_directory = save_directory;
	};

	SocketListener::~SocketListener() {
		// Clean up resources here
		closesocket(hSocket);
		WSACleanup();
	}
	
	// Reads a pre-determined amount of file information
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

	// Calls Read Data for reading a pre-determined amount of file information to the buffer
	bool readlong(SOCKET sock, long *value)
	{
		if (!readdata(sock, value, sizeof(value)))
			return false;
		*value = ntohl(*value);
		return true;
	}


	// Function Task - Task that is threaded to ensure ASYNC calls
	void task_listen(std::promise<std::string> && p, std::string ip, unsigned port, std::string directory) {

		// Return Value
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

		// Listen for Client connection
		if (listen(hSocket, 1) == SOCKET_ERROR) {
			closesocket(hSocket);
			WSACleanup();
			p.set_value("Server: Error listening on socket");
			return;
		}

		std::cout << "Server: Waiting for connection\n";

		//  Accept the Connection
		SOCKET hAccepted = SOCKET_ERROR;
		while (hAccepted == SOCKET_ERROR) {
			hAccepted = accept(hSocket, NULL, NULL);
		}
		std::cout << "Server: Client connected\n";


		// Receive Socket Identifier
		int messageIdentifer;
		int bytesRecv = recv(hAccepted, (char*)&messageIdentifer, 4, 0);
		std::cout << "Server: Message Identifier Recieved [" << bytesRecv << "]: " << messageIdentifer << std::endl;


		// These Memebers for Message Receival - Prefer to declare outside of switch
		char receivedMessage[32] = "";
		int confirmationMessageSent;
		int messageBufferSize;
		char sendbuf[32] = "Thank you for the message!";

		// Choose what to listen to based on task received
		switch (messageIdentifer)
		{

			// Message Found
		case SocketListener::Type::MESSAGES:
			std::cout << "Server: Recieved Message Transfer Request" << std::endl;

			// Receive Message
			messageBufferSize = recv(hAccepted, receivedMessage, 32, 0);
			std::cout << "Server: Recieved Message [" << messageBufferSize << "]: " << receivedMessage << std::endl;

			// Set the return string with the message received
			ss << "[msg] " << receivedMessage;

			// Send the Confirmation of Receival
			confirmationMessageSent = send(hAccepted, sendbuf, strlen(sendbuf) + 1, 0);
			std::cout << "Sent = " << confirmationMessageSent << " bytes" << std::endl;

			break;

			// File Found
		case SocketListener::Type::FILES:
			std::cout << "Server: Recieved File Transfer Request" << std::endl;

			// Receive Filesize
			int fsize;
			int filesize_buffer = recv(hAccepted, (char*)& fsize, 4, 0);
			std::cout << "Server: Recieved Filename Size [" << filesize_buffer << "]: " << fsize << std::endl;

			// Receive Message
			char* filename = new char[fsize + 1];
			int filename_buffer = recv(hAccepted, filename, fsize + 1, 0);
			std::cout << "Server: Recieved Filename [" << filename_buffer << "]: " << filename << std::endl;



			// Somewhere to put the file!
			std::string file = directory + "\\" + filename;
			FILE *f = fopen(file.c_str(), "wb");
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

			// File size is greater than 0
			if (filesize > 0)
			{
				std::cout << "Server: filesize > 0" << std::endl;
				char buffer[1024];

				do
				{
					// Validate and prepare for filesize
					int num = min(filesize, sizeof(buffer));
					std::cout << "Server: FileSize = " << num << std::endl;

					// Start getting the first set of data
					if (!readdata(hAccepted, buffer, num)) {
						ss << "Server: Error reading file";
						std::cerr << ss.str() << std::endl;
						p.set_value(ss.str());
						return;
					}

					int offset = 0;
					do
					{
						// Start receiving a bit of data at a time
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
					
					// Finished
					std::cout << "Server: Finished writing to buffer" << std::endl;
					filesize -= num;
				} while (filesize > 0);

				// Close
				fclose(f);
				std::cout << "Server: File finished writing to buffer" << std::endl;
			}
			else
				std::cout << "Server: Empty File" << std::endl;
			
			// Return File
			ss << "File Recieved!";
			break;
		}

		// Return Value
		p.set_value(ss.str());

		// Clean up
		closesocket(hSocket);
		WSACleanup();
	}


	// Threaded Task Listener
	std::string SocketListener::Listen() {
		std::promise<std::string> p;
		auto f = p.get_future();
		std::thread t(&task_listen, std::move(p), _ip, _port, _directory);
		t.join();
		// Sleep(1000); return "Finished"; // Debugging
		return f.get();
	}

}