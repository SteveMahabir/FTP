// This is the main DLL file.

#include "stdafx.h"

#include "ServerInterface.h"

namespace ServerInterface
{
	ServerSocket::ServerSocket(System::String^ ip, unsigned port) {
		_ipaddress = ip;
		_port = port;
	}

	bool readdata(SOCKET sock, void *buf, int buflen)
	{
		char *pbuf = (char *)buf;

		while (buflen > 0)
		{
			int num = recv(sock, pbuf, buflen, 0);
			if (num == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					// optional: use select() to check for timeout to fail the read
					continue;
				}
				return false;
			}
			else if (num == 0)
				return false;

			pbuf += num;
			buflen -= num;
		}

		return true;
	}

	bool readlong(SOCKET sock, long *value)
	{
		if (!readdata(sock, value, sizeof(value)))
			return false;
		*value = ntohl(*value);
		return true;
	}

	bool readfile(SOCKET sock, FILE *f)
	{
		long filesize;
		if (!readlong(sock, &filesize))
			return false;
		if (filesize > 0)
		{
			char buffer[1024];
			do
			{
				int num = min(filesize, sizeof(buffer));
				if (!readdata(sock, buffer, num))
					return false;
				int offset = 0;
				do
				{
					size_t written = fwrite(&buffer[offset], 1, num - offset, f);
					if (written < 1)
						return false;
					offset += written;
				} while (offset < num);
				filesize -= num;
			} while (filesize > 0);
		}
		return true;
	}

	void RecieveFile() {
		FILE *filehandle = fopen("imagefile.jpg", "wb");
		//if (filehandle != NULL);
		//{
		//	//bool ok = readfile(, filehandle);
		//	fclose(filehandle);
		//	
		//	//if (ok)
		//	{
		//		// use file as needed...
		//	}
		//	else
		//		remove("imagefile.jpg");
		//	}
	}
}
