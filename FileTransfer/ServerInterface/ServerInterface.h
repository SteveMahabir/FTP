// ServerInterface.h

#pragma once

using namespace System;
using namespace System::Threading;


#include <msclr\marshal_cppstd.h>

namespace ServerInterface {

	public ref class ServerSocket
	{
	private:
		System::String^ _ipaddress;
		unsigned _port;

	public:

		ServerSocket(System::String^ ip, unsigned port);

		System::String^ Recieve();
	};


}
