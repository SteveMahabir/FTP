// This is the main DLL file.

#include "stdafx.h"

#include "ServerInterface.h"

namespace ServerInterface
{
	// Converters
	std::string convert(System::String^ input) {
		msclr::interop::marshal_context context;
		return context.marshal_as<std::string>(input);
	}
	System::String^ convert(std::string input) {
		return gcnew System::String(input.c_str());
	}


	// This class is used for Threading the Socket Listener
	ref class TaskListener
	{
	private:
		System::String^ return_message;
		System::String^ _ip_address;
		unsigned _port;
		// constructor to initialize a MessagePrinter object
	public:


		TaskListener(System::String^ ip, unsigned port)
		{
			_ip_address = ip;
			_port = port;
		}

		//controls Thread that prints message
		void ListenForMessages()
		{
			// obtain reference to currently executing thread
			Thread^ current = Thread::CurrentThread;

			Console::WriteLine(current->Name + " started");
			socklib::SocketListener socketlistener(convert(_ip_address), _port);
			return_message = convert(socketlistener.ListenForMessage());

			Console::WriteLine(current->Name + " finished");

		} // end method Print

		  //controls Thread that prints message
		void ListenForFiles()
		{
			// obtain reference to currently executing thread
			Thread^ current = Thread::CurrentThread;

			Console::WriteLine(current->Name + " started");

			socklib::SocketListener socketlistener(convert(_ip_address), _port);
			return_message = convert(socketlistener.ListenForFile());

			Console::WriteLine(current->Name + " finished");

		} // end method Print

		System::String^ getLastMessage() {
			return return_message;
		}

	}; // end class MessagePrinter  




	ServerSocket::ServerSocket(System::String^ ip, unsigned port) {
		_ipaddress = ip;
		_port = port;
	}


	System::String^ ServerSocket::RecieveMessage() {

		// Create and name each thread. Use MessagePrinter's
		// Print method as argument to ThreadStart delegate.
		TaskListener^ listener = gcnew TaskListener(_ipaddress, _port);
		Thread^ thread1 = gcnew Thread(gcnew ThreadStart(listener, &TaskListener::ListenForMessages));
		thread1->Name = "thread1";


		Console::WriteLine("Starting thread");

		thread1->Start();

		Console::WriteLine("Thread started\n");


		thread1->Join();

		return listener->getLastMessage();
	}

	System::String^ ServerSocket::RecieveFile() {
		
		// Create and name each thread. Use MessagePrinter's
		// Print method as argument to ThreadStart delegate.
		TaskListener^ listener = gcnew TaskListener(_ipaddress, _port);
		Thread^ thread1 = gcnew Thread(gcnew ThreadStart(listener, &TaskListener::ListenForFiles));
		thread1->Name = "thread1";


		Console::WriteLine("Starting thread");

		thread1->Start();

		Console::WriteLine("Thread started\n");


		thread1->Join();

		return listener->getLastMessage();

	}
}
