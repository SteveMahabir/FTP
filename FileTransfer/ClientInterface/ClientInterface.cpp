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


	void ClientSocket::SendMessage()
	{
		msclr::interop::marshal_context context;
		std::string standardString = context.marshal_as<std::string>(_ipaddress);
		socklib::SocketSender s(standardString, _port);
		s.sendMessage();
	}

}
