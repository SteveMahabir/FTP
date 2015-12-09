// This is the main DLL file.

#include "stdafx.h"

#include "ClientInterface.h"

#include <msclr\marshal_cppstd.h>

namespace ClientInterface
{

	ClientSocket::ClientSocket(System::String^ ip, unsigned port) {
		_ipaddress = ip;
		_port = port;
	}

	// Converters
	std::string convert(System::String^ input) {
		msclr::interop::marshal_context context;
		return context.marshal_as<std::string>(input);
	}
	System::String^ convert(std::string input) {
		return gcnew System::String(input.c_str());
	}



	System::String^ ClientSocket::SendMessage(System::String^ message)
	{
		msclr::interop::marshal_context context;
		std::string standardString = context.marshal_as<std::string>(_ipaddress);
		socklib::SocketSender s(convert(_ipaddress), _port);

		return convert(s.sendMessage(convert(message)).c_str());
	}

	bool ClientSocket::SendFile(System::String^ filename) {

		socklib::SocketSender s(convert(_ipaddress), _port);

		return s.SendFile(convert(filename));


	};


}
