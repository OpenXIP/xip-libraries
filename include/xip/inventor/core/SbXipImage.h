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
#ifndef SBXIPIMAGE_H
#define SBXIPIMAGE_H

#include <xip/inventor/core/xipivcore.h>
#include <Inventor/SbLinear.h>

const int XIP_IMAGE_DIMENSIONS = 3;

class XIPIVCORE_API SbXipImageDimensions
{
public:
	SbXipImageDimensions();
	SbXipImageDimensions(const SbXipImageDimensions& other);
	SbXipImageDimensions(int width, int height, int depth = 1);
	virtual ~SbXipImageDimensions();
	int& operator [](const int i);
	int  operator [](const int i) const;

protected:
	int mDimension[XIP_IMAGE_DIMENSIONS];
};

XIPIVCORE_API int operator ==(const SbXipImageDimensions& d1, const SbXipImageDimensions& d2);
XIPIVCORE_API int operator !=(const SbXipImageDimensions& d1, const SbXipImageDimensions& d2);



class XIPIVCORE_API SbXipImage
{
public:
	enum DataType
	{
		UNSIGNED_BYTE,
		BYTE,
		UNSIGNED_SHORT,
		SHORT,
		UNSIGNED_INT,
		INT,
		FLOAT,
		DOUBLE
	};

	enum ComponentType
	{
		INTERLEAVED,
		SEPARATE
	};

	enum ComponentLayoutType
	{
		LUMINANCE,
		LUMINANCE_ALPHA,
		ALPHA,
		RGB,
		RGBA,
		RED,
		GREEN,
		BLUE,
        PACKED_LUMINANCE
	};

	enum MemoryType
	{
		HEAP,
		MAPPED
	};

	SbXipImage();

	SbXipImage(	const SbXipImageDimensions &dimensions,	DataType type, int bitsStored,
				void* pixelBuffer, int components = 1,
				ComponentType compType = SEPARATE, ComponentLayoutType compLayout = LUMINANCE,
				const SbMatrix &modelMatrix = SbMatrix::identity(), int lineAlignment = 1,
				MemoryType memType = HEAP);

	SbXipImage(	const SbXipImageDimensions &dimensions,
				DataType type, int bitsStored, int components = 1,
				ComponentType compType = SEPARATE, ComponentLayoutType compLayout = LUMINANCE,
				const SbMatrix &modelMatrix = SbMatrix::identity(), int lineAlignment = 1,
				MemoryType memType = HEAP, unsigned char memoryAlignment = 1);

	SbXipImage(	const SbXipImageDimensions &dimAllocated, const SbXipImageDimensions &dimStored,
				DataType type, int bitsStored, int components = 1,
				ComponentType compType = SEPARATE, ComponentLayoutType compLayout = LUMINANCE,
				const SbMatrix &modelMatrix = SbMatrix::identity(), int lineAlignment = 1,
				MemoryType memType = HEAP, unsigned char memoryAlignment = 1);

	virtual void init(
				const SbXipImageDimensions &dimensions,	DataType type, int bitsStored,
				void* pixelBuffer, int components = 1,
				ComponentType compType = SEPARATE, ComponentLayoutType compLayout = LUMINANCE,
				const SbMatrix &modelMatrix = SbMatrix::identity(), int lineAlignment = 1,
				MemoryType memType = HEAP);

	virtual void init(
				const SbXipImageDimensions &dimensions,
				DataType type, int bitsStored, int components = 1,
				ComponentType compType = SEPARATE, ComponentLayoutType compLayout = LUMINANCE,
				const SbMatrix &modelMatrix = SbMatrix::identity(), int lineAlignment = 1,
				MemoryType memType = HEAP, unsigned char memoryAlignment = 1);

	virtual void init(
				const SbXipImageDimensions &dimAllocated, const SbXipImageDimensions &dimStored,
				DataType type, int bitsStored, int components = 1,
				ComponentType compType = SEPARATE, ComponentLayoutType compLayout = LUMINANCE,
				const SbMatrix &modelMatrix = SbMatrix::identity(), int lineAlignment = 1,
				MemoryType memType = HEAP, unsigned char memoryAlignment = 1);


	virtual ~SbXipImage();
	virtual void* refBufferPtr();
	virtual void  unrefBufferPtr();
	virtual const SbXipImageDimensions& getDimAllocated() const;
	virtual const SbXipImageDimensions& getDimStored() const;
	virtual int getBitsStored() const;
	virtual DataType getType() const;
	virtual int getComponents() const;
	virtual ComponentType getComponentType() const;
	virtual ComponentLayoutType getComponentLayoutType() const;
	virtual SbMatrix getModelMatrix() const;
    virtual double getMinLuminance() const;
    virtual double getMaxLuminance() const;
	virtual int getCurCol() const;
	virtual void setCurCol(int curCol) { mCurCol = curCol; }

	virtual int getLineAlignment() const;
	virtual int getLineLengthAllocated() const;
	virtual int getLineLengthStored() const;

	virtual void   zero();
    virtual void setMinMaxLuminance(double min, double max);
	virtual size_t bufferSize() const;

protected:
	virtual void allocBuffer();
	virtual void freeBuffer();

	SbXipImageDimensions mDimAllocated;
	SbXipImageDimensions mDimStored;
	int mBitsStored;
	DataType mType;
	int mComponents;
	ComponentType mCompType;
	ComponentLayoutType mCompLayout;
	SbMatrix mModelMatrix;
	int mLineAlignment;
	unsigned char mMemoryAlignment;
	int mCurCol;

	void *mBuffer;
	bool mOwnBuffer;
    double mMinLuminance;
    double mMaxLuminance;
};


#endif // SBXIPIMAGE_H
