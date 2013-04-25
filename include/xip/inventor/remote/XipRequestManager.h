/*
*  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
*  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
*  (XIP) was created with NCI funding and is part of the caBIG(tm) 
*  initiative. The software subject to this notice and license 
*  includes both human readable source code form and machine 
*  readable, binary, object code form (the "caBIG(tm) Software").
*  
*  This caBIG(tm) Software License (the "License") is between 
*  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
*  person or an entity, and all other entities that control, are 
*  controlled by, or are under common control with the entity.  
*  "Control" for purposes of this definition means (i) the direct or 
*  indirect power to cause the direction or management of such 
*  entity, whether by contract or otherwise, or (ii) ownership of 
*  fifty percent (50%) or more of the outstanding shares, or (iii) 
*  beneficial ownership of such entity.
*  
*  LICENSE.  Provided that You agree to the conditions described 
*  below, caBIG(tm) Participant grants You a non-exclusive, 
*  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
*  transferable and royalty-free right and license in its rights in 
*  the caBIG(tm) Software, including any copyright or patent rights 
*  therein that may be infringed by the making, using, selling, 
*  offering for sale, or importing of caBIG(tm) Software, to (i) 
*  use, install, access, operate, execute, reproduce, copy, modify, 
*  translate, market, publicly display, publicly perform, and 
*  prepare derivative works of the caBIG(tm) Software; (ii) make, 
*  have made, use, practice, sell, and offer for sale, and/or 
*  otherwise dispose of caBIG(tm) Software (or portions thereof); 
*  (iii) distribute and have distributed to and by third parties the 
*  caBIG(tm) Software and any modifications and derivative works 
*  thereof; and (iv) sublicense the foregoing rights set out in (i), 
*  (ii) and (iii) to third parties, including the right to license 
*  such rights to further third parties.  For sake of clarity, and 
*  not by way of limitation, caBIG(tm) Participant shall have no 
*  right of accounting or right of payment from You or Your 
*  sublicensees for the rights granted under this License.  This 
*  License is granted at no charge to You.  Your downloading, 
*  copying, modifying, displaying, distributing or use of caBIG(tm) 
*  Software constitutes acceptance of all of the terms and 
*  conditions of this Agreement.  If you do not agree to such terms 
*  and conditions, you have no right to download, copy, modify, 
*  display, distribute or use the caBIG(tm) Software.
*  
*  1.	Your redistributions of the source code for the caBIG(tm) 
*      Software must retain the above copyright notice, this list 
*      of conditions and the disclaimer and limitation of 
*      liability of Article 6 below.  Your redistributions in 
*      object code form must reproduce the above copyright notice, 
*      this list of conditions and the disclaimer of Article 6 in 
*      the documentation and/or other materials provided with the 
*      distribution, if any.
*  2.	Your end-user documentation included with the 
*      redistribution, if any, must include the following 
*      acknowledgment: "This product includes software developed 
*      by Siemens Corporate Research Inc."  If You do not include 
*      such end-user documentation, You shall include this 
*      acknowledgment in the caBIG(tm) Software itself, wherever 
*      such third-party acknowledgments normally appear.
*  3.	You may not use the names "Siemens Corporate Research, 
*      Inc.", "The National Cancer Institute", "NCI", "Cancer 
*      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
*      products derived from this caBIG(tm) Software.  This 
*      License does not authorize You to use any trademarks, 
*  	service marks, trade names, logos or product names of 
*      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
*      required to comply with the terms of this License.
*  4.	For sake of clarity, and not by way of limitation, You may 
*      incorporate this caBIG(tm) Software into Your proprietary 
*      programs and into any third party proprietary programs.  
*      However, if You incorporate the caBIG(tm) Software into 
*      third party proprietary programs, You agree that You are 
*      solely responsible for obtaining any permission from such 
*      third parties required to incorporate the caBIG(tm) 
*      Software into such third party proprietary programs and for 
*      informing Your sublicensees, including without limitation 
*      Your end-users, of their obligation to secure any required 
*      permissions from such third parties before incorporating 
*      the caBIG(tm) Software into such third party proprietary 
*      software programs.  In the event that You fail to obtain 
*      such permissions, You agree to indemnify caBIG(tm) 
*      Participant for any claims against caBIG(tm) Participant by 
*      such third parties, except to the extent prohibited by law, 
*      resulting from Your failure to obtain such permissions.
*  5.	For sake of clarity, and not by way of limitation, You may 
*      add Your own copyright statement to Your modifications and 
*      to the derivative works, and You may provide additional or 
*      different license terms and conditions in Your sublicenses 
*      of modifications of the caBIG(tm) Software, or any 
*      derivative works of the caBIG(tm) Software as a whole, 
*      provided Your use, reproduction, and distribution of the 
*      Work otherwise complies with the conditions stated in this 
*      License.
*  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
*      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
*      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
*      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
*      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
*      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
*      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
*      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
*      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
*      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
*      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
*      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
*      THE POSSIBILITY OF SUCH DAMAGE.
*  
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