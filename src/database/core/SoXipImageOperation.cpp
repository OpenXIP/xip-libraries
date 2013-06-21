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

#include <Inventor/errors/SoMemoryError.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SbXipImageAdaptor.h>
#include "SoXipImageOperation.h"

SO_ENGINE_SOURCE( SoXipImageOperation );

SoXipImageOperation::SoXipImageOperation()
{
	SO_ENGINE_CONSTRUCTOR( SoXipImageOperation );

	SO_ENGINE_DEFINE_ENUM_VALUE( OperationEnum, MASK_OR );
	SO_ENGINE_DEFINE_ENUM_VALUE( OperationEnum, MASK_AND );
	SO_ENGINE_DEFINE_ENUM_VALUE( OperationEnum, MASK_NOR );
	SO_ENGINE_SET_SF_ENUM_TYPE( operation, OperationEnum );

	SO_ENGINE_ADD_INPUT( mask1, (0) );
    SO_ENGINE_ADD_INPUT( mask2, (0) );
    SO_ENGINE_ADD_INPUT( operation, (MASK_OR) );

	SO_ENGINE_ADD_OUTPUT( mask, SoXipSFDataImage );

	mMaskData = 0;
}

SoXipImageOperation::~SoXipImageOperation()
{
	if( mMaskData )
	{
		mMaskData->unref();
		mMaskData = 0;
	}    
}

void
SoXipImageOperation::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipImageOperation, SoEngine, "Engine" );
}

void 
SoXipImageOperation::evaluate()
{
	try
	{
		// Reset output
		if( mMaskData )
		{
			mMaskData->unref();
			mMaskData = 0;
		}

		SO_ENGINE_OUTPUT( mask, SoXipSFDataImage, setValue(0) );

		SoXipDataImage* maskData1 = mask1.getValue();
		SoXipDataImage* maskData2 = mask2.getValue();

		if( !maskData1 || !maskData1->get() )
		{
			if( operation.getValue() == MASK_OR || operation.getValue() == MASK_NOR )
			{
				SO_ENGINE_OUTPUT( mask, SoXipSFDataImage, setValue(maskData2) );
			}
			return ;
		}
		else if( !maskData2 || !maskData2->get() )
		{
			if( operation.getValue() == MASK_OR || operation.getValue() == MASK_NOR )
			{
				SO_ENGINE_OUTPUT( mask, SoXipSFDataImage, setValue(maskData1) );
			}
			return ;
		}

		SbXipImage* maskImage1 = maskData1->get();
		SbXipImage* maskImage2 = maskData2->get();

		if( maskImage1->getType() != SbXipImage::UNSIGNED_BYTE ||
			maskImage2->getType() != SbXipImage::UNSIGNED_BYTE ||
			maskImage1->getComponentLayoutType() != SbXipImage::PACKED_LUMINANCE ||
			maskImage2->getComponentLayoutType() != SbXipImage::PACKED_LUMINANCE )
		{
			SoDebugError::post( __FILE__, "SoXipImageOperation::evaluate(): image format not supported. \
				Expect unsigned 8 bits packed image" );
			return ;
		}

		SbXipImageDimensions dimensions = maskImage1->getDimStored();

		if( maskImage2->getDimStored() != dimensions )
		{
			SoDebugError::post( __FILE__, "SoXipImageOperation::evaluate(): input masks have different dimensions" );
			return ;
		}

		// Allocate output mask
		SbXipImage* maskOut = new SbXipImage(
			dimensions,
			SbXipImage::UNSIGNED_BYTE,
			8,
			1,
			SbXipImage::SEPARATE, 
			SbXipImage::PACKED_LUMINANCE, 
			maskImage1->getModelMatrix() );

		if( !maskOut )
		{
			SoMemoryError::post( "SoXipImageOperation::evaluate(): output mask" );
			return ;
		}

		unsigned char* mask1Ptr = (unsigned char *) maskImage1->refBufferPtr();
		unsigned char* mask2Ptr = (unsigned char *) maskImage2->refBufferPtr();
		unsigned char* maskOutPtr = (unsigned char *) maskOut->refBufferPtr();
		{
			int lineLengthAllocated = maskImage1->getLineLengthAllocated();
			int numCells = dimensions[2] * dimensions[1] * lineLengthAllocated;

			if( operation.getValue() == MASK_OR )
			{
				for( int i = 0; i < numCells; ++ i )
					*maskOutPtr ++ = *mask1Ptr ++ | *mask2Ptr ++;
			}
			else if( operation.getValue() == MASK_AND )
			{
				for( int i = 0; i < numCells; ++ i )
					*maskOutPtr ++ = *mask1Ptr ++ & *mask2Ptr ++;
			}
			else if( operation.getValue() == MASK_NOR )
			{
				for( int i = 0; i < numCells; ++ i )
					*maskOutPtr ++ = *mask1Ptr ++ ^ *mask2Ptr ++;
			}				
		}
		maskImage1->unrefBufferPtr();
		maskImage2->unrefBufferPtr();
		maskOut->unrefBufferPtr();

		mMaskData = new SoXipDataImage;
		if( !mMaskData )
		{
			SoMemoryError::post( "SoXipImageOperation::evaluate(): output mask data" );
			return ;
		}

		mMaskData->ref();
		mMaskData->set( maskOut );

		SO_ENGINE_OUTPUT( mask, SoXipSFDataImage, setValue(mMaskData) );
	}
	catch(...)
	{
		SoError::post( __FILE__, "Unexpected error in SoXipImageOperation::evaluate()" );
	}
}
