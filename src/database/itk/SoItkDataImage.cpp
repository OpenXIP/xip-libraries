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
#include <itkImageBase.h>
#include <xip/inventor/itk/SoItkDataImage.h>

XIP_DATA_SOURCE( SoItkDataImage );

SoItkDataImage::SoItkDataImage()
{
	XIP_DATA_CONSTRUCTOR( SoItkDataImage );

	mItkImage				= 0;
	mDataType				= UNDEFINED;
	mNumDimension			= 0;
	mComponentLayoutType	= LUMINANCE;
}

SoItkDataImage::SoItkDataImage( DataType type, unsigned int numDimension, const SbMatrix& modelMatrix )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataImage );

	mItkImage				= 0;
	mDataType				= type;
	mComponentLayoutType	= LUMINANCE;
	mNumDimension			= numDimension;
	mModelMatrix			= modelMatrix;
}

SoItkDataImage::SoItkDataImage( DataType type, ComponentLayoutType componentLayoutType,
							    unsigned int numDimension, const SbMatrix& modelMatrix )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataImage );

	mItkImage				= 0;
	mDataType				= type;
	mNumDimension			= numDimension;
	mModelMatrix			= modelMatrix;
	mComponentLayoutType	= componentLayoutType;
}

SoItkDataImage::SoItkDataImage( const SoItkDataImage& other )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataImage );

	// FIXME : since it's void, reference counting won't work...
	mItkImage				= other.mItkImage;
	mDataType				= other.mDataType;
	mComponentLayoutType	= other.mComponentLayoutType;
	mNumDimension			= other.mNumDimension;
	mModelMatrix			= other.mModelMatrix;	
}

SoItkDataImage::~SoItkDataImage()
{
	if( mItkImage )
	{
		// Itk objects are reference counted so there is no way to destroy
		// directly an object. Use Unregister() to decrement the reference
		// counter.
		//		
		if( mNumDimension == 2 )
		{
			typedef itk::ImageBase< 2 > ImageType;
			
			ImageType* itkImage2D = static_cast< ImageType* >( mItkImage );
			itkImage2D->UnRegister();
		}
		else if( mNumDimension == 3 )
		{
			typedef itk::ImageBase< 3 > ImageType;
			
			ImageType* itkImage3D = static_cast< ImageType* >( mItkImage );
			itkImage3D->UnRegister();
		}

		mItkImage = 0;
	}
}

void 
SoItkDataImage::initClass()
{	
	XIP_DATA_INIT_CLASS( SoItkDataImage, SoXipData, "SoXipData" );	
}

void 
SoItkDataImage::setPointer( const void* itkImage )
{
	mItkImage = const_cast< void* >( itkImage );
}

SoItkDataImage::DataType
SoItkDataImage::getType() const
{
	return mDataType;
}

SoItkDataImage::ComponentLayoutType
SoItkDataImage::getComponentLayoutType() const
{
	return mComponentLayoutType;
}

unsigned int
SoItkDataImage::getDimension( unsigned int i ) const
{
	if( mItkImage )
	{
		if( mNumDimension == 2 )
		{
			typedef itk::ImageBase< 2 > ImageType;
			
			ImageType* itkImage2D = static_cast< ImageType* >( mItkImage );
			return itkImage2D->GetLargestPossibleRegion().GetSize()[ i ];
		}
		else if( mNumDimension == 3 )
		{
			typedef itk::ImageBase< 3 > ImageType;
			
			ImageType* itkImage3D = static_cast< ImageType* >( mItkImage );
			return itkImage3D->GetLargestPossibleRegion().GetSize()[ i ];
		}
	}

	return 0;
}

unsigned int
SoItkDataImage::getNumDimension() const
{
	return mNumDimension;
}

void*
SoItkDataImage::getPointer() const
{
	return mItkImage;
}

const SbMatrix&
SoItkDataImage::getModelMatrix() const
{
	return mModelMatrix;
}
