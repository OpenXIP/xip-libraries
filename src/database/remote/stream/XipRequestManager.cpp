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
#include <xip/inventor/remote/xipRequestManager.h>

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

	#if defined(__APPLE__) && defined(__MACH__)
		#include <machine/endian.h>
	#else
		#include "endian.h"
	#endif

#endif

#include <memory.h>


#if _DEBUGINFILE__
#include <fstream>
#endif

#define SIZESEPARATOR 2


// --------------------------------------------------------------------------
//! Constructor
// --------------------------------------------------------------------------
RequestTreeElement::RequestTreeElement()
: mFirstChildElement(0),
mNextElement(0)
{
	this->init();
}

// --------------------------------------------------------------------------
//! Constructor with ID
// --------------------------------------------------------------------------
RequestTreeElement::RequestTreeElement(short ID)
: mFirstChildElement(0),
mNextElement(0)
{
	this->init(ID);
}

// --------------------------------------------------------------------------
//! Constructor with a buffer
// --------------------------------------------------------------------------
RequestTreeElement::RequestTreeElement(short ID, int Size, char * Buf)
: mFirstChildElement(0),
mNextElement(0)
{
	this->init(ID, Size, Buf);
}


// --------------------------------------------------------------------------
//! method used for element initialization
// --------------------------------------------------------------------------
void RequestTreeElement::init(short ID, int Size, char * Buf)
{
	mElementID = ID;
	mBufferSize = Size;
	mBuffer = Buf;
	mSizeForWritting = 0;
    mFirstChildElement = 0;
    mNextElement = 0;
}

// --------------------------------------------------------------------------
//! method used to add a element at the same level of the tree than the current element
// --------------------------------------------------------------------------
void RequestTreeElement::addElement(RequestTreeElement * Element)
{
	//recursive function looking for a NULL pointer of an element to attach the new one 
	
	if(mNextElement == NULL)
	{
		mNextElement = Element;
	}
	else
	{
		mNextElement->addElement(Element);
	}
}

// --------------------------------------------------------------------------
//! method used to add a element as a child of the current element
// --------------------------------------------------------------------------
void RequestTreeElement::addChildElement(RequestTreeElement * Element)
{
	//recursive function looking for a NULL pointer of a child element to attach the new one 

	if(mFirstChildElement == NULL)
	{
		mFirstChildElement = Element;
	}
	else
	{
		mFirstChildElement->addElement(Element);
	}
}

// --------------------------------------------------------------------------
//! return the first child of the current element
// --------------------------------------------------------------------------
RequestTreeElement * RequestTreeElement::getFirstChildElement()
{
	return mFirstChildElement;
}

// --------------------------------------------------------------------------
//! return the element next to the current one
// --------------------------------------------------------------------------
RequestTreeElement * RequestTreeElement::getNextElement()
{
	return mNextElement;
}

// --------------------------------------------------------------------------
//! search for the element with identifiant ID in the tree
//! return the element if it's itself or one of the childs, NULL else
// --------------------------------------------------------------------------
RequestTreeElement * RequestTreeElement::getElement(short ID)
{
	//recursive function testing the ID on itself, then his children then his neighbor	
	
	if(mElementID == ID)
		return this;

	if(mFirstChildElement)
	{
		RequestTreeElement * cE = mFirstChildElement->getElement(ID);
		if(cE)
			return cE;
	}

	if(mNextElement)
	{
		RequestTreeElement * nE = mNextElement->getElement(ID);
		if(nE)
			return nE;
	}

	return NULL;
}

// --------------------------------------------------------------------------
//! calculate the needed place to write the element in a buffer
// --------------------------------------------------------------------------
int RequestTreeElement::calculateSizeForWritting()
{
	mSizeForWritting = 0;
	RequestTreeElement * elt = getFirstChildElement();

	while(elt)
	{
		mSizeForWritting += elt->calculateSizeForWritting();
		elt = elt->getNextElement();
	}

	mSizeForWritting += mBufferSize;

	// return the size used to the element to be writen into a buffer
	// including the element header ('OP' + identifiant + size)
	return mSizeForWritting + SIZESEPARATOR + sizeof(short) + sizeof(int);
}




// --------------------------------------------------------------------------
//! Constructor with a stream
// --------------------------------------------------------------------------
XipTreeRequestManager::XipTreeRequestManager(XipStreamBase *Stream)
: mStream(0),
mSocketBuffer(0)
{
	mStream = Stream;
	mSocketBuffer = new char[XIP_STREAM_BUFFER_SIZE];
	if (!mSocketBuffer)
	{
		//throw RadException(__LINE__, __FILE__, RadException::MEMORY_HEAP_ERROR);
		return;
	}
	this->init();
}



// --------------------------------------------------------------------------
//! return a pointer on the element giving the ID
// --------------------------------------------------------------------------
RequestTreeElement * XipTreeRequestManager::getElement(short ElementID)
{
	// test if the element is not in the cache, then call the search
	//function getElement
	
	if(mLastUsedElement && mLastUsedElement->mElementID == ElementID)
		return mLastUsedElement;

	RequestTreeElement * ptr = mTabElements;
	if(!ptr)
		return NULL;

	int eltID = ptr->mElementID;

	for(int i=0; i<nbUsedElement; i++)
	{
		if(eltID == ElementID)
		{
			mLastUsedElement = ptr;
			return mLastUsedElement;
		}

		++ptr;
		eltID = ptr->mElementID;	
	}

	return NULL;
}

// --------------------------------------------------------------------------
//! method used to init the tree
// --------------------------------------------------------------------------
void XipTreeRequestManager::init()
{
	mPtrTabElement = mTabElements;
	mLastUsedElement = NULL;
	mPtrTabElement->init();
	nbUsedElement = 0;
}



// --------------------------------------------------------------------------
//! Constructor
// --------------------------------------------------------------------------
XipTreeRequestSender::XipTreeRequestSender() : XipTreeRequestManager(NULL) 
{
}

// --------------------------------------------------------------------------
//! Constructor with a stream and the request ID
// --------------------------------------------------------------------------
XipTreeRequestSender::XipTreeRequestSender(XipStreamBase *Stream, short IDRequest) : XipTreeRequestManager(NULL)
{
	initSender(Stream, IDRequest);
}


// --------------------------------------------------------------------------
//! init the request  with a stream and the request ID
// --------------------------------------------------------------------------
void XipTreeRequestSender::initSender(XipStreamBase *Stream, short IDRequest)
{
	init();
	mStream = Stream;
	mTabElements->init(IDRequest);
	nbUsedElement++;
}

// --------------------------------------------------------------------------
//! Add a new element to the request as the next element of toElementID in the tree
// --------------------------------------------------------------------------
void XipTreeRequestSender::addNextElement(short ToElementID, short NewElementID, int NewElementSize, void * NewElementBuffer)
{
	RequestTreeElement * tmp = getElement(ToElementID);
	if(tmp)
	{
		nbUsedElement++;
		if(nbUsedElement > MAX_TREE_ELEMENTS)
		{
			//throw RadException(__LINE__, __FILE__, RadException::INTERNAL_SYSTEM_ERROR, L"Tree request full, can't add element");
			return;
		}

		RequestTreeElement * newElt = ++mPtrTabElement;
		newElt->init(NewElementID, NewElementSize, (char *)NewElementBuffer);
		tmp->addElement(newElt);

		mLastUsedElement = newElt;		
	}
}

// --------------------------------------------------------------------------
//! Add a new element to the request as the child element of toElementID in the tree
// --------------------------------------------------------------------------
void XipTreeRequestSender::addChildElement(short ToElementID, short NewElementID, int NewElementSize, void * NewElementBuffer)
{
	RequestTreeElement * tmp = getElement(ToElementID);
	if(tmp)
	{
		nbUsedElement++;
		if(nbUsedElement > MAX_TREE_ELEMENTS)
		{
			//throw RadException(__LINE__, __FILE__, RadException::INTERNAL_SYSTEM_ERROR, L"Tree request full, can't add element");
			return;
		}

		RequestTreeElement * newElt = ++mPtrTabElement;
		newElt->init(NewElementID, NewElementSize, (char *)NewElementBuffer);
		tmp->addChildElement(newElt);
	}
}

// --------------------------------------------------------------------------
//! Change the content of an element
// --------------------------------------------------------------------------
bool XipTreeRequestSender::changeElementContent(short ElementID, void * NewElementBuffer)
{
	RequestTreeElement * tmp = getElement(ElementID);
	if(tmp)
	{
		if(NewElementBuffer)
			tmp->mBuffer = (char *)NewElementBuffer;

		return true;
	}

	return false;
}


// --------------------------------------------------------------------------
//! method used to send the request
// --------------------------------------------------------------------------
void XipTreeRequestSender::send()
{
	//allow the memory buffer to be sent, then call "writeElementToBuffer" to this buffer
	
	if(!mStream)
		return;

	int sent;

	int sendBufSize = mTabElements->calculateSizeForWritting();		

	if(sendBufSize > XIP_STREAM_BUFFER_SIZE)
    {
        //throw RadException(__LINE__, __FILE__, RadException::INTERNAL_SYSTEM_ERROR, L"Request too big to be send");
        return;
    }
	

	writeElementToBuffer(mSocketBuffer, mTabElements);


	sent = mStream->send(mSocketBuffer, sendBufSize, 0);
	if(sent != sendBufSize)
	{
		//throw RadException(__LINE__, __FILE__, RadException::COMM_ERROR, L"Communication error (invalid size of request sent)");
        return;
	}

}

// --------------------------------------------------------------------------
//! method to give the request containing in a buffer
// --------------------------------------------------------------------------
char * XipTreeRequestSender::getBuffer(int &sizeBuffer)
{
	sizeBuffer = mTabElements->calculateSizeForWritting();		

	if(sizeBuffer > XIP_STREAM_BUFFER_SIZE)
    {
	    //throw RadException(__LINE__, __FILE__, RadException::INTERNAL_SYSTEM_ERROR, L"Request too big to be send");
        return NULL;
    }

	writeElementToBuffer(mSocketBuffer, mTabElements);

	return mSocketBuffer;
}

// --------------------------------------------------------------------------
//! write an element and all the child to the buffer starting at the given pointer
// --------------------------------------------------------------------------
char * XipTreeRequestSender::writeElementToBuffer(char * PtrBuffer, RequestTreeElement * Element)
{
	//! recursive function, writing itself to the buffer, then the childs, then after the neighbor
	//! then finish with a end flag of the ID element  

	if(!Element || !PtrBuffer)
		return NULL;

	short htoId = htons(Element->mElementID); 
	int htoSize = htonl(Element->mSizeForWritting); 

	memcpy(PtrBuffer, "OP", 2*sizeof(char));
	PtrBuffer += 2*sizeof(char);

	memcpy(PtrBuffer, &htoId, sizeof(short));
	PtrBuffer += sizeof(short);

	memcpy(PtrBuffer, &htoSize, sizeof(int));
	PtrBuffer += sizeof(int);

	RequestTreeElement * elt = Element->getFirstChildElement();
	while(elt)
	{
		PtrBuffer = writeElementToBuffer(PtrBuffer, elt);
		elt = elt->getNextElement();
	}

//	if(Element->getFirstChildElement())
//		PtrBuffer = writeElementToBuffer(PtrBuffer, Element->getFirstChildElement());

	
	if(Element->mBuffer != NULL)
	{
		memcpy(PtrBuffer, Element->mBuffer, Element->mBufferSize);
		PtrBuffer += Element->mBufferSize;
	}


//	if(Element->getNextElement())
//		PtrBuffer = writeElementToBuffer(PtrBuffer, Element->getNextElement());


	return PtrBuffer;
}


// --------------------------------------------------------------------------
//! method used to receive the request
// --------------------------------------------------------------------------
//! init the request  with a stream
void XipTreeRequestReceiver::initReceiver(XipStreamBase *Stream)
{
	init();
	mStream = Stream;
}

// --------------------------------------------------------------------------
//! method used to receive the request
// --------------------------------------------------------------------------
void XipTreeRequestReceiver::receive()
{
	// receive the buffer, then call the function readElementFromBuffer to
	// read the tree from it

	int sizeRecBuf = 0;

	init();

	sizeRecBuf = mStream->recv(mSocketBuffer, XIP_STREAM_BUFFER_SIZE, 0);
	if(sizeRecBuf <= 0) 
    {
		//throw RadException(__LINE__, __FILE__, RadException::COMM_ERROR, L"Communication error (request received invalid )");
        return;
    }

	char * remainingBufferPtr = mSocketBuffer;

	if(!remainingBufferPtr && sizeRecBuf < 4 + 2*sizeof(short))
    {
		//throw RadException(__LINE__, __FILE__, RadException::INVALID_STATE_ERROR, L"Received buffer  invalid");
        return;
    }

	remainingBufferPtr += 2;

	short reqID = ntohs(*((short *)remainingBufferPtr));
	remainingBufferPtr += sizeof(short);

	int sizeReq = ntohl(*((int *)remainingBufferPtr));
	remainingBufferPtr += sizeof(int);

	mTabElements->init(reqID);
	nbUsedElement++;

	#if _DEBUGINFILE__
	std::ofstream debugFile("c:\\RequestDebug.txt", std::ofstream::out | std::ofstream::app);
	if(debugFile.is_open())
	{
		debugFile << "readElement id:"<<reqID<<" htons:"<<htons(reqID)<<std::endl;
		debugFile << "readElement size:"<<sizeReq<<std::endl;
		debugFile <<"buffer ||";
		debugFile.write(mSocketBuffer, sizeRecBuf);
		debugFile.flush();
		debugFile <<"|| endbuffer"<<std::endl;
		debugFile.flush();
		debugFile.close();
	}
	#endif	

	readElementFromBuffer(mTabElements, remainingBufferPtr ,sizeReq);
}

// --------------------------------------------------------------------------
//! read a request containing in a buffer
// --------------------------------------------------------------------------
void XipTreeRequestReceiver::readBuffer(char *buff, int sizeBuff)
{

	init();

	if(!buff && sizeBuff < 4 + 2*sizeof(short))
    {
		//throw RadException(__LINE__, __FILE__, RadException::INVALID_STATE_ERROR, L"Received buffer  invalid");
        return;
    }
	
	memcpy(mSocketBuffer, buff, sizeBuff);
	char * remainingBufferPtr = mSocketBuffer;

	remainingBufferPtr += 2;

	short reqID = ntohs(*((short *)remainingBufferPtr));
	remainingBufferPtr += sizeof(short);

	int sizeReq = ntohl(*((int *)remainingBufferPtr));
	remainingBufferPtr += sizeof(int);

	mTabElements->init(reqID);
	nbUsedElement++;

	readElementFromBuffer(mTabElements, remainingBufferPtr ,sizeReq);
}


// --------------------------------------------------------------------------
//! give the identifiant of the first element of the tree
// --------------------------------------------------------------------------
short XipTreeRequestReceiver::getFirstElementId()
{
	return mTabElements->mElementID;
}

// --------------------------------------------------------------------------
//! give the ID of the element next to the element given in parameter
// --------------------------------------------------------------------------
short XipTreeRequestReceiver::getNextElementId(short ToElementID)
{
	RequestTreeElement * tmp = getElement(ToElementID);
	if(tmp)
	{
		if(tmp->getNextElement())
			return tmp->getNextElement()->mElementID;
	}

	return -1;
}

// --------------------------------------------------------------------------
//! give the ID of the first child element of the element given in parameter
// --------------------------------------------------------------------------
short XipTreeRequestReceiver::getChildElementId(short ToElementID)
{
	RequestTreeElement * tmp = getElement(ToElementID);
	if(tmp)
	{
		if(tmp->getFirstChildElement())
			return tmp->getFirstChildElement()->mElementID;
	}

	return -1;
}

// --------------------------------------------------------------------------
//! give the buffer of the given element if exist, else return NULL
// --------------------------------------------------------------------------
char * XipTreeRequestReceiver::getElementContent(short IdElement, int sizeBufferContent)
{
	RequestTreeElement * tmp = getElement(IdElement);
	if(tmp && tmp->mBuffer)
	{
		if(tmp->mBufferSize == sizeBufferContent)
		{
			return tmp->mBuffer;
		}
		else
		{
			//throw RadException(__LINE__, __FILE__, RadException::INVALID_PARAM_ERROR, L"size or type of content not valid");
            return NULL;
		}
	}

	return NULL;
}

// --------------------------------------------------------------------------
//! give a bool if exist and if is of the good type, else return false
// --------------------------------------------------------------------------
bool XipTreeRequestReceiver::getUniqueBoolElement(short IdElement, bool &content)
{
	char * res = getElementContent(IdElement, sizeof(bool));
	if(res)
	{
		content = *((bool *)res);
		return true;
	}

	return false;
}

// --------------------------------------------------------------------------
//! give a short if exist and if is of the good type, else return false
// --------------------------------------------------------------------------
bool XipTreeRequestReceiver::getUniqueShortElement(short IdElement, short &content)
{
	char * res = getElementContent(IdElement, sizeof(short));
	if(res)
	{
		content = *((short *)res);
		return true;
	}

	return false;
}

// --------------------------------------------------------------------------
//! give a int if exist and if is of the good type, else return false
// --------------------------------------------------------------------------
bool XipTreeRequestReceiver::getUniqueIntElement(short IdElement, int &content)
{
	char * res = getElementContent(IdElement, sizeof(int));
	if(res)
	{
		content = *((int *)res);
		return true;
	}

	return false;
}

// --------------------------------------------------------------------------
//! give a float if exist and if is of the good type, else return false
// --------------------------------------------------------------------------
bool XipTreeRequestReceiver::getUniqueFloatElement(short IdElement, float &content)
{
	char * res = getElementContent(IdElement, sizeof(float));
	if(res)
	{
		content = *((float *)res);
		return true;
	}

	return false;
}

// --------------------------------------------------------------------------
//! give a double if exist and if is of the good type, else return false
// --------------------------------------------------------------------------
bool XipTreeRequestReceiver::getUniqueDoubleElement(short IdElement, double &content)
{
	char * res = getElementContent(IdElement, sizeof(double));
	if(res)
	{
		content = *((double *)res);
		return true;
	}

	return false;
}

// --------------------------------------------------------------------------
//! give a unsigned int if exist and if is of the good type, else return false
// --------------------------------------------------------------------------
bool XipTreeRequestReceiver::getUniqueUIntElement(short IdElement, unsigned int &content)
{
	char * res = getElementContent(IdElement, sizeof(unsigned int));
	if(res)
	{
		content = *((unsigned int *)res);
		return true;
	}

	return false;
}


// --------------------------------------------------------------------------
//! read an element and all the child from the buffer starting at the given pointer
// --------------------------------------------------------------------------
void XipTreeRequestReceiver::readElementFromBuffer(RequestTreeElement * CurrentElement, char *buffer, int sizeBuffer)
{
	//recursive parsing function, calling itself on the childs elements when found


	#if _DEBUGINFILE__
	std::ofstream debugFile("c:\\RequestDebug.txt", std::ofstream::out | std::ofstream::app);
	if(debugFile.is_open())
	{
		debugFile << "readElement id:"<<CurrentElement->mElementID<<std::endl;
		debugFile << "readElement size:"<<sizeBuffer<<std::endl;
		debugFile <<"buffer ||";
		debugFile.write(buffer, sizeBuffer);
		debugFile.flush();
		debugFile <<"|| endbuffer"<<std::endl;
		debugFile.flush();
		debugFile.close();
	}
	#endif


	short childID;
	int childSize;	

	while(sizeBuffer > 0)
	{
		if(sizeBuffer > SIZESEPARATOR && buffer[0] == 'O' && buffer[1] == 'P')
		{

			buffer += 2;

			childID = ntohs(*((short *)buffer));
			buffer += sizeof(short);

			childSize = ntohl(*((int *)buffer));
			buffer += sizeof(int);


			RequestTreeElement * fChild = ++mPtrTabElement;
			fChild->init(childID);
			CurrentElement->addChildElement(fChild);
			nbUsedElement++;
		
			readElementFromBuffer(fChild, buffer, childSize);

			sizeBuffer -= (2 + sizeof(short) + sizeof(int) + childSize);
			buffer += childSize;
		}
		else
		{
			CurrentElement->mBuffer = buffer;
			CurrentElement->mBufferSize = sizeBuffer;
			buffer += sizeBuffer;
			sizeBuffer = 0;
		}
	}
}


// --------------------------------------------------------------------------
//! find the sequence str2 in str1, return the position and the pointer in str1, 
//! return the pos just before the sequence str2 in str1, -1 if not found
// --------------------------------------------------------------------------
int XipTreeRequestReceiver::strFindStr(char * str1, char * str2, int maxLenght, int sizeStr2, char * &ptrStr1)
{
	if(!str1 || !str2)	
		return -1;
		
	int pos = 0;
	ptrStr1 = str1;
	bool found = false;

	while(pos < maxLenght && !found)
	{
		if(*ptrStr1 == *str2)
			found = compStr(ptrStr1, str2, sizeStr2);

		++ptrStr1;
		++pos;
	}

	--ptrStr1;

	if(!found)
		return -1;
	else
		return pos-1;
}

// --------------------------------------------------------------------------
//! find if str2 is equal to the beginning of str1 
// --------------------------------------------------------------------------
bool XipTreeRequestReceiver::compStr(char * str1, char * str2, int sizeStr2)
{
	if(!str1 || !str2)
		return false;
	
	for(int i=0; i<sizeStr2; i++)
	{
		if(*str1++ != *str2++)
			return false;
	}

	return true;
}


// --------------------------------------------------------------------------
//! convert table of short (little endian/big endian)
// --------------------------------------------------------------------------
void XipTreeRequestManager::rHtons(short* tabShort, int sizeTab)
{
	int i;
	for(i=0; i< sizeTab; i++)
	{
		tabShort[i] = htons(tabShort[i]);
	}
}

// --------------------------------------------------------------------------
//! convert table of int (little endian/big endian)
// --------------------------------------------------------------------------
void XipTreeRequestManager::rHtonl(int* tabInt, int sizeTab)
{
	int i;
	for(i=0; i< sizeTab; i++)
	{
		tabInt[i] = htonl(tabInt[i]);
	}
}

// --------------------------------------------------------------------------
//! reconvert table of short (little endian/big endian)
// --------------------------------------------------------------------------
void XipTreeRequestManager::rNtohs(short* tabShort, int sizeTab)
{
	int i;
	for(i=0; i< sizeTab; i++)
	{
		tabShort[i] = ntohs(tabShort[i]);
	}
}

// --------------------------------------------------------------------------
//! reconvert table of int (little endian/big endian)
// --------------------------------------------------------------------------
void XipTreeRequestManager::rNtohl(int* tabInt, int sizeTab)
{
	int i;
	for(i=0; i< sizeTab; i++)
	{
		tabInt[i] = ntohl(tabInt[i]);
	}
}

// --------------------------------------------------------------------------
//! convert table of float (little endian/big endian)
// --------------------------------------------------------------------------
void XipTreeRequestManager::rSwapf(float* tabFloat, int sizeTab)
{
	//only swap if big endian architecture
	#if defined(WINDOWS) || defined(_WIN32)
		return;
	#else
		if(BYTE_ORDER == 1234)
			return;
	#endif

	int i;
	for(i=0; i< sizeTab; i++)
	{
		tabFloat[i] = swapFloat(tabFloat[i]);
	}
}

// --------------------------------------------------------------------------
//! convert table of double (little endian/big endian)
// --------------------------------------------------------------------------
void XipTreeRequestManager::rSwapd(double* tabDouble, int sizeTab)
{
	//only swap if big endian architecture
	#if defined(WINDOWS) || defined(_WIN32)
		return;
	#else
		if(BYTE_ORDER == 1234)
			return;
	#endif

	int i;
	for(i=0; i< sizeTab; i++)
	{
		tabDouble[i] = swapDouble(tabDouble[i]);
	}
}



// --------------------------------------------------------------------------
//! used to swap a short (little endian/big endian)
// --------------------------------------------------------------------------
short XipTreeRequestManager::swapShort(short S)
{


	//only swap if big endian architecture
	#if defined(WINDOWS) || defined(_WIN32)
		return S;
	#else
		if(BYTE_ORDER == 1234)
			return S;
	#endif

	union {        
		short s;        
		unsigned char b[2];
	} u1, u2;

	u1.s = S;

	u2.b[0] = u1.b[1];
	u2.b[1] = u1.b[0];    

	return u2.s;
}


// --------------------------------------------------------------------------
//! used to swap a unsigned short (little endian/big endian)
// --------------------------------------------------------------------------
unsigned short XipTreeRequestManager::swapUShort(unsigned short S)
{
	//only swap if big endian architecture
	#if defined(WINDOWS) || defined(_WIN32)
		return S;
	#else
		if(BYTE_ORDER == 1234)
			return S;
	#endif

	short res;
	char *ptS = ((char*)&S);
	char *ptres = ((char*)&res);
	*ptres++ = ptS[1];
	*ptres=*ptS;

	return res;
/*
	union {        
		unsigned short s;        
		unsigned char b[2];
	} u1, u2;

	u1.s = S;

	u2.b[0] = u1.b[1];
	u2.b[1] = u1.b[0];    

	return u2.s;*/
}

// --------------------------------------------------------------------------
//! used to swap a float (little endian/big endian)
// --------------------------------------------------------------------------
float XipTreeRequestManager::swapFloat( float F ) 
{
	union {        
		float f;        
		unsigned char b[4];
	} u1, u2;

	u1.f = F;

	u2.b[0] = u1.b[3];
	u2.b[1] = u1.b[2];    
	u2.b[2] = u1.b[1];    
	u2.b[3] = u1.b[0];

	return u2.f;
}

// --------------------------------------------------------------------------
//! used to swap a double (little endian/big endian)
// --------------------------------------------------------------------------
double XipTreeRequestManager::swapDouble( double D ) 
{    
	union {
		double d;
		unsigned char b[8];
	} u1, u2;

	u1.d = D;

	u2.b[0] = u1.b[7];
	u2.b[1] = u1.b[6];
	u2.b[2] = u1.b[5];
	u2.b[3] = u1.b[4];
	u2.b[4] = u1.b[3];
	u2.b[5] = u1.b[2];
	u2.b[6] = u1.b[1];
	u2.b[7] = u1.b[0];

	return u2.d;
}
