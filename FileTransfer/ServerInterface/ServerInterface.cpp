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
		System::String^ _save_directory;
		// constructor to initialize a MessagePrinter object
	public:


		TaskListener(System::String^ ip, unsigned port, System::String^ save_directory)
		{
			_ip_address = ip;
			_port = port;
			_save_directory = save_directory;
		}

		// Controls the Thread that listens for client sending
		void Listen()
		{
			// obtain reference to currently executing thread
			Thread^ current = Thread::CurrentThread;

			Console::WriteLine(current->Name + " started");
			socklib::SocketListener socketlistener(convert(_ip_address), _port, convert(_save_directory));
			
			return_message = convert(socketlistener.Listen());

			Console::WriteLine(current->Name + " finished");

		} // end method Print

		System::String^ getLastMessage() {
			return return_message;
		}

	}; // end class MessagePrinter  




	ServerSocket::ServerSocket(System::String^ ip, unsigned port, System::String^ save_directory) {
		_ipaddress = ip;
		_port = port;
		_directory = save_directory;
	}


	System::String^ ServerSocket::Recieve() {

		// Create and name each thread. Use MessagePrinter's
		// Print method as argument to ThreadStart delegate.
		TaskListener^ listener = gcnew TaskListener(_ipaddress, _port, _directory);
		Thread^ thread1 = gcnew Thread(gcnew ThreadStart(listener, &TaskListener::Listen));
		thread1->Name = "ThreadListener";


		Console::WriteLine("Starting ThreadListener");

		thread1->Start();

		Console::WriteLine("ThreadListener started\n");


		thread1->Join();

		return listener->getLastMessage();
	}

}
