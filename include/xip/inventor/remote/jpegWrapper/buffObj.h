//----------------------------------------------------------------------------------
//! ImageHandler
/*!
// \file    buffObj.h
// \author  Mathia Scucchiari
// \date    2007-05-21
//
// base class of the memory object
// To compile the code with VC6 the Processor Pack 5 and the Service pack 5 are required
*/
//----------------------------------------------------------------------------------
#if !defined(__BUFFOBJ_H)
#define __BUFFOBJ_H

#ifdef WIN32
 #include <windows.h>
#endif

#include <stdlib.h>

class  BuffObj
{
public:
	BuffObj(void) { };
	virtual ~BuffObj() { };

	virtual bool	CloseMemObj() = 0;
	virtual size_t	ReadFromMem(void *buffer, size_t size, size_t count) = 0;
	virtual size_t	WriteToMem(const void *buffer, size_t size, size_t count) = 0;
	virtual long	PtrPosition() = 0;
	virtual long	MemSize() = 0;
	virtual bool	Clean() = 0;
	virtual long	Error() = 0;
};

#endif //__BUFFOBJ_H
