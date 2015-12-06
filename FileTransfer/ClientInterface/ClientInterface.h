// ClientInterface.h

#pragma once

#include <string>

using namespace System;

namespace ClientInterface {

	public ref class ClientSocket
	{
	public:
		

		static void SendMessage();

		static std::string testing_method();

		static int testing_method_2();

		static System::String^ testing_method_3();
	};
}
