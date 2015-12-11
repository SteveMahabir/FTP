/*
ServerInterface.h

Header file for the DLL Common langauge Runtime used by the C# Application

Steve Mahabir and Kevin Postma

11/Dec/2015
*/

#pragma once

using namespace System;
using namespace System::Threading;

#include <msclr\marshal_cppstd.h>

namespace ServerInterface {

	// Server Socket used to link the C# GUI to the .LIB
	public ref class ServerSocket
	{
	private:
		// Data Members
		System::String^ _ipaddress;
		unsigned _port;
		System::String^ _directory;

	public:
		// Constructor
		ServerSocket(System::String^ ip, unsigned port, System::String^ save_directory);
		
		// Main Receiver
		System::String^ Recieve();
	};


}
