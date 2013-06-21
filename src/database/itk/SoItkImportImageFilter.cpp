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


#include <xip/inventor/core/XipStringUtils.h>

#include <itkImportImageFilter.h>
#include <xip/inventor/itk/SoItkSFDataImage.h>
#include "SoItkImportImageFilter.h"
#include <fstream>

SO_ENGINE_SOURCE( SoItkImportImageFilter );

SoItkImportImageFilter::SoItkImportImageFilter()
{
	// Do standard constructor stuff
	SO_ENGINE_CONSTRUCTOR( SoItkImportImageFilter );

	// Enumerations
	SO_ENGINE_DEFINE_ENUM_VALUE( OutputPixelTypeEnum, FLOAT );
	SO_ENGINE_DEFINE_ENUM_VALUE( OutputPixelTypeEnum, UNSIGNED_SHORT );

	// Define input fields and their default values
	SO_ENGINE_SET_SF_ENUM_TYPE( Type, OutputPixelTypeEnum );
	SO_ENGINE_ADD_INPUT( File, ("") );
	SO_ENGINE_ADD_INPUT( Type, (FLOAT) );
	SO_ENGINE_ADD_INPUT( Width, (0) );
	SO_ENGINE_ADD_INPUT( Height, (0) );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( Output, SoItkSFDataImage );
	mOutput = 0;
}

SoItkImportImageFilter::~SoItkImportImageFilter()
{
	if( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
	}
}

void 
SoItkImportImageFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkImportImageFilter, SoEngine, "SoEngine" );
}

void*
SoItkImportImageFilter::loadBuffer()
{
	const char* filename = File.getValue().getString();

	int imageWidth = Width.getValue();
	int imageHeight = Height.getValue();
	
#ifdef WIN32
    //assuming everything is done using the bad backslashes... so we convert all forward slashes to those
    const char * fileLocal = XipReplaceChar(filename, '/', '\\').getString();
#else //UNIX
    //assuming the other way around since we need forward slashes now...
    const char * fileLocal = XipReplaceChar(filename, '\\', '/').getString();
#endif //WIN32

	std::ifstream fileIn( fileLocal, std::ios::in | std::ios::binary );

	if( !fileIn.is_open() )
	{
		SoDebugError::post( __FILE__, "Cannot Open File" );
		return 0;
	}

	long fileSize = fileIn.tellg();
	fileIn.seekg( 0, std::ios::end );
	long endPos = fileIn.tellg();
	fileSize = endPos - fileSize;
	fileIn.seekg( 0, std::ios::beg );

	long numElements = imageWidth * imageHeight;
	long bufferSize = numElements * sizeof( unsigned short );

	if( fileSize < bufferSize )
	{
		SoDebugError::post( __FILE__, "Invalid File Size" );
		return 0;
	}
	
	char* pixelBuffer = new char[ bufferSize ];

	fileIn.read( pixelBuffer, bufferSize );
	fileIn.close();

	return pixelBuffer;
}

void 
SoItkImportImageFilter::evaluate()
{
	if( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
		SO_ENGINE_OUTPUT( Output, SoItkSFDataImage, setValue( 0 ) );
	}

	unsigned short width = Width.getValue();
	unsigned short height = Height.getValue();

	if( width <= 0 || height <= 0 || File.getValue().getLength() <= 0 )
		return ;

	try
	{
		#define DO_IT( type, typeFlag )                                          \
		{                                                                        \
			type* pixelBuffer = (type *) loadBuffer();                           \
			if( !pixelBuffer )                                                   \
				return ;                                                         \
                                                                                 \
			typedef itk::ImportImageFilter< type, 2 > ImportFilterType;          \
																				 \
			ImportFilterType::Pointer import = ImportFilterType::New();          \
                                                                                 \
			ImportFilterType::SizeType size;                                     \
				size[0] = Width.getValue();                                      \
				size[1] = Height.getValue();                                     \
                                                                                 \
			ImportFilterType::IndexType start;                                   \
				start[0] = 0;                                                    \
				start[1] = 0;                                                    \
				                                                                 \
	 		ImportFilterType::RegionType region;                                 \
				region.SetIndex( start );                                        \
				region.SetSize( size );                                          \
				                                                                 \
			import->SetRegion( region );                                         \
				                                                                 \
			double origin[2];                                                    \
				origin[0] = 0.0;                                                 \
				origin[1] = 0.0;                                                 \
				                                                                 \
			import->SetOrigin( origin );                                         \
                                                                                 \
			double spacing[2];                                                   \
				spacing[0] = 1.0;                                                \
				spacing[1] = 1.0;                                                \
                                                                                 \
			import->SetSpacing( spacing );                                       \
			import->SetImportPointer( pixelBuffer, size[0] * size[1], false );   \
			import->Update();                                                    \
																				 \
			/* Since Itk objects are reference-counted, we need to manually   */ \
			/* increment the reference count of the resulting image, to avoid */ \
			/* the importFilter instance to destroy it.                       */ \
																				 \
			import->GetOutput()->Register();                                     \
																				 \
			mOutput = new SoItkDataImage( SoItkDataImage::typeFlag, 2 );         \
			mOutput->ref();                                                      \
			mOutput->setPointer( import->GetOutput() );                          \
		}

		#define CASE( type, typeFlag )                                           \
			case typeFlag:                                                       \
				DO_IT( type, typeFlag );                                         \
				break ;

		switch( Type.getValue() )
		{
			CASE( unsigned short, UNSIGNED_SHORT );
			CASE(          float,          FLOAT );
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