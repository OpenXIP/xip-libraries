//----------------------------------------------------------------------------------
//! ImageHandler
/*!
// \file    memoryObj.h
// \author  Mathia Scucchiari
// \date    2007-05-21
*/
//----------------------------------------------------------------------------------
#if !defined(__MEMORYOBJ_H)
#define __MEMORYOBJ_H

#include "buffObj.h"


class MemoryObj : public BuffObj
{
public:
	MemoryObj(unsigned char* pBuffer = NULL, unsigned long size = 0);
	~MemoryObj();

	bool OpenMemObj();

	inline unsigned char* getBufferPtr()
	{
		return bufferPtr;
	}

	virtual bool	CloseMemObj();
	virtual size_t	ReadFromMem(void *buffer, size_t size, size_t count);
	virtual size_t	WriteToMem(const void *buffer, size_t size, size_t count);
	
	inline virtual long	PtrPosition()
	{
		if (bufferPtr==NULL) return -1;
		return pointerPosition;
	}
	
	inline virtual long	MemSize()
	{
		if (bufferPtr==NULL) return -1;
		return memobjSize;
	}
	
	inline virtual bool	Clean()
	{
		if (bufferPtr==NULL) return false;
		return true;
	}

	inline virtual long	Error()
	{
		if (bufferPtr==NULL) return -1;
		return (pointerPosition > (long)memobjSize);
	}


protected:
	void	Alloc(unsigned long nBytes);
	void	Free();

	unsigned char*	bufferPtr;
	unsigned long	memobjSize;
	bool	freeMemobj;			// free memory object on close
	long	pointerPosition;	// current position
	long	bufferSize;			//buffer size
};

#endif //__MEMORYOBJ_H
