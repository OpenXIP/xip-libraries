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
#include <itkImportImageFilter.h>
#include <itkRGBPixel.h>
#include <itkRGBAPixel.h>
#include <Inventor/SoDB.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include "SoItkConvertXipImageToItkImage.h"

SO_ENGINE_SOURCE( SoItkConvertXipImageToItkImage );

SoItkConvertXipImageToItkImage::SoItkConvertXipImageToItkImage()
{
	SO_ENGINE_CONSTRUCTOR( SoItkConvertXipImageToItkImage );

	// Inputs
	SO_ENGINE_ADD_INPUT( input, (0) );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( output, SoItkSFDataImage );

	mItkImage = 0;
}

void 
SoItkConvertXipImageToItkImage::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkConvertXipImageToItkImage, SoFieldConverter, "SoFieldConverter" );

	SoDB::addConverter( SoXipSFDataImage::getClassTypeId(),
		SoItkSFDataImage::getClassTypeId(),
		getClassTypeId() );
}

SoItkConvertXipImageToItkImage::~SoItkConvertXipImageToItkImage()
{
	if( mItkImage )
	{
		mItkImage->unref();
		mItkImage = 0;
	}
}

void
SoItkConvertXipImageToItkImage::evaluate()
{	
	if( mItkImage )
	{
		mItkImage->unref();
		mItkImage = 0;
		SO_ENGINE_OUTPUT( output, SoItkSFDataImage, setValue(0) );
	}

	SoXipDataImage* radImage = input.getValue();
	if( !radImage )
		return ;

    SbXipImage* inputImage = radImage->get();
	if( inputImage->getType() != SbXipImage::UNSIGNED_SHORT &&
		inputImage->getType() != SbXipImage::FLOAT &&
		inputImage->getType() != SbXipImage::SHORT &&
		inputImage->getType() != SbXipImage::UNSIGNED_BYTE )
	{
		SoDebugError::post( __FILE__, "Itk image only supports UNSIGNED_SHORT, SHORT, UNSIGNED_BYTE or FLOAT" );
		return ;
	}

	try
	{
		SbXipImage* inputImage = radImage->get();
		SbXipImageDimensions dimensions = inputImage->getDimStored();

		unsigned int imageDimension = 2;
		if( dimensions[2] > 1 )
			++ imageDimension;

		if( inputImage->getComponentLayoutType() != SbXipImage::LUMINANCE && 
			inputImage->getComponentLayoutType() != SbXipImage::RGB && 
			inputImage->getComponentLayoutType() != SbXipImage::RGBA )
		{
			SoDebugError::post( __FILE__, "Image format not supported yet" );
			SoDebugError::post( __FILE__, "Rad To Itk only works with LUMINANCE, RGB and RGBA" );
			return ;
		}

		#define CREATE_RADITK_IMAGE( Type, TypeFlag, ComponentLayoutFlag, Dimension )	\
		{																				\
			Type* pixelBuffer = (Type *) inputImage->refBufferPtr();					\
																						\
			typedef itk::ImportImageFilter< Type, Dimension > ImportFilterType;			\
																						\
			ImportFilterType::SizeType size;											\
			ImportFilterType::IndexType start;											\
			double origin[ Dimension ];													\
			double spacing[ Dimension ];												\
																						\
			for( unsigned int d = 0; d < Dimension; ++ d )								\
			{												                            \
				size[d]    = dimensions[d];												\
				start[d]   = 0;															\
				origin[d]  = 0;															\
				spacing[d] = 1;															\
			}																			\
																						\
			ImportFilterType::RegionType region;										\
			region.SetIndex( start );													\
			region.SetSize( size );														\
																						\
			ImportFilterType::Pointer importFilter = ImportFilterType::New();			\
			importFilter->SetRegion( region );											\
			importFilter->SetOrigin( origin );											\
			importFilter->SetSpacing( spacing );										\
			importFilter->SetImportPointer(	pixelBuffer, size[0] * size[1], false );	\
			importFilter->Update();														\
																						\
			/* Since Itk objects are reference-counted, we need to manually   */		\
			/* increment the reference count of the resulting image, to avoid */		\
			/* the importFilter instance to destroy it.                       */		\
			/*                                                                */		\
			importFilter->GetOutput()->Register();										\
																						\
			mItkImage = new SoItkDataImage( TypeFlag, ComponentLayoutFlag, Dimension,	\
				inputImage->getModelMatrix() );											\
			mItkImage->ref();															\
			mItkImage->addRef( radImage );												\
			mItkImage->setPointer( importFilter->GetOutput() );							\
		}

		switch( imageDimension )
		{
			case 2:
			{
				switch( inputImage->getType() )                                      
				{
					case SbXipImage::UNSIGNED_SHORT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE(unsigned short, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::LUMINANCE, 2);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<unsigned short>, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::RGB, 2);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<unsigned short>, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::RGBA, 2);
							}
							break;
						}
					}
					break ;
					case SbXipImage::FLOAT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE( float, SoItkDataImage::FLOAT, SoItkDataImage::LUMINANCE, 2);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<float>, SoItkDataImage::FLOAT, SoItkDataImage::RGB, 2);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<float>, SoItkDataImage::FLOAT, SoItkDataImage::RGBA, 2);
							}
							break;
						}
					}
					break ;
					case SbXipImage::SHORT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE( short, SoItkDataImage::SHORT, SoItkDataImage::LUMINANCE, 2);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<short>, SoItkDataImage::SHORT, SoItkDataImage::RGB, 2);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<short>, SoItkDataImage::SHORT, SoItkDataImage::RGBA, 2);
							}
							break;
						}
					}
					break ;
					case SbXipImage::UNSIGNED_BYTE:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE(unsigned char, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::LUMINANCE, 2);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<unsigned char>, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::RGB, 2);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<unsigned char>, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::RGBA, 2);
							}
							break;
						}
					}
					break ;
				}
			}
			break;
			case 3:
			{
				switch( inputImage->getType() )                                      
				{
					case SbXipImage::UNSIGNED_SHORT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE(unsigned short, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::LUMINANCE, 3);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<unsigned short>, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::RGB, 3);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<unsigned short>, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::RGBA, 3);
							}
							break;
						}
					}
					break ;
					case SbXipImage::FLOAT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE( float, SoItkDataImage::FLOAT, SoItkDataImage::LUMINANCE, 3);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<float>, SoItkDataImage::FLOAT, SoItkDataImage::RGB, 3);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<float>, SoItkDataImage::FLOAT, SoItkDataImage::RGBA, 3);
							}
							break;
						}
					}
					break ;
					case SbXipImage::SHORT:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE( short, SoItkDataImage::SHORT, SoItkDataImage::LUMINANCE, 3);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<short>, SoItkDataImage::SHORT, SoItkDataImage::RGB, 3);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<short>, SoItkDataImage::SHORT, SoItkDataImage::RGBA, 3);
							}
							break;
						}
					}
					break ;
					case SbXipImage::UNSIGNED_BYTE:     
					{
						switch( inputImage->getComponentLayoutType() )                                      
						{
							case SbXipImage::LUMINANCE :
							{
								CREATE_RADITK_IMAGE(unsigned char, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::LUMINANCE, 3);
							}
							break;
							case SbXipImage::RGB :
							{
								CREATE_RADITK_IMAGE(itk::RGBPixel<unsigned char>, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::RGB, 3);
							}
							break;
							case SbXipImage::RGBA :
							{
								CREATE_RADITK_IMAGE(itk::RGBAPixel<unsigned char>, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::RGBA, 3);
							}
							break;
						}
					}
					break ;
				}
			}
			break;
		}
#undef CREATE_RADITK_IMAGE
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

	SO_ENGINE_OUTPUT( output, SoItkSFDataImage, setValue( mItkImage ) );
}

SoField* 
SoItkConvertXipImageToItkImage::getInput( SoType type )
{
	if( type == SoXipSFDataImage::getClassTypeId() )
	{
		return &input;
	}

	SoDebugError::post( __FILE__, "SoItkConvertXipImageToItkImage::getOutput() : unresolved input" );
	return 0;
}

SoEngineOutput* 
SoItkConvertXipImageToItkImage::getOutput( SoType type )
{
	if( type == SoItkSFDataImage::getClassTypeId() )
	{
		return &output;
	}

	SoDebugError::post( __FILE__, "SoItkConvertXipImageToItkImage::getOutput() : unresolved output" );
	return 0;
}
