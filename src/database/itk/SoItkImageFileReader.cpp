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

#include <itkImageFileReader.h>
#include <itkRGBPixel.h>
#include <itkRGBAPixel.h>
#include <xip/inventor/itk/SoItkSFDataImage.h>
#include <Inventor/fields/SoMFShort.h>
#include "SoItkImageFileReader.h"

SO_ENGINE_SOURCE( SoItkImageFileReader );

SoItkImageFileReader::SoItkImageFileReader()
{
	SO_ENGINE_CONSTRUCTOR( SoItkImageFileReader );

	// Enumerations
	SO_ENGINE_DEFINE_ENUM_VALUE( DataType, FLOAT );
	SO_ENGINE_DEFINE_ENUM_VALUE( DataType, UNSIGNED_SHORT );
	SO_ENGINE_DEFINE_ENUM_VALUE( DataType, SHORT );
	SO_ENGINE_DEFINE_ENUM_VALUE( DataType, UNSIGNED_CHAR );
 
	SO_ENGINE_DEFINE_ENUM_VALUE( DimensionEnum, TWO );
	SO_ENGINE_DEFINE_ENUM_VALUE( DimensionEnum, THREE );

	SO_ENGINE_DEFINE_ENUM_VALUE( ComponentLayoutType, LUMINANCE );
	SO_ENGINE_DEFINE_ENUM_VALUE( ComponentLayoutType, RGB );
	SO_ENGINE_DEFINE_ENUM_VALUE( ComponentLayoutType, RGBA );

	// Define input fields and their default values
	SO_ENGINE_SET_SF_ENUM_TYPE( Type, DataType );
	SO_ENGINE_SET_SF_ENUM_TYPE( Dimension, DimensionEnum );
	SO_ENGINE_SET_SF_ENUM_TYPE( ComponentLayout, ComponentLayoutType );

	SO_ENGINE_ADD_INPUT( File, ("") );
	SO_ENGINE_ADD_INPUT( Type, (FLOAT) );
	SO_ENGINE_ADD_INPUT( Dimension, (TWO) );
	SO_ENGINE_ADD_INPUT( ComponentLayout, (LUMINANCE) );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( Output, SoItkSFDataImage );
	SO_ENGINE_ADD_OUTPUT( Dimensions, SoMFShort );

	mOutput = 0;
}

SoItkImageFileReader::~SoItkImageFileReader()
{
	if( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
	}
}

void 
SoItkImageFileReader::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkImageFileReader, SoEngine, "SoEngine" );
}

void 
SoItkImageFileReader::evaluate()
{
	if( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
		SO_ENGINE_OUTPUT( Output, SoItkSFDataImage, setValue( 0 ) );
		SO_ENGINE_OUTPUT( Dimensions, SoMFShort, setNum( 0 ) );
	}

	if( File.getValue().getLength() <= 0 )
		return ;

	try
	{
		#define DO_IT( Type, ComponentLayoutFlag, TypeFlag, Dimension )				        \
		{                                                                        			\
			typedef itk::Image< Type, Dimension > OutputImageType;							\
			typedef itk::ImageFileReader< OutputImageType > ReaderType;          			\
																				 			\
			ReaderType::Pointer reader = ReaderType::New();                      			\
			reader->SetFileName( File.getValue().getString() );                  			\
			reader->Update();                                                    			\
																				 			\
			/* Since Itk objects are reference-counted, we need to manually   */ 			\
			/* increment the reference count of the resulting image, to avoid */ 			\
			/* the importFilter instance to destroy it.                       */ 			\
																				 			\
			reader->GetOutput()->Register();                                     			\
																				 			\
			mOutput = new SoItkDataImage( TypeFlag, ComponentLayoutFlag, Dimension );		\
			mOutput->ref();                                                      			\
			mOutput->setPointer( reader->GetOutput() );                          			\
			                                                                     			\
			short dims[2];                                                       			\
			dims[0] = mOutput->getDimension( 0 );                                			\
			dims[1] = mOutput->getDimension( 1 );                                			\
			SO_ENGINE_OUTPUT( Dimensions, SoMFShort, setNum(2) );                			\
			SO_ENGINE_OUTPUT( Dimensions, SoMFShort, setValues( 0, 2, dims ) );  			\
		}

		#define CASE( Type, ItkTypeFlag, Dimension, TypeFlag, ComponentLayoutFlag )			\
		{																					\
			case ItkTypeFlag:                                                  				\
				DO_IT( Type, ComponentLayoutFlag, TypeFlag, Dimension )                   	\
				break ;																		\
		}

		switch( Dimension.getValue() )
		{
			case SoItkImageFileReader::TWO :
			{
				switch( ComponentLayout.getValue() )
				{
					case SoItkImageFileReader::LUMINANCE :
					{
						switch( Type.getValue() )
						{
							CASE( unsigned short, SoItkImageFileReader::UNSIGNED_SHORT, 2, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::LUMINANCE);
							CASE( float, SoItkImageFileReader::FLOAT, 2, SoItkDataImage::FLOAT, SoItkDataImage::LUMINANCE);
							CASE( unsigned char, SoItkImageFileReader::UNSIGNED_CHAR, 2, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::LUMINANCE  );
							CASE( short, SoItkImageFileReader::SHORT, 2, SoItkDataImage::SHORT, SoItkDataImage::LUMINANCE  );
						}
					}
					break;
					case SoItkImageFileReader::RGB :
					{
						switch( Type.getValue() )
						{
							CASE( itk::RGBPixel<unsigned short>, SoItkImageFileReader::UNSIGNED_SHORT, 2, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::RGB);
							CASE( itk::RGBPixel<float>, SoItkImageFileReader::FLOAT, 2, SoItkDataImage::FLOAT, SoItkDataImage::RGB );
							CASE( itk::RGBPixel<unsigned char>, SoItkImageFileReader::UNSIGNED_CHAR, 2, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::RGB );
							CASE( itk::RGBPixel<short>, SoItkImageFileReader::SHORT, 2, SoItkDataImage::SHORT, SoItkDataImage::RGB  );
						}
					}
					break;
					case SoItkImageFileReader::RGBA :
					{
						switch( Type.getValue() )
						{
							CASE( itk::RGBAPixel<unsigned short>, SoItkImageFileReader::UNSIGNED_SHORT, 2, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::RGBA);
							CASE( itk::RGBAPixel<float>, SoItkImageFileReader::FLOAT, 2, SoItkDataImage::FLOAT, SoItkDataImage::RGBA );
							CASE( itk::RGBAPixel<unsigned char>, SoItkImageFileReader::UNSIGNED_CHAR, 2, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::RGBA );
							CASE( itk::RGBAPixel<short>, SoItkImageFileReader::SHORT, 2, SoItkDataImage::SHORT, SoItkDataImage::RGBA  );
						}
					}
					break;					
				}
			}
			break;
			case SoItkImageFileReader::THREE :
			{
				switch( ComponentLayout.getValue() )
				{
					case SoItkImageFileReader::LUMINANCE :
					{
						switch( Type.getValue() )
						{
							CASE( unsigned short, SoItkImageFileReader::UNSIGNED_SHORT, 3, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::LUMINANCE);
							CASE( float, SoItkImageFileReader::FLOAT, 3, SoItkDataImage::FLOAT, SoItkDataImage::LUMINANCE);
							CASE( unsigned char, SoItkImageFileReader::UNSIGNED_CHAR, 3, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::LUMINANCE  );
							CASE( short, SoItkImageFileReader::SHORT, 3, SoItkDataImage::SHORT, SoItkDataImage::LUMINANCE  );
						}
					}
					break;
					case SoItkImageFileReader::RGB :
					{
						switch( Type.getValue() )
						{
							CASE( itk::RGBPixel<unsigned short>, SoItkImageFileReader::UNSIGNED_SHORT, 3, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::RGB);
							CASE( itk::RGBPixel<float>, SoItkImageFileReader::FLOAT, 3, SoItkDataImage::FLOAT, SoItkDataImage::RGB );
							CASE( itk::RGBPixel<unsigned char>, SoItkImageFileReader::UNSIGNED_CHAR, 3, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::RGB );
							CASE( itk::RGBPixel<short>, SoItkImageFileReader::SHORT, 3, SoItkDataImage::SHORT, SoItkDataImage::RGB  );
						}
					}
					break;
					case SoItkImageFileReader::RGBA :
					{
						switch( Type.getValue() )
						{
							CASE( itk::RGBAPixel<unsigned short>, SoItkImageFileReader::UNSIGNED_SHORT, 3, SoItkDataImage::UNSIGNED_SHORT, SoItkDataImage::RGBA);
							CASE( itk::RGBAPixel<float>, SoItkImageFileReader::FLOAT, 3, SoItkDataImage::FLOAT, SoItkDataImage::RGBA );
							CASE( itk::RGBAPixel<unsigned char>, SoItkImageFileReader::UNSIGNED_CHAR, 3, SoItkDataImage::UNSIGNED_CHAR, SoItkDataImage::RGBA );
							CASE( itk::RGBAPixel<short>, SoItkImageFileReader::SHORT, 3, SoItkDataImage::SHORT, SoItkDataImage::RGBA  );
						}
					}
					break;					
				}
			}
			break;
		}		

		#undef CASE
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

	SO_ENGINE_OUTPUT( Output, SoItkSFDataImage, setValue( mOutput ) );
}