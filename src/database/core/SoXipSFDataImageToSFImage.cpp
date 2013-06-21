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

#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <Inventor/errors/SoMemoryError.h>
#include "SoXipSFDataImageToSFImage.h"

SO_ENGINE_SOURCE( SoXipSFDataImageToSFImage );

SoXipSFDataImageToSFImage::SoXipSFDataImageToSFImage()
{
	SO_ENGINE_CONSTRUCTOR( SoXipSFDataImageToSFImage );

	SO_ENGINE_ADD_INPUT( input, (0) );
	SO_ENGINE_ADD_OUTPUT( output, SoSFImage );
}

SoXipSFDataImageToSFImage::~SoXipSFDataImageToSFImage()
{

}

void
SoXipSFDataImageToSFImage::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipSFDataImageToSFImage, SoEngine, "Engine" );
}

static inline SbXipImage* getXipImage( SoXipSFDataImage& dataField )
{
	SoXipDataImage* dataImage = dataField.getValue();
	if( !dataImage )
		return 0;

	return dataImage->get();
}

template< typename T >
unsigned char* 
convertBufferToUChar( const T* inputPtr, unsigned int bufferSize, float scale )
{
	unsigned char* outPtr = new unsigned char[ bufferSize ];
	if( !outPtr )
	{
		SoMemoryError::post( "Could not allocate conversion buffer" );
		return 0;
	}

	for( unsigned int i = 0; i < bufferSize; ++ i )
	{
		outPtr[i] = inputPtr[i] * scale;
	}

	return outPtr;
}

void
SoXipSFDataImageToSFImage::evaluate()
{
	SO_ENGINE_OUTPUT( output, SoSFImage, setValue(SbVec2s(0, 0), 1, 0) );

	SbXipImage* inputImage = getXipImage(input);
	if( !inputImage )
		return ;

	if( inputImage->getType() != SbXipImage::UNSIGNED_BYTE &&
		inputImage->getType() != SbXipImage::UNSIGNED_SHORT &&
		inputImage->getType() != SbXipImage::FLOAT )
	{
		SoError::post( "Only supports unsigned unsigned byte/ short, and float data" );
		return ;
	}

	if( inputImage->getComponentLayoutType() != SbXipImage::LUMINANCE &&
		inputImage->getComponentLayoutType() != SbXipImage::RGB &&
		inputImage->getComponentLayoutType() != SbXipImage::RGBA )
	{
		SoError::post( "Only supports LUMINANCE, RGB or RGBA data" );
		return ;
	}

	// Input image dimensions
	SbVec2s imgDims( inputImage->getDimAllocated()[0], inputImage->getDimAllocated()[1] );

	unsigned char* imgPtr;
	int bufferSize = imgDims[0] * imgDims[1];

	if( inputImage->getType() == SbXipImage::UNSIGNED_SHORT )
	{
		// Convert 16 bits data to 8 bits data
		unsigned short* buffer = (unsigned short *) inputImage->refBufferPtr();
		float scale = 1.f / 256.f;
		if( !(imgPtr = convertBufferToUChar( buffer, bufferSize, scale ) ) )
			return ;
	}
	else if( inputImage->getType() == SbXipImage::FLOAT )
	{
		// Convert float data to 8 bits data
		float* buffer = (float *) inputImage->refBufferPtr();
		float scale = 255.f;
		if( !(imgPtr = convertBufferToUChar( buffer, bufferSize, scale ) ) )
			return ;
	}
	else
	{
		// Get a pointer to the input image pixel buffer
		imgPtr = (unsigned char *) inputImage->refBufferPtr();
	}

	if( inputImage->getComponentLayoutType() == SbXipImage::LUMINANCE )
	{
		SO_ENGINE_OUTPUT( output, SoSFImage, setValue(imgDims, 1, imgPtr) );
	}
	else if( inputImage->getComponentLayoutType() == SbXipImage::RGB )
	{
		SO_ENGINE_OUTPUT( output, SoSFImage, setValue(imgDims, 3, imgPtr) );
	}
	else if( inputImage->getComponentLayoutType() == SbXipImage::RGBA )
	{
		SO_ENGINE_OUTPUT( output, SoSFImage, setValue(imgDims, 4, imgPtr) );
	}

	if( inputImage->getType() == SbXipImage::UNSIGNED_SHORT ||
		inputImage->getType() == SbXipImage::FLOAT )
	{
		// Delete buffer that was allocated to perform the conversion
		delete [] imgPtr;
	}

	// Release the pointer to the input image pixel buffer
	inputImage->unrefBufferPtr();
}
