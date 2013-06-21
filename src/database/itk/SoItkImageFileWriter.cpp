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
#include <itkImage.h>
#include <itkImageFileWriter.h>
#include <itkRGBPixel.h>
#include <itkRGBAPixel.h>
#include <xip/inventor/itk/SoItkSFDataImage.h>
#include "SoItkImageFileWriter.h"

SO_ENGINE_SOURCE( SoItkImageFileWriter );

SoItkImageFileWriter::SoItkImageFileWriter()
{
	// Do standard constructor stuff
	SO_ENGINE_CONSTRUCTOR( SoItkImageFileWriter );

	// Define input fields and their default values
	SO_ENGINE_ADD_INPUT( File, ("") );
	SO_ENGINE_ADD_INPUT( Input, (0) );
	SO_ENGINE_ADD_INPUT( Write, () );
}

SoItkImageFileWriter::~SoItkImageFileWriter()
{
	
}

void 
SoItkImageFileWriter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkImageFileWriter, SoEngine, "SoEngine" );
}

void
SoItkImageFileWriter::inputChanged( SoField* whichField )
{
	if (whichField != &Write)
		return ;

	SoItkDataImage* inputImage = Input.getValue();

	if( File.getValue().getLength() > 0 && inputImage )
	{
		try
		{
			#define DO_IT( Type, Dimension )										\
			{																		\
				typedef itk::Image< Type, Dimension > InputImageType;				\
				typedef itk::ImageFileWriter< InputImageType > WriterType;			\
																					\
				InputImageType* itkImage =											\
					static_cast< InputImageType* >( inputImage->getPointer() );		\
				if( !itkImage )														\
					return ;														\
																					\
				WriterType::Pointer writer = WriterType::New();						\
				writer->SetFileName( File.getValue().getString() );					\
				writer->SetInput( itkImage );										\
				writer->Update();													\
			}

			switch( inputImage->getNumDimension())
			{
				case 2 :
				{
					switch( inputImage->getType() )
					{
						case SoItkDataImage::UNSIGNED_SHORT:
						{
							switch( inputImage->getComponentLayoutType() )
							{
								case SoItkDataImage::LUMINANCE:
								{
									DO_IT( unsigned short, 2 );
								}
								break;
								case SoItkDataImage::RGB:
								{
									DO_IT( itk::RGBPixel<unsigned short>, 2 );
								}
								break;
								case SoItkDataImage::RGBA:
								{
									DO_IT( itk::RGBAPixel<unsigned short>, 2 );
								}
								break;
							}
						}
						break;
						case SoItkDataImage::FLOAT:
						{
							switch( inputImage->getComponentLayoutType() )
							{
								case SoItkDataImage::LUMINANCE:
								{
									DO_IT( float, 2 );
								}
								break;
								case SoItkDataImage::RGB:
								{
									DO_IT( itk::RGBPixel<float>, 2 );
								}
								break;
								case SoItkDataImage::RGBA:
								{
									DO_IT( itk::RGBAPixel<float>, 2 );
								}
								break;
							}
						}
						break;
						case SoItkDataImage::SHORT:
						{
							switch( inputImage->getComponentLayoutType() )
							{
								case SoItkDataImage::LUMINANCE:
								{
									DO_IT( short, 2 );
								}
								break;
								case SoItkDataImage::RGB:
								{
									DO_IT( itk::RGBPixel<short>, 2 );
								}
								break;
								case SoItkDataImage::RGBA:
								{
									DO_IT( itk::RGBAPixel<short>, 2 );
								}
								break;
							}
						}
						break;
						case SoItkDataImage::UNSIGNED_CHAR:
						{
							switch( inputImage->getComponentLayoutType() )
							{
								case SoItkDataImage::LUMINANCE:
								{
									DO_IT( unsigned char, 2 );
								}
								break;
								case SoItkDataImage::RGB:
								{
									DO_IT( itk::RGBPixel<unsigned char>, 2 );
								}
								break;
								case SoItkDataImage::RGBA:
								{
									DO_IT( itk::RGBAPixel<unsigned char>, 2 );
								}
								break;
							}
						}
						break;
					}
				}
				break;
				case 3 :
				{
					switch( inputImage->getType() )
					{
						case SoItkDataImage::UNSIGNED_SHORT:
						{
							switch( inputImage->getComponentLayoutType() )
							{
								case SoItkDataImage::LUMINANCE:
								{
									DO_IT( unsigned short, 3 );
								}
								break;
								case SoItkDataImage::RGB:
								{
									DO_IT( itk::RGBPixel<unsigned short>, 3 );
								}
								break;
								case SoItkDataImage::RGBA:
								{
									DO_IT( itk::RGBAPixel<unsigned short>, 3 );
								}
								break;
							}
						}
						break;
						case SoItkDataImage::FLOAT:
						{
							switch( inputImage->getComponentLayoutType() )
							{
								case SoItkDataImage::LUMINANCE:
								{
									DO_IT( float, 3 );
								}
								break;
								case SoItkDataImage::RGB:
								{
									DO_IT( itk::RGBPixel<float>, 3 );
								}
								break;
								case SoItkDataImage::RGBA:
								{
									DO_IT( itk::RGBAPixel<float>, 3 );
								}
								break;
							}
						}
						break;
						case SoItkDataImage::SHORT:
						{
							switch( inputImage->getComponentLayoutType() )
							{
								case SoItkDataImage::LUMINANCE:
								{
									DO_IT( short, 3 );
								}
								break;
								case SoItkDataImage::RGB:
								{
									DO_IT( itk::RGBPixel<short>, 3 );
								}
								break;
								case SoItkDataImage::RGBA:
								{
									DO_IT( itk::RGBAPixel<short>, 3 );
								}
								break;
							}
						}
						break;
						case SoItkDataImage::UNSIGNED_CHAR:
						{
							switch( inputImage->getComponentLayoutType() )
							{
								case SoItkDataImage::LUMINANCE:
								{
									DO_IT( unsigned char, 3 );
								}
								break;
								case SoItkDataImage::RGB:
								{
									DO_IT( itk::RGBPixel<unsigned char>, 3 );
								}
								break;
								case SoItkDataImage::RGBA:
								{
									DO_IT( itk::RGBAPixel<unsigned char>, 3 );
								}
								break;
							}
						}
						break;
					}
				}
				break;
			}

			#undef DO_IT
		}
		catch( itk::ExceptionObject& e )
		{
			SoDebugError::post( e.GetFile(), " line %d: %s", e.GetLine(), e.GetDescription() );
			return ;
		}
		catch(...)
		{
			SoDebugError::post( __FILE__, "Unknown Exception" );
			return ;
		}
	}	
}

void
SoItkImageFileWriter::evaluate()
{

}
