/*

	ClientInterface.cpp

	Implements the Client Interface for the C# application

	Steve Mahabir and Kevin Postma

	11/Dec/2015
*/

#include "stdafx.h"

#include "ClientInterface.h"

#include <msclr\marshal_cppstd.h>

namespace ClientInterface
{
	// Constructor
	ClientSocket::ClientSocket(System::String^ ip, unsigned port) {
		_ipaddress = ip;
		_port = port;
	}

	// Converters
	std::string convert(System::String^ input) {
		msclr::interop::marshal_context context;
		return context.marshal_as<std::string>(input);
	}
	
	// Converter (Overloaded)
	System::String^ convert(std::string input) {
		return gcnew System::String(input.c_str());
	}


	// Sends a message to the Server
	System::String^ ClientSocket::SendMessage(System::String^ message)
	{
		socklib::SocketSender s(convert(_ipaddress), _port);

		return convert(s.sendMessage(convert(message)).c_str());
	}

	// Sends a file to the Server
	bool ClientSocket::SendFile(System::String^ path, System::String^ filename) {

		socklib::SocketSender s(convert(_ipaddress), _port);

		return s.SendFile(convert(path),convert(filename));


	};


}
