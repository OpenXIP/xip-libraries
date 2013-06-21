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
#include <itkTransform.h>
#include <xip/inventor/itk/SoItkDataTransform.h>

XIP_DATA_SOURCE( SoItkDataTransform );

SoItkDataTransform::SoItkDataTransform()
{
	XIP_DATA_CONSTRUCTOR( SoItkDataTransform );

	mItkTransform = 0;
	mPixelType = UNDEFINED;
	mNumDimension = 0;
}

SoItkDataTransform::SoItkDataTransform( pixel_type_t pixelType, unsigned int numDimension )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataTransform );

	mItkTransform = 0;
	mPixelType = pixelType;
	mNumDimension = numDimension;
}

SoItkDataTransform::SoItkDataTransform( const SoItkDataTransform& other )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataTransform );

	mItkTransform = other.mItkTransform;
	mPixelType = other.mPixelType;
	mNumDimension = other.mNumDimension;
}

SoItkDataTransform::~SoItkDataTransform()
{
	if( mItkTransform )
	{
		// Itk objects are reference counted so there is no way to destroy
		// directly an object. Use Unregister() to decrement the reference
		// counter.
		//
        typedef itk::TransformBase TransformType;
        TransformType* transform = static_cast< TransformType* >( mItkTransform );
        transform->UnRegister();

		mItkTransform = 0;
	}
}

void 
SoItkDataTransform::initClass()
{
	XIP_DATA_INIT_CLASS( SoItkDataTransform, SoXipData, "SoXipData" );	
}

void 
SoItkDataTransform::setPointer( void* itkTransform )
{
	mItkTransform = itkTransform;
}

SoItkDataTransform::pixel_type_t
SoItkDataTransform::getType() const
{
	return mPixelType;
}

unsigned int
SoItkDataTransform::getNumDimension() const
{
	return mNumDimension;
}

void*
SoItkDataTransform::getPointer() const
{
	return mItkTransform;
}
