/*

	ClientInterface.h

	Header file for the DLL Common langauge Runtime used by the C# Application

	Steve Mahabir and Kevin Postma

	11/Dec/2015

*/


#pragma once

#include <string>


using namespace System;

namespace ClientInterface {

	public ref class ClientSocket
	{

	private:
		// Data Member
		System::String^ _ipaddress;
		unsigned _port;

	public:
		// Constructor
		ClientSocket(System::String^ ip, unsigned port);

		// Used for Sending a message to the Server
		System::String^ SendMessage(System::String^ message);
		
		// Used for Sending a File to the Server
		bool SendFile(System::String^ path, System::String^ filename );
	};
}
