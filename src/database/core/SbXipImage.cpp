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

#include <string.h>
#include <xip/inventor/core/SbXipImage.h>
#include <Inventor/errors/SoMemoryError.h>
#include <Inventor/errors/SoDebugError.h>


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
	for (int i = 0; i < 3; i++)
		if (d1[i] != d2[i]) return FALSE;

	return TRUE;
}

int operator !=(const SbXipImageDimensions& d1, const SbXipImageDimensions& d2)
{
	for (int i = 0; i < 3; i++)
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
	const SbMatrix &modelMatrix, int lineAlignment, MemoryType memType, unsigned char memoryAlignment)
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


void SbXipImage::init(
	const SbXipImageDimensions &dimensions,
    DataType type, int bitsStored, void* pixelBuffer,
	int components,	ComponentType compType, ComponentLayoutType compLayout,
	const SbMatrix &modelMatrix, int lineAlignment,	MemoryType memType)
{
	freeBuffer();

	mMinLuminance = 0;
	mMaxLuminance = 0;
	mDimAllocated = dimensions;
	mDimStored = dimensions;
	mBitsStored = bitsStored;
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
	const SbMatrix &modelMatrix, int lineAlignment, MemoryType memType, unsigned char memoryAlignment)
{	
	freeBuffer();

	mMinLuminance = 0;
	mMaxLuminance = 0;
	mDimAllocated = dimensions;
	mDimStored = dimensions;

	// We have to ensure that the x-dimension allocated is a multiple of 8
	// in case the image pixel buffer is packed (8 voxel per byte).
	//
	if( compLayout == PACKED_LUMINANCE )
		mDimAllocated[0] = ( ( mDimAllocated[0] + 7 ) / 8 ) * 8;

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
		return (mDimAllocated[0] / b) * (mCompType == INTERLEAVED ? mComponents : 1);
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
		return (mDimStored[0] / b) * (mCompType == INTERLEAVED ? mComponents : 1);
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
