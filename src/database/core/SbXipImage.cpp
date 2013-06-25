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

#include <string.h>
#include <xip/inventor/core/SbXipImage.h>
#include <Inventor/errors/SoMemoryError.h>
#include <Inventor/errors/SoDebugError.h>
//#include <xip/system/standard.h>
#include <Inventor/system/SoStandard.h>
#include <algorithm>

SbXipImageDimensions::SbXipImageDimensions()
{
	for (int i = 0; i < XIP_IMAGE_DIMENSIONS; i++)
		mDimension[i] = 0;
}

SbXipImageDimensions::SbXipImageDimensions(const SbXipImageDimensions& other)
{
	for (int i = 0; i < XIP_IMAGE_DIMENSIONS; i++)
		mDimension[i] = other[i];
}

SbXipImageDimensions::SbXipImageDimensions(int width, int height, int depth)
{
	mDimension[0] = width;
	mDimension[1] = height;
	mDimension[2] = depth;

	for (int i = 3; i < XIP_IMAGE_DIMENSIONS; i++)
		mDimension[i] = 0;
}

SbXipImageDimensions::~SbXipImageDimensions()
{
}

int& SbXipImageDimensions::operator [](const int i)
{
	return mDimension[i];
}

int SbXipImageDimensions::operator [](const int i) const
{
	return mDimension[i];
}

int operator ==(const SbXipImageDimensions& d1, const SbXipImageDimensions& d2)
{
	for (int i = 0; i < XIP_IMAGE_DIMENSIONS; i++)
		if (d1[i] != d2[i]) return FALSE;

	return TRUE;
}

int operator !=(const SbXipImageDimensions& d1, const SbXipImageDimensions& d2)
{
	for (int i = 0; i < XIP_IMAGE_DIMENSIONS; i++)
		if (d1[i] != d2[i]) return TRUE;

	return FALSE;
}


SbXipImage::SbXipImage()
{
	mMinLuminance = 0;
	mMaxLuminance = 0;
	mDimAllocated = SbXipImageDimensions(0, 0, 0);
	mDimStored = SbXipImageDimensions(0, 0, 0);
	mBitsStored = 0;
	mType = UNSIGNED_BYTE;
	mComponents = 0;
	mCompType = INTERLEAVED;
	mCompLayout = LUMINANCE;
	mModelMatrix = SbMatrix::identity();
	mLineAlignment = 1;
	mBuffer = 0;
	mOwnBuffer = TRUE;
	mMemoryAlignment = 1;
	mCurCol = -1;
}


SbXipImage::SbXipImage( const SbXipImageDimensions &dimAllocated,
			const SbXipImageDimensions &dimStored, DataType type, int bitsStored,
			int components, ComponentType compType, ComponentLayoutType compLayout,
			const SbMatrix &modelMatrix, int lineAlignment, MemoryType memType, unsigned char memoryAlignment)
{
	mBuffer = 0;
	mOwnBuffer = TRUE;

	init(dimAllocated, dimStored, type, bitsStored, components, compType, compLayout, modelMatrix, lineAlignment, memType, memoryAlignment);
}


SbXipImage::SbXipImage(	const SbXipImageDimensions &dimensions,
		    DataType type, int bitsStored, void* pixelBuffer,
			int components,	ComponentType compType, ComponentLayoutType compLayout,
			const SbMatrix &modelMatrix, int lineAlignment,	MemoryType memType)
{
	mBuffer = 0;
	mOwnBuffer = TRUE;

	init(dimensions, type, bitsStored, pixelBuffer, components,	compType, compLayout, modelMatrix, lineAlignment, memType);
}


SbXipImage::SbXipImage( const SbXipImageDimensions &dimensions,
			DataType type, int bitsStored,
			int components,	ComponentType compType, ComponentLayoutType compLayout,
			const SbMatrix &modelMatrix, int lineAlignment, MemoryType memType, unsigned char memoryAlignment)
{	
	mBuffer = 0;
	mOwnBuffer = TRUE;

	init(dimensions, type, bitsStored, components, compType, compLayout, modelMatrix, lineAlignment, memType, memoryAlignment);
}


void SbXipImage::init( 
	const SbXipImageDimensions &dimAllocated,
	const SbXipImageDimensions &dimStored, DataType type, int bitsStored,
	int components, ComponentType compType, ComponentLayoutType compLayout,
	const SbMatrix &modelMatrix, int lineAlignment, MemoryType , unsigned char memoryAlignment)
{
	freeBuffer();

	mMinLuminance = 0;
	mMaxLuminance = 0;
	mDimAllocated = dimAllocated;
	mDimStored = dimStored;
	mBitsStored = bitsStored;
	mType = type;
	mComponents = components;
	mCompType = compType;
	mCompLayout = compLayout;
	mModelMatrix = modelMatrix;
	mLineAlignment = lineAlignment;
	mBuffer = 0;
	mOwnBuffer = TRUE;
	mMemoryAlignment = memoryAlignment;
	mCurCol = -1;

	allocBuffer();
}

static const int __maxBitsStoredTable[] =
{
    8,	// UNSIGNED_BYTE
    8,	// BYTE
    16, // UNSIGNED_SHORT
    16, // SHORT
    32, // UNSIGNED_INT
    32, // INT
    32, // FLOAT
    64  // DOUBLE
};


void SbXipImage::init(
	const SbXipImageDimensions &dimensions,
    DataType type, int bitsStored, void* pixelBuffer,
	int components,	ComponentType compType, ComponentLayoutType compLayout,
	const SbMatrix &modelMatrix, int lineAlignment,	MemoryType )
{
	freeBuffer();

	mMinLuminance = 0;
	mMaxLuminance = 0;
	mDimAllocated = dimensions;
	mDimStored = dimensions;
	mBitsStored = std::min(bitsStored, __maxBitsStoredTable[type]);
	mType = type;
	mComponents = components;
	mCompType = compType;
	mCompLayout = compLayout;
	mModelMatrix = modelMatrix;
	mLineAlignment = lineAlignment;
	mMemoryAlignment = 1;
	mCurCol = -1;

	mBuffer = pixelBuffer;
	mOwnBuffer = FALSE;
}


void SbXipImage::init( 
	const SbXipImageDimensions &dimensions,
	DataType type, int bitsStored,
	int components,	ComponentType compType, ComponentLayoutType compLayout,
	const SbMatrix &modelMatrix, int lineAlignment, MemoryType , unsigned char memoryAlignment)
{	
	freeBuffer();

	mMinLuminance = 0;
	mMaxLuminance = 0;
	mDimAllocated = dimensions;
	mDimStored = dimensions;

	// We have to ensure that the x-dimension allocated is a multiple of 8
	// in case the image pixel buffer is packed (8 voxel per byte).
	if( compLayout == PACKED_LUMINANCE )
		mDimAllocated[0] = ( ( mDimAllocated[0] + 7 ) / 8 ) * 8;

	mBitsStored = std::min(bitsStored, __maxBitsStoredTable[type]);
	mType = type;
	mComponents = components;
	mCompType = compType;
	mCompLayout = compLayout;
	mModelMatrix = modelMatrix;
	mLineAlignment = lineAlignment;
	mBuffer = 0;
	mOwnBuffer = TRUE;
	mMemoryAlignment = memoryAlignment;
	mCurCol = -1;

	allocBuffer();
}


SbXipImage::~SbXipImage() 
{
	freeBuffer();
}

void* SbXipImage::refBufferPtr()
{
	return mBuffer;
}

void SbXipImage::unrefBufferPtr()
{
}

int SbXipImage::getCurCol() const 
{
	return mCurCol;
}

const SbXipImageDimensions& SbXipImage::getDimAllocated() const 
{
	return mDimAllocated;
}

const SbXipImageDimensions& SbXipImage::getDimStored() const 
{
	return mDimStored;
}

int SbXipImage::getBitsStored() const
{
	return mBitsStored;
}

SbXipImage::DataType SbXipImage::getType() const
{
	return mType;
}

int SbXipImage::getComponents() const
{
	return mComponents;
}

SbXipImage::ComponentType SbXipImage::getComponentType() const
{
	return mCompType;
}

SbXipImage::ComponentLayoutType SbXipImage::getComponentLayoutType() const
{
	return mCompLayout;
}

SbMatrix SbXipImage::getModelMatrix() const
{
	return mModelMatrix;
}

int SbXipImage::getLineAlignment() const
{
	return mLineAlignment;
}

size_t SbXipImage::bufferSize() const
{
	return (getLineLengthAllocated() * mDimAllocated[1] * mDimAllocated[2]);
}

void SbXipImage::allocBuffer()
{
	freeBuffer();

#ifdef _CRT_ALLOCATION_DEFINED 
	mBuffer = _aligned_malloc(bufferSize(), mMemoryAlignment);
#else //only for VC6 compilation
	mBuffer = new unsigned char[bufferSize()];
#endif
	
	if (!mBuffer)
	{
		SoMemoryError::post("SbXipImage image buffer");
	}

	mOwnBuffer = TRUE;
}


void SbXipImage::freeBuffer()
{
	if (mBuffer && mOwnBuffer)
#ifdef _CRT_ALLOCATION_DEFINED
		_aligned_free(mBuffer);
#else
		delete [] mBuffer;
#endif

	mBuffer = 0;
	mOwnBuffer = TRUE;
}

void SbXipImage::zero()
{
	if (mBuffer)
	{
		memset(mBuffer, 0, bufferSize());
	}
}

int SbXipImage::getLineLengthAllocated() const
{
	int bytesAllocated = 0;

	if (mCompLayout == PACKED_LUMINANCE)
	{
		int b = 8 / mBitsStored;
		return (mDimAllocated[0] / b);
	}

	switch (mType)
	{
	case UNSIGNED_BYTE:
	case BYTE:				bytesAllocated = 1; break;
	case UNSIGNED_SHORT:
	case SHORT:				bytesAllocated = 2; break;
	case UNSIGNED_INT:
	case INT:
	case FLOAT:				bytesAllocated = 4; break;
	case DOUBLE:			bytesAllocated = 8; break;
	}

	return (bytesAllocated * mDimAllocated[0] * (mCompType == INTERLEAVED ? mComponents : 1));
}

int SbXipImage::getLineLengthStored() const
{
	int bytesAllocated = 0;

	if (mCompLayout == PACKED_LUMINANCE)
	{
		int b = 8 / mBitsStored;
		return (mDimStored[0] / b);
	}

	switch (mType)
	{
	case UNSIGNED_BYTE:
	case BYTE:				bytesAllocated = 1; break;
	case UNSIGNED_SHORT:
	case SHORT:				bytesAllocated = 2; break;
	case UNSIGNED_INT:
	case INT:
	case FLOAT:				bytesAllocated = 4; break;
	case DOUBLE:			bytesAllocated = 8; break;
	}

	return (bytesAllocated * mDimStored[0] * (mCompType == INTERLEAVED ? mComponents : 1));
}

/// Simple method to store minimum and maximum luminance value of this image
/// Default = 0 if unknown or not set
void 
SbXipImage::setMinMaxLuminance(double min, double max)
{
    mMinLuminance = min;
    mMaxLuminance = max;
}

/// Returns the minimum luminance value, undefined if data is not in luminance format
/// This method does not calculate the value, it simply returns it if the user has
/// previously set it.  By default = 0
double
SbXipImage::getMinLuminance() const
{
    return (mMinLuminance);
}

/// Returns the maximum luminance value, undefined if data is not in luminance format
/// This method does not calculate the value, it simply returns it if the user has
/// previously set it.  By default = 0
double
SbXipImage::getMaxLuminance() const
{
    return (mMaxLuminance);
}


