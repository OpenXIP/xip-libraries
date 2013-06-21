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

/* author Sylvain Jaume, Julien Gein */

#include <itkImage.h>
#include <itkRGBPixel.h>
#include <itkRGBAPixel.h>
#include <Inventor/SoDB.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include "SoItkConvertItkImageToXipImage.h"

SO_ENGINE_SOURCE( SoItkConvertItkImageToXipImage );

SoItkConvertItkImageToXipImage::SoItkConvertItkImageToXipImage()
{
	SO_ENGINE_CONSTRUCTOR( SoItkConvertItkImageToXipImage );

    // Inputs
	SO_ENGINE_ADD_INPUT( input, (0) );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( output, SoXipSFDataImage );

	mXipImage = 0;
}

void 
SoItkConvertItkImageToXipImage::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkConvertItkImageToXipImage, SoFieldConverter, "SoFieldConverter" );

	// Register this converter's type with the Inventor database
	//
	SoDB::addConverter( SoItkSFDataImage::getClassTypeId(),
		SoXipSFDataImage::getClassTypeId(),
		getClassTypeId() );
}

SoItkConvertItkImageToXipImage::~SoItkConvertItkImageToXipImage()
{
	if( mXipImage )
	{
		mXipImage->unref();
		mXipImage = 0;
	}
}



template <class Type, int nDims, int nComps>
static SoXipDataImage *
createXipImageSingle(SoItkDataImage * xipItkImage, SbXipImage::DataType typeFlag,
		     int bitsPerComp, SbXipImage::ComponentLayoutType compLayout)
{
    typedef typename itk::Image<Type, nDims> ImageType;
    ImageType * itkImage = reinterpret_cast<ImageType *>(xipItkImage->getPointer());

    typename ImageType::RegionType region = itkImage->GetBufferedRegion();

    SbXipImageDimensions dimensions(1, 1, 1);

    for (unsigned int i = 0; i < nDims; ++ i)
    {
	dimensions[i] = region.GetSize()[i];
    }

    SbXipImage* image =
	new SbXipImage(dimensions, typeFlag, bitsPerComp,
		       itkImage->GetBufferPointer(), nComps,
		       SbXipImage::INTERLEAVED, compLayout,
		       xipItkImage->getModelMatrix());

    if (!image) return 0;

    SoXipDataImage * xipImage = new SoXipDataImage;
    xipImage->ref();
    xipImage->addRef(xipItkImage);
    xipImage->set(image);

    return xipImage;
}


template <class Type, int nDims>
static SoXipDataImage *
createXipImageAllComp(SoItkDataImage * xipItkImage, SbXipImage::DataType typeFlag, int bpc)
{
    SoXipDataImage * xipImage = 0;

    switch (xipItkImage->getComponentLayoutType())
    {
    case SoItkDataImage::LUMINANCE:
	xipImage = createXipImageSingle<Type, nDims, 1>(xipItkImage, typeFlag,
							bpc, SbXipImage::LUMINANCE);
	break;
                    
    case SoItkDataImage::RGB:
	xipImage = createXipImageSingle<itk::RGBPixel<Type>, nDims, 3>(xipItkImage, typeFlag,
								       bpc, SbXipImage::RGB);
	break;
                    
    case SoItkDataImage::RGBA:
	xipImage = createXipImageSingle<itk::RGBAPixel<Type>, nDims, 4>(xipItkImage, typeFlag,
									bpc, SbXipImage::RGBA);
	break;						
    }
    
    return xipImage;
}

template <int nDims>
static SoXipDataImage *
createXipImage(SoItkDataImage * xipItkImage)
{
    SoXipDataImage * xipImage = 0;

    switch (xipItkImage->getType())
    {
    case SoItkDataImage::UNSIGNED_CHAR:
	xipImage = createXipImageAllComp<unsigned char, nDims>(xipItkImage, SbXipImage::UNSIGNED_BYTE, 8);
	break;

    case SoItkDataImage::UNSIGNED_SHORT:
	xipImage = createXipImageAllComp<unsigned short, nDims>(xipItkImage, SbXipImage::UNSIGNED_SHORT, 16);
	break;
                
    case SoItkDataImage::SHORT:
	xipImage = createXipImageAllComp<short, nDims>(xipItkImage, SbXipImage::SHORT, 16);
	break;

    case SoItkDataImage::FLOAT:
	xipImage = createXipImageAllComp<float, nDims>(xipItkImage, SbXipImage::FLOAT, 32);
	break;
    }

    return xipImage;
}

void
SoItkConvertItkImageToXipImage::evaluate()
{
	if( mXipImage )
	{
		mXipImage->unref();
		mXipImage = 0;
		SO_ENGINE_OUTPUT( output, SoXipSFDataImage, setValue(0) );
	}

	SoItkDataImage* xipItkImage = input.getValue();

	if (!xipItkImage)
	    return;

	if (xipItkImage->getType() != SoItkDataImage::UNSIGNED_SHORT &&
	    xipItkImage->getType() != SoItkDataImage::FLOAT &&
	    xipItkImage->getType() != SoItkDataImage::UNSIGNED_CHAR &&
	    xipItkImage->getType() != SoItkDataImage::SHORT)
	{
	    SoDebugError::post( __FILE__, "Itk image only supports UNSIGNED_SHORT, UNSIGNED_CHAR, SHORT or FLOAT" );
	    return ;
	}

	try
	{
            switch (xipItkImage->getNumDimension())
            {
	    case 1:
		mXipImage = createXipImage<1>(xipItkImage);
		break;
	    case 2:
		mXipImage = createXipImage<2>(xipItkImage);
		break;
	    case 3:
		mXipImage = createXipImage<3>(xipItkImage);
		break;
	    }
	}
	catch( itk::ExceptionObject& e )
	{
		SoDebugError::post( e.GetFile(), "line %d: %s", e.GetLine(), e.GetDescription() );
		return ;
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown exception" );
		return ;
	}

	SO_ENGINE_OUTPUT( output, SoXipSFDataImage, setValue( mXipImage ) );
}

SoField* 
SoItkConvertItkImageToXipImage::getInput( SoType type )
{
	if( type == SoItkSFDataImage::getClassTypeId() )
	{
		return &input;
	}

	SoDebugError::post( __FILE__, "SoItkConvertItkImageToXipImage::getOutput() : unresolved input" );
	return 0;
}

SoEngineOutput* 
SoItkConvertItkImageToXipImage::getOutput( SoType type )
{
	if( type == SoXipSFDataImage::getClassTypeId() )
	{
		return &output;
	}

	SoDebugError::post( __FILE__, "SoItkConvertItkImageToXipImage::getOutput() : unresolved output" );
	return 0;
}

