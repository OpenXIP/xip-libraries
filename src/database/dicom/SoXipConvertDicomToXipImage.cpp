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
#include <Inventor/SoDB.h>
#include <Inventor/errors/SoErrors.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/dicom/SoXipDataDicom.h>
#include <xip/inventor/dicom/xipivDicomUtils.h>

#include "SoXipConvertDicomToXipImage.h"


//////////////////////////////////////////////////////////////////////
// SoXipConvertMFDicomToMFImage
//////////////////////////////////////////////////////////////////////


SO_ENGINE_SOURCE(SoXipConvertMFDicomToMFImage);

void SoXipConvertMFDicomToMFImage::initClass()
{
   SO_ENGINE_INIT_CLASS(SoXipConvertMFDicomToMFImage,
                        SoFieldConverter, "FieldConverter");

   // Register this converter's type with the Inventor database
   // to convert from a field (or engine output) of type
   // SoSFShort to a field of type SoSFFloat.
   // We only call this once, since this engine offers only one
   // type conversion.
   SoDB::addConverter(SoXipMFDataDicom::getClassTypeId(),
                      SoXipMFDataImage::getClassTypeId(),
                      getClassTypeId());
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SoXipConvertMFDicomToMFImage::SoXipConvertMFDicomToMFImage()
{
   // Do standard constructor tasks
   SO_ENGINE_CONSTRUCTOR(SoXipConvertMFDicomToMFImage);

   // Define input field and its default value
   SO_ENGINE_ADD_INPUT(input, (0));
   input.setNum(0);

   // Define the output, specifying its type
   SO_ENGINE_ADD_OUTPUT(output, SoXipMFDataImage);
}

SoXipConvertMFDicomToMFImage::~SoXipConvertMFDicomToMFImage()
{

}

// This is the evaluation routine.
void SoXipConvertMFDicomToMFImage::evaluate()
{
	// Remove previous data
	mData.setNum(0);

	// Reset output
	SO_ENGINE_OUTPUT( output, SoXipMFDataImage, setNum(0) );

	int size = input.getNum();
	for( int i = 0; i < size; ++ i )
	{
		SoXipDataDicom* in = input[i];
		if( !in )
			continue ;

		// convert dicom data to xip image
		SbXipImage* image = new SbXipImage();
		if( !image )
		{
			SoMemoryError::post( "SbXipImage" );
			continue ;
		}

		// error is already posted by getPixelData when returning FALSE
		if( !in->getPixelData( *image ) )
			continue ;

		// create instance of SoXipDataImage
		SoXipDataImage* dataImage = new SoXipDataImage();
		dataImage->set( image );

		// Add a reference to the original dicom image
		dataImage->addRef( in );

		mData.set1Value( mData.getNum(), dataImage );
	}

	SO_ENGINE_OUTPUT( output, SoXipMFDataImage, copyFrom( mData ) );
}

// This returns the input field for the given type. Since we
// have only one input field, we don't have to check the type.

SoField *SoXipConvertMFDicomToMFImage::getInput(SoType)
{
   return &input;
}

// This does the same for the output.

SoEngineOutput *SoXipConvertMFDicomToMFImage::getOutput(SoType)
{
   return &output;
}


//////////////////////////////////////////////////////////////////////
// SoXipConvertMFDicomToSFImage
//////////////////////////////////////////////////////////////////////


SO_ENGINE_SOURCE(SoXipConvertMFDicomToSFImage);


void SoXipConvertMFDicomToSFImage::initClass()
{
   SO_ENGINE_INIT_CLASS(SoXipConvertMFDicomToSFImage,
                        SoFieldConverter, "FieldConverter");

   // Register this converter's type with the Inventor database
   // to convert from a field (or engine output) of type
   // SoSFShort to a field of type SoSFFloat.
   // We only call this once, since this engine offers only one
   // type conversion.
   SoDB::addConverter(SoXipMFDataDicom::getClassTypeId(),
                      SoXipSFDataImage::getClassTypeId(),
                      getClassTypeId());
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SoXipConvertMFDicomToSFImage::SoXipConvertMFDicomToSFImage()
{
   // Do standard constructor tasks
   SO_ENGINE_CONSTRUCTOR(SoXipConvertMFDicomToXipImage);

   // Define input field and its default value
   SO_ENGINE_ADD_INPUT(input, (0));
   SO_ENGINE_ADD_INPUT(index, (0) );

   // Define the output, specifying its type
   SO_ENGINE_ADD_OUTPUT(output, SoXipSFDataImage);

   mOutputImage = 0;
}

SoXipConvertMFDicomToSFImage::~SoXipConvertMFDicomToSFImage()
{
	if (mOutputImage)
	{
		mOutputImage->unref();
		mOutputImage = 0;
	}
}

// This is the evaluation routine.
void SoXipConvertMFDicomToSFImage::evaluate()
{
	// set output to NULL
	SO_ENGINE_OUTPUT(output, SoXipSFDataImage, setValue(0));

	// clear existing data
	if (mOutputImage)
	{
		mOutputImage->unref();
		mOutputImage = 0;
	}

	int numSlices = input.getNum();

	// if input size is zero or the slice number is not within the number of slices, return
	if (numSlices == 0)
		return;

	int sliceId = index.getValue();
	if (sliceId >= numSlices)
		return;

	SoXipDataDicom* in = input[sliceId];
	if (!in)
		return;

	// convert dicom data to xip image
	SbXipImage *img = new SbXipImage();
	if (!img)
	{
		SoMemoryError::post("SbXipImage");
		return;
	}

	// error is already posted by getPixelData when returning FALSE
	if (!in->getPixelData(*img))
		return;

	// create instance of SoXipDataImage
	mOutputImage = new SoXipDataImage();
	mOutputImage->ref();
	mOutputImage->set(img);

	// Add a reference to the original dicom image
	mOutputImage->addRef( in );

	// update output
	SO_ENGINE_OUTPUT(output, SoXipSFDataImage, setValue(mOutputImage));
}

// This returns the input field for the given type. Since we
// have only one input field, we don't have to check the type.
SoField *SoXipConvertMFDicomToSFImage::getInput(SoType)
{
   return &input;
}

// This does the same for the output.
SoEngineOutput *SoXipConvertMFDicomToSFImage::getOutput(SoType)
{
   return &output;
}


//////////////////////////////////////////////////////////////////////
// SoXipConvertSFDicomToSFImage
//////////////////////////////////////////////////////////////////////

SO_ENGINE_SOURCE(SoXipConvertSFDicomToSFImage);


void SoXipConvertSFDicomToSFImage::initClass()
{
   SO_ENGINE_INIT_CLASS(SoXipConvertSFDicomToSFImage,
                        SoFieldConverter, "FieldConverter");

   // Register this converter's type with the Inventor database
   // to convert from a field (or engine output) of type
   // SoSFShort to a field of type SoSFFloat.
   // We only call this once, since this engine offers only one
   // type conversion.
   SoDB::addConverter(SoXipSFDataDicom::getClassTypeId(),
                      SoXipSFDataImage::getClassTypeId(),
                      getClassTypeId());
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SoXipConvertSFDicomToSFImage::SoXipConvertSFDicomToSFImage()
{
   // Do standard constructor tasks
   SO_ENGINE_CONSTRUCTOR(SoXipConvertSFDicomToSFImage);

   // Define input field and its default value
   SO_ENGINE_ADD_INPUT(input, (0));

   // Define the output, specifying its type
   SO_ENGINE_ADD_OUTPUT(output, SoXipSFDataImage);

   mOutputImage = 0;
}


SoXipConvertSFDicomToSFImage::~SoXipConvertSFDicomToSFImage()
{
	if (mOutputImage)
	{
		mOutputImage->unref();
		mOutputImage = 0;
	}
}


// This is the evaluation routine.
void SoXipConvertSFDicomToSFImage::evaluate()
{
	// set output to NULL
	SO_ENGINE_OUTPUT(output, SoXipSFDataImage, setValue(0));

	// clear existing data
	if (mOutputImage)
	{
		mOutputImage->unref();
		mOutputImage = 0;
	}

	SoXipDataDicom *in = input.getValue();
	if (!in)
		return;

	// convert dicom data to xip image
	SbXipImage *img = new SbXipImage();
	if (!img)
	{
		SoMemoryError::post("SbXipImage");
		return;
	}

	// error is already posted by getPixelData when returning FALSE
	if (!in->getPixelData(*img))
		return;

	// create instance of SoXipDataImage
	mOutputImage = new SoXipDataImage();
	mOutputImage->ref();
	mOutputImage->set(img);

	// Add a reference to the original dicom image
	mOutputImage->addRef( in );

	SO_ENGINE_OUTPUT( output, SoXipSFDataImage, setValue(mOutputImage) );
}


// This returns the input field for the given type. Since we
// have only one input field, we don't have to check the type.
SoField *SoXipConvertSFDicomToSFImage::getInput(SoType)
{
   return &input;
}


// This does the same for the output.
SoEngineOutput *SoXipConvertSFDicomToSFImage::getOutput(SoType)
{
   return &output;
}
