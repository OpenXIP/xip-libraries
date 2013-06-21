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
#include <xip/inventor/remote/XipStream.h>

#if defined(WINDOWS) || defined(_WIN32)
	#include <winsock2.h>
#else
	#include <string.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <sys/uio.h>
	#include <unistd.h>
	#include <errno.h>
	#include <netdb.h>
#endif

// XipStreamBase
XipStreamBase::~XipStreamBase()
{
}


// XipStreamSockets
XipStreamSockets::XipStreamSockets(int socket)
 : XipStreamBase()
{
	mSocket = socket;
}

int XipStreamSockets::recv(char * buf, int len, int flags)
{
	return ::recv(mSocket, buf, len, flags);
}

int XipStreamSockets::send(const char * buf, int len, int flags)
{
	return ::send(mSocket, buf, len, flags);
}


// XipStreamLengthPackage
XipStreamLengthPackage::XipStreamLengthPackage(XipStreamBase *downStream, unsigned int sendBufferSize, unsigned int recvBufferSize)
 : XipStreamBase(), mSendBuffer(NULL), mRecvBuffer(NULL)
{
	mStream = downStream;
	mSendBufferSize = 0;
	mRecvBufferSize = 0;
	mRecvBufferUsed = 0;

	mSendBuffer = new char[sendBufferSize];
	if (!mSendBuffer)
	{
		//printf("MEMORY_HEAP_ERROR!\n");
        return;
	}
	mSendBufferSize = sendBufferSize;

	mRecvBuffer = new char[recvBufferSize];
	if (!mRecvBuffer)
	{
		//printf("MEMORY_HEAP_ERROR!\n");
        return;
	}
	mRecvBufferSize = recvBufferSize;
}

XipStreamLengthPackage::~XipStreamLengthPackage()
{
	if (mSendBuffer)
	{
		delete [] mSendBuffer;
	}

	if (mRecvBuffer)
	{
		delete [] mRecvBuffer;
	}
}

int XipStreamLengthPackage::recv(char * buf, int len, int flags)
{
	int length = 0, received = 0, i = 0;
    int this_can_be_improved;

	if (mRecvBufferUsed >= sizeof(int))
	{
		int length = ((int*) mRecvBuffer)[0];
		length = ntohl(length);
		if (length > len)
		{
			return -1;
		}

		if ((length + sizeof(int)) > mRecvBufferUsed)
		{
			// incomplete package
			received = mStream->recv(mRecvBuffer + mRecvBufferUsed, mRecvBufferSize - mRecvBufferUsed, flags);
		}
		else
		{
			// everything is already in buffer
			char *readPtr = mRecvBuffer + sizeof(int);

			memcpy(buf, readPtr, length);
			readPtr += length;

			i = 0;
			while (readPtr < (mRecvBuffer + mRecvBufferUsed))
			{
				mRecvBuffer[i++] = *readPtr++;
			}
			mRecvBufferUsed = i;

			return length;
		}
	}
	else
	{
		received = mStream->recv(mRecvBuffer + mRecvBufferUsed, mRecvBufferSize - mRecvBufferUsed, flags);
	}

	// get as much as we can hold
	if (received > 0)
	{
		mRecvBufferUsed += received;

		int length = ((int*) mRecvBuffer)[0];
		length = ntohl(length);

		if (length > len)
		{
			return -1;
		}

		// keep receiving until we got the entire buffer
		while ((mRecvBufferUsed - sizeof(int)) < (unsigned int) length)
		{
			received = mStream->recv(mRecvBuffer + mRecvBufferUsed, mRecvBufferSize - mRecvBufferUsed, flags);
			mRecvBufferUsed += received;
		}

		char *readPtr = mRecvBuffer + sizeof(int);

		memcpy(buf, readPtr, length);
		readPtr += length;

		i = 0;
		while (readPtr < (mRecvBuffer + mRecvBufferUsed))
		{
			mRecvBuffer[i++] = *readPtr++;
		}
		mRecvBufferUsed = i;

		return length;
	}

	return received;
}

int XipStreamLengthPackage::send(const char * buf, int len, int flags)
{
	// mSendBufferSize initialized by constructor
	if (mSendBufferSize < (len + sizeof(int)))
	{
		return -1;
	}

	// create package with length first and then the data

	// The htonl function converts a u_long from host to 
	// TCP/IP network byte order (which is big endian).
	((int*) mSendBuffer)[0] = htonl(len);
	memcpy(mSendBuffer + sizeof(int), buf, len);

	int length = mStream->send(mSendBuffer, len + sizeof(int), flags);

	if (length > sizeof(int))
	{
		length -= sizeof(int);
	}

	return length;
}
