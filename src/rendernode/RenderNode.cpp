/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include "XipRenderTask.h"

#define publishServer(a, b)	
#define publishClient(a, b)	



// server function:
// from: http://support.microsoft.com/default.aspx?scid=kb;en-us;150523
// (Microsoft Knowledge Base Article - 150523, Socket inheritance on different Windows platforms)
//
// Note: The example on MSDN did not work the expected way (parent was blocked until child
//       terminated). Therefor an additional synchronization through hEvent has been added.
//		 Also, due to handle leakages in the example the handle is now duplicated in the
//		 child rather than the parent.
//
int server(const char *appl, int port)
{
	printf("server process %d started\n", ::GetCurrentProcessId());

	//
	// Need to create event to sync with child processes.
	//
	char eventName[40];
	sprintf(eventName, "renderNode_%d", ::GetCurrentProcessId());
	HANDLE hEvent = ::CreateEventA(NULL, TRUE, FALSE, eventName);
	if (!hEvent)
	{
		fprintf(stderr,"CreateEvent error %d\n", GetLastError());
		return -1;
	}

	//
	// Open socket for listening.
	//
	SOCKET listen_socket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listen_socket == INVALID_SOCKET)
	{
		fprintf(stderr,"socket error %d\n", GetLastError());
		return -1;
	}

	struct sockaddr_in serverInfo;
	memset((void*) &serverInfo, 0, sizeof serverInfo);
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_port = ::htons((unsigned short) port);
	serverInfo.sin_addr.s_addr = INADDR_ANY;
	if (::bind(listen_socket, (struct sockaddr*) &serverInfo, sizeof serverInfo) != 0)
	{
		fprintf(stderr,"bind error %d\n", GetLastError());
		return -1;
	}
	if (::listen(listen_socket, SOMAXCONN) != 0)
	{
		fprintf(stderr,"listen error %d\n", GetLastError());
		return -1;
	}


	// This is a Winsock server that is listening on a port.

	// When a client connects, the server spawns a child process and
	// passes the socket handle to the child.
	// The child can use this socket handle to interact with the
	// client and the parent is free to go back to waiting for
	// other clients to connect.

	SOCKADDR_IN from;
	int fromlen = sizeof(from);
	SOCKET OrigSock = 0;
	SOCKET DuplicateSock = 0;


	struct timeval timeOut;
	timeOut.tv_sec = 1;
	timeOut.tv_usec = 0;
	int resSelect;

	fd_set socketset;
	FD_ZERO(&socketset); 
	FD_SET(listen_socket, &socketset);
	
 
	while ((resSelect = select (0, &socketset, NULL, NULL, &timeOut)) != SOCKET_ERROR) 
	{
		if(resSelect == 0)
		{
			// MSG_ID: is the message id that the monitor in the DCF subscribes to 
			// "RENDERNODE_ALIVE" is the message that it designates as the heartbeat message
			publishServer(MSG_ID, "RENDERNODE_ALIVE");

			FD_SET(listen_socket, &socketset);
		}
		else
		{
			if((OrigSock = accept(listen_socket, (struct sockaddr *) &from, &fromlen)) != INVALID_SOCKET)
			{
				STARTUPINFOA si;
				memset(&si,0,sizeof(si));
				
 				PROCESS_INFORMATION pi;
 				char argbuf[256];
				char charIp[20];

				if (from.sin_family == AF_INET)
				{
					unsigned int ip = ntohl(from.sin_addr.S_un.S_addr);
					unsigned short clientPort = ntohs(from.sin_port);
					sprintf(charIp, "%d.%d.%d.%d:%d\0", (ip >> 24) & 0xff, (ip >> 16) & 0xff, (ip >> 8) & 0xff, ip & 0xff, clientPort);
					printf("Incoming connection request from: %s\n", charIp);
				}

			/*	BOOL bOptVal = TRUE;
				if (setsockopt(OrigSock, IPPROTO_TCP, TCP_NODELAY, (char*) &bOptVal, sizeof(BOOL)) == SOCKET_ERROR)
				{
					::OutputDebugStringA("Warning from ivtRemoteUtil: setsockopt() failed!\n");
				}
			*/


#if _DEBUG
//---------------------------------------------------------------
				//
				// Start rendering task.
				//

				//publish a message to say the client start
				publishClient(MSGCLIENT_ID, charIp);


				XipStreamSockets socketStream(OrigSock);		// socket connection
				XipStreamLengthPackage stream(&socketStream);	// add length info

				XipRenderTask renderTask(&stream);
				renderTask.run();

				//shut down the socket.say that no more data will be sent.
				if(shutdown(OrigSock, SD_SEND) == SOCKET_ERROR)
				{
					DWORD error = WSAGetLastError();
				}

				//publish a message to say the client stop
				publishClient(MSGCLIENT_ID+2, charIp);

				//
				// Close socket connection.
				//
				closesocket(OrigSock);


#else
//---------------------------------------------------------------
				// 
				// Reset event with which the child will signal it has duplicated the handle
				// so it is not closed prematurely.
				// 
				::ResetEvent(hEvent);

				// 
				// Spawn the child process.
				// The first command line argument (argv[1]) is the process ID.
				// The second command line argument (argv[2]) is the socket handle.
				// 
				sprintf(argbuf,"child %d %d %s", ::GetCurrentProcessId(), OrigSock, charIp);
				if (!(CreateProcessA(appl, argbuf, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)))
				{
					fprintf(stderr,"createprocess failed %d\n",GetLastError());
					return -1;
				}

				//
				// Need to close returned handles.
				//
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);

				// 
				// The parent needs to wait until the child is done with
				// duplicating the handle before closing it.
				// 
				::WaitForSingleObject(hEvent, INFINITE);

				//
				// The duplicated socket handle must be closed by the owner
				// process--the parent. Otherwise, socket handle leakage
				// occurs. On the other hand, closing the handle prematurely
				// would make the duplicated handle invalid in the child. In this
				// sample, we use WaitForSingleObject(hEvent, INFINITE) to
				// wait for the child.
				// 
				closesocket(OrigSock);
//---------------------------------------------------------------
#endif

			} //end if
		} //end if
	} //end while

	::CloseHandle(hEvent);

	return 0;
}



//---------------------------------------------------------
// child function:
// Duplicates the parent's handle given in the arguments and runs a radRenderTask
// instance.
//
int child(int parentPID, int parentHandle, char * ipAddress)
{
	int ret = 0;

	HANDLE hEvent = 0;
	HANDLE hProcess = 0;
	SOCKET hSocket = 0;

	try
	{
		//
		// Open child-parent synchronisation event.
		//
		char eventName[40];
		sprintf(eventName, "renderNode_%d", parentPID);

		hEvent = ::OpenEventA(EVENT_MODIFY_STATE, FALSE, eventName);
		if (!hEvent)
		{
			throw "OpenEvent";
		}

		//
		// Open parent process handle.
		//
		hProcess = ::OpenProcess(PROCESS_DUP_HANDLE, FALSE, parentPID);
		if (!hProcess)
		{
			throw "OpenProcess";
		}

		//
		// Duplicate socket handle from parent process to work with
		// the accepted connection. Note that DUPLICATE_CLOSE_SOURCE 
		// leaks handles in the parent, so we need to synchronize
		// manually.
		//
		hSocket = 0;
		if (!::DuplicateHandle(
					hProcess, (HANDLE) parentHandle,
					::GetCurrentProcess(), (HANDLE*) &hSocket,
					0, FALSE, DUPLICATE_SAME_ACCESS))
		{
			throw "DuplicateHandle";
		}
		
		//
		// Done duplicating the handle. Let the parent close the socket now.
		//
		::SetEvent(hEvent);

		//
		// Close handles that are no longer needed.
		//
		::CloseHandle(hEvent); hEvent = 0;
		::CloseHandle(hProcess); hProcess = 0;

		//
		// Start rendering task.
		//
		BOOL bOptVal = TRUE;
		if (setsockopt(hSocket, IPPROTO_TCP, TCP_NODELAY, (char*) &bOptVal, sizeof(BOOL)) == SOCKET_ERROR)
		{
			::OutputDebugStringA("Warning from ivtRemoteUtil: setsockopt() failed!\n");
		}


		//publish a message to say the client start
		publishClient(MSGCLIENT_ID, ipAddress);

		XipStreamSockets socketStream(hSocket);			// socket connection
		XipStreamLengthPackage stream(&socketStream);	// add length info

		XipRenderTask renderTask(&stream);
		renderTask.run();

		//shut down the socket.say that no more data will be sent.
		if(shutdown(hSocket, SD_SEND) == SOCKET_ERROR)
		{
			DWORD error = WSAGetLastError();
		}

		//
		// Close socket connection.
		//
		ret = closesocket(hSocket);
		hSocket = 0;

		//publish a message to say the client stop
		publishClient(MSGCLIENT_ID+2, ipAddress);

		printf("Closing connection request from: %s\n", ipAddress);

		return 0;
	}
	catch(char *errMsg)
	{
		//
		// Unlock the parent.
		//
		if (hEvent)
		{
			::SetEvent(hEvent);
			::CloseHandle(hEvent);
		}

		if (hProcess) ::CloseHandle(hProcess);
		if (hSocket) ::closesocket(hSocket);

		fprintf(stderr, "Caught exception in client() service routine.\n");
		fprintf(stderr, "error: %s, GetLastError: %d\n", errMsg, GetLastError());
		ret = -1;
	}
	catch(...)
	{
		//
		// Unlock the parent.
		//
		if (hEvent)
		{
			::SetEvent(hEvent);
			::CloseHandle(hEvent);
		}

		if (hProcess) ::CloseHandle(hProcess);
		//if (hSocket) ::closesocket(hSocket);

		fprintf(stderr, "Caught unknown exception in client() service routine.\n");

		ret = -1;
	}

	return ret;
}



// main function:
// Applications entry point for both server and child.
//

int main(int argc, char* argv[])
{
	//
	// Socket initialization (once per process).
	//
	WSADATA wsaData;
	if (::WSAStartup(0x0202, &wsaData) != 0)
	{
		fprintf(stderr,"WSAStartup error %d\n",GetLastError());
		return -1;
	}

	if ((argc > 3) && (strcmp(argv[0], "child") == 0))
	{
		return child(atoi(argv[1]), atoi(argv[2]), argv[3]);
	}
	else
	{
		return server(argv[0], 12121);
	}
}
