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

#ifndef XIPSTREAM_H
#define XIPSTREAM_H

const int XIP_STREAM_BUFFER_SIZE = 4 * 1024 * 1024;

// abstract base class for stream I/O
class XipStreamBase
{
public:
	virtual ~XipStreamBase();

	virtual int recv(char * buf, int len, int flags) = 0;
	virtual int send(const char * buf, int len, int flags) = 0;
};


// sockets stream I/O
class XipStreamSockets : public XipStreamBase
{
public:
	XipStreamSockets(int socket);

	virtual int recv(char * buf, int len, int flags);
	virtual int send(const char * buf, int len, int flags);

protected:
	int mSocket;
};


// stream module that adds length prefix before sending
// receiver waits for entire data in package before returning to caller
class XipStreamLengthPackage : public XipStreamBase
{
public:
	XipStreamLengthPackage(XipStreamBase *downStream, unsigned int sendBufferSize = XIP_STREAM_BUFFER_SIZE,
		unsigned int recvBufferSize = XIP_STREAM_BUFFER_SIZE);
	virtual ~XipStreamLengthPackage();

	virtual int recv(char * buf, int len, int flags);
	virtual int send(const char * buf, int len, int flags);

protected:
	XipStreamBase *mStream;
	char *mSendBuffer;
	char *mRecvBuffer;
	unsigned int mSendBufferSize;
	unsigned int mRecvBufferSize;
	unsigned int mRecvBufferUsed;
};


#endif // XIPSTREAM_H
