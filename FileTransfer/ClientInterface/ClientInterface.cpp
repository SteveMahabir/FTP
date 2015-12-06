// This is the main DLL file.

#include "stdafx.h"

#include "ClientInterface.h"

namespace ClientInterface
{
	void ClientSocket::SendMessage()
	{
		socklib::SocketSender::sendMessage();
	}

	std::string ClientSocket::testing_method() 
	{
		return "Working";
	}

	int ClientSocket::testing_method_2()
	{
		return EXIT_SUCCESS;
	}

	System::String^ ClientSocket::testing_method_3() 
	{
		return gcnew System::String("Working");
	}
}
