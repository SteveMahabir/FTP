// ServerInterface.h

#pragma once

using namespace System;
using namespace System::Threading;


#include <msclr\marshal_cppstd.h>

namespace ServerInterface {

	ref class MessageListener
	{
	private:
		System::String^ return_message;
		System::String^ _ip_address;
		unsigned _port;
		// constructor to initialize a MessagePrinter object
	public:


		MessageListener(System::String^ ip, unsigned port)
		{
			_ip_address = ip;
			_port = port;
		}

		//controls Thread that prints message
		void Listen()
		{
			// obtain reference to currently executing thread
			Thread^ current = Thread::CurrentThread;

			Console::WriteLine(current->Name + " started");

			msclr::interop::marshal_context context;
			std::string standardString = context.marshal_as<std::string>(_ip_address);

			socklib::SocketListener s(standardString, _port);
			return_message = gcnew System::String(
				
				// Listen !!!				
				s.startListening().c_str()

				);

			Console::WriteLine(current->Name + " finished");

		} // end method Print



	}; // end class MessagePrinter  



	public ref class ServerSocket
	{
	private:
		System::String^ _ipaddress;
		unsigned _port;

	public:

		ServerSocket(System::String^ ip, unsigned port);

		System::String^ task_runner() {
			
			// Create and name each thread. Use MessagePrinter's
			// Print method as argument to ThreadStart delegate.
			MessageListener^ listener = gcnew MessageListener(_ipaddress, _port);
			Thread^ thread1 = gcnew Thread(gcnew ThreadStart(listener, &MessageListener::Listen));
			thread1->Name = "thread1";


			Console::WriteLine("Starting thread");
			
			thread1->Start();

			Console::WriteLine("Thread started\n");
			

			thread1->Join();

			return gcnew System::String("Message Recieved");
		}

		bool RecieveFile() {
			msclr::interop::marshal_context context;
			std::string standardString = context.marshal_as<std::string>(_ipaddress);

			socklib::SocketListener s(standardString, _port);

			// Recieve File
			return s.ReadFile();

		}
	};


}
