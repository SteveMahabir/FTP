// ClientInterface.h

#pragma once

#include <string>


using namespace System;

namespace ClientInterface {

	public ref class ClientSocket
	{

	private:
		System::String^ _ipaddress;
		unsigned _port;

	public:
		ClientSocket(System::String^ ip, unsigned port);

		System::String^ SendMessage(System::String^ message);
		
		bool SendFile(System::String^ path, System::String^ filename );
	};
}
