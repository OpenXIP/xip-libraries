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

#ifndef XIPREQUESTMANAGER_H
#define XIPREQUESTMANAGER_H

#include <xip/inventor/remote/XipStream.h>


#define MAX_TREE_ELEMENTS 100

//----------------------------------------------------------------------------
//! class element of the request tree
class RequestTreeElement
{

public:

	//! identifiant of te request element
	short mElementID;

	//! size of the buffer
	int mBufferSize;

	//! buffer containing the element
	char * mBuffer;

	int mSizeForWritting;

	//! Constructor
	RequestTreeElement();

	//! Constructor with ID
	RequestTreeElement(short ID);

	//! Constructor with a buffer
	RequestTreeElement(short ID, int Size, char * Buf);

	//! Destructor
	~RequestTreeElement(){}

	//! method used for element initialisation
	void init(short ID = -1, int Size = 0, char * Buf = 0);

	//! method used to add a element at the same level of the tree than the current element
	void addElement(RequestTreeElement * Element);

	//! method used to add a element as a child of the current element
	void addChildElement(RequestTreeElement * Element);

	//! return the first child of the current element
	RequestTreeElement * getFirstChildElement();

	//! return the element next to the current one
	RequestTreeElement * getNextElement();

	//! search for the element with identifiant ID in the tree
	RequestTreeElement * getElement(short ID);

	//! calculate the needed place to write the element in a buffer
	int calculateSizeForWritting();


private:
	//! first child of the current element	
	RequestTreeElement * mFirstChildElement;

	//! element next to the current one
	RequestTreeElement * mNextElement;

};



//----------------------------------------------------------------------------
//! base class used to send tree requests
class XipTreeRequestManager
{

public:

	//! Constructor with a stream and the request ID
	XipTreeRequestManager(XipStreamBase *Stream);
	
	//! Destructor
	virtual ~XipTreeRequestManager() { if(mSocketBuffer) delete [] mSocketBuffer; }

	//! convert table of short (little endian/big endian)
	void rHtons(short	* tabShort, int sizeTab = 1);

	//! convert table of int (little endian/big endian)
	void rHtonl(int	* tabInt, int sizeTab = 1);

	//! reconvert table of short (little endian/big endian)
	void rNtohs(short	* tabShort, int sizeTab = 1);

	//! reconvert table of int (little endian/big endian)
	void rNtohl(int	* tabInt, int sizeTab = 1);

	//! convert table of float (little endian/big endian)
	void rSwapf(float	* tabFloat, int sizeTab = 1);

	//! convert table of double (little endian/big endian)
	void rSwapd(double	* tabDouble, int sizeTab = 1);


	//! used to swap a short (little endian/big endian)
	short swapShort(short S); 
	
	//! used to swap a unsigned short (little endian/big endian)
	unsigned short swapUShort(unsigned short S);

	//! used to swap a float (little endian/big endian)
	float swapFloat(float F); 

	//! used to swap a double (little endian/big endian)
	double swapDouble(double D);

protected:

    //! stream used for communication
	XipStreamBase *mStream;
	
	//! first request element of the tree
	RequestTreeElement * mPtrTabElement;
	
	//! pointer on the last used element
	RequestTreeElement * mLastUsedElement;

	//! number of element in the table
	int nbUsedElement;

	//! buffer used to store information we send/receive from socket
	char *mSocketBuffer;

	//! table containing the elements of the request
	RequestTreeElement mTabElements[MAX_TREE_ELEMENTS];

	//! return a pointer on the element giving the ID
	RequestTreeElement * getElement(short ElementID);

	//! method used to init the tree
	void init();
};


//----------------------------------------------------------------------------
//! class used to send tree requests
class XipTreeRequestSender : public XipTreeRequestManager
{
public:
	//! Constructor
	XipTreeRequestSender();	

	//! Constructor with a stream and the request ID
	XipTreeRequestSender(XipStreamBase *Stream, short IDRequest);

	//! Destructor
	~XipTreeRequestSender(){}

	//! init the request  with a stream and the request ID
	void initSender(XipStreamBase *Stream, short IDRequest);

	//! Add a new element to the request as the next element of toElementID in the tree
	void addNextElement(short ToElementID, short NewElementID, int NewElementSize = 0, void * NewElementBuffer = 0);

	//! Add a new element to the request as the child element of toElementID in the tree
	void addChildElement(short ToElementID, short NewElementID, int NewElementSize = 0, void * NewElementBuffer = 0);

	//! Change the content of an element
	bool changeElementContent(short ElementID, void * NewElementBuffer);

	//! method used to send the request
	virtual void send();

	//! method to give the request containing in a buffer
	char * getBuffer(int & sizeBuffer);


private:

	//! write an element and all the child to the buffer starting at the given pointer
	char * writeElementToBuffer(char * PtrBuffer, RequestTreeElement * Element);
};



//----------------------------------------------------------------------------
//! class used to receive tree requests
class XipTreeRequestReceiver : public XipTreeRequestManager
{

public:
	
	//! Constructor
	XipTreeRequestReceiver(): XipTreeRequestManager(0){}
	
	//! Constructor with a stream
	XipTreeRequestReceiver(XipStreamBase *Stream): XipTreeRequestManager(Stream){}
	
	//! Destructor	
	virtual ~XipTreeRequestReceiver(){}

	//! init the request  with a stream
	void initReceiver(XipStreamBase *Stream);

	//! method used to receive the request
	virtual void receive();

	//! give the identifiant of the first element of the tree
	short getFirstElementId();

	//! give the ID of the element next to the element given in parameter
	short getNextElementId(short ToElementID);

	//! give the ID of the first child element of the element given in parameter
	short getChildElementId(short ToElementID);

	//! give the buffer of the given element if exist, else return NULL
	char * getElementContent(short IdElement, int sizeBufferContent);

	//! give the element content if exist and if is of the good type, else return false
	bool getUniqueBoolElement(short IdElement, bool &content);
	bool getUniqueShortElement(short IdElement, short &content);
	bool getUniqueIntElement(short IdElement, int &content);
	bool getUniqueFloatElement(short IdElement, float &content);
	bool getUniqueDoubleElement(short IdElement, double &content);
	bool getUniqueUIntElement(short IdElement, unsigned int &content);

	//! read a request containing in a buffer
	void readBuffer(char *buff, int sizeBuff);

private:


	//! read an element and all the children from the buffer starting at the given pointer
	void readElementFromBuffer(RequestTreeElement * CurrentElement, char *buffer, int sizeBuffer);

	//! find the sequence str2 in str1, return the position and the pointer in str1, -1 if not found
	int strFindStr(char * str1, char * str2, int maxLenght, int sizeStr2, char * &ptrStr1);

	//! find if str2 is equal to the beginning of str1 
	bool compStr(char * str1, char * str2, int sizeStr2);
};


#endif	// RADREQUESTMANAGER_H