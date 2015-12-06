// This is the main DLL file.

#include "stdafx.h"

#include "ServerInterface.h"

namespace ServerInterface
{
	System::String^ ServerSocket::RecieveMessage()
	{
		return gcnew System::String(socklib::SocketListener::startListening().c_str());
	}
}
