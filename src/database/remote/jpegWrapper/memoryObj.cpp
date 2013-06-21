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

#include <xip/inventor/remote/jpegWrapper/memoryObj.h>

MemoryObj::MemoryObj(unsigned char* pBuffer, unsigned long size)
{
	bufferPtr = pBuffer;
	pointerPosition = 0;
	memobjSize = bufferSize = size;
	freeMemobj = (bool)(pBuffer==0);
}

MemoryObj::~MemoryObj()
{
	CloseMemObj();
}

bool MemoryObj::CloseMemObj()
{
	if ( (bufferPtr) && (freeMemobj) )
	{
		free(bufferPtr);
		bufferPtr = NULL;
		memobjSize = 0;
		return true;
	}
	else
		return false;
}

bool MemoryObj::OpenMemObj()
{
	if (bufferPtr) return false;	// must be closed first

	pointerPosition = memobjSize = bufferSize = 0;
	bufferPtr=(unsigned char*)malloc(1);
	freeMemobj = true;

	return (bufferPtr!=0);
}

size_t MemoryObj::ReadFromMem(void *buffer, size_t size, size_t count)
{
	if (buffer==NULL) return 0;

	if (bufferPtr==NULL) return 0;
	if (pointerPosition >= (long)memobjSize) return 0;

	long nCount = (long)(count*size);
	if (nCount == 0) return 0;

	long nRead;
	if (pointerPosition + nCount > (long)memobjSize)
		nRead = (memobjSize - pointerPosition);
	else
		nRead = nCount;

	memcpy(buffer, bufferPtr + pointerPosition, nRead);
	pointerPosition += nRead;

	return (size_t)(nRead/size);
}

size_t MemoryObj::WriteToMem(const void *buffer, size_t size, size_t count)
{
	if (bufferPtr==NULL) return 0;
	if (buffer==NULL) return 0;

	long nCount = (long)(count*size);
	if (nCount == 0) return 0;

	if (pointerPosition + nCount > bufferSize) Alloc(pointerPosition + nCount);

	memcpy(bufferPtr + pointerPosition, buffer, nCount);

	pointerPosition += nCount;

	if (pointerPosition > (long)memobjSize) memobjSize = pointerPosition;
	
	return count;
}

void MemoryObj::Alloc(unsigned long dwNewLen)
{
	if (dwNewLen > (unsigned long)bufferSize)
	{
		unsigned long dwNewBufferSize = (unsigned long)(((dwNewLen>>12)+1)<<12);

		if (bufferPtr == NULL) bufferPtr = (unsigned char*)malloc(dwNewBufferSize);
		else	bufferPtr = (unsigned char*)realloc(bufferPtr, dwNewBufferSize);

		freeMemobj = true;

		bufferSize = dwNewBufferSize;
	}
	return;
}

void MemoryObj::Free()
{
	CloseMemObj();
}

