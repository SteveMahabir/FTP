// ServerInterface.h

#pragma once

using namespace System;
using namespace System::Threading;


namespace ServerInterface {

	ref class MessagePrinter
	{
	private:
		System::String^ return_message;

		// constructor to initialize a MessagePrinter object
	public:


		MessagePrinter()
		{

		}

		//controls Thread that prints message
		void Print()
		{
			// obtain reference to currently executing thread
			Thread^ current = Thread::CurrentThread;

			Console::WriteLine(current->Name + " started");
			return_message = gcnew System::String(


				socklib::SocketListener::startListening().c_str()

				);

			Console::WriteLine(current->Name + " finished");

		} // end method Print
	}; // end class MessagePrinter  



	public ref class ServerSocket
	{



	public:
		static System::String^ RecieveMessage();

		static System::String^ task_runner() {
			// Create and name each thread. Use MessagePrinter's
			// Print method as argument to ThreadStart delegate.
			MessagePrinter^ printer1 = gcnew MessagePrinter();
			Thread^ thread1 = gcnew Thread(gcnew ThreadStart(printer1, &MessagePrinter::Print));
			thread1->Name = "thread1";


			Console::WriteLine("Starting threads");
			// call each thread's Start method to place each
			// thread in Started state
			thread1->Start();

			Console::WriteLine("Threads started\n");
			thread1->Join();

			return gcnew System::String("Message Recieved");
		}


	};


}
