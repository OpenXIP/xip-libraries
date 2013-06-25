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
#include <itkInterpolateImageFunction.h>
#include <xip/inventor/itk/SoItkDataInterpolator.h>

XIP_DATA_SOURCE( SoItkDataInterpolator );

SoItkDataInterpolator::SoItkDataInterpolator()
{
	XIP_DATA_CONSTRUCTOR( SoItkDataInterpolator );

	mItkInterpolator = 0;
	mPixelType = UNSIGNED_SHORT;
	mDimension = 0;
}

SoItkDataInterpolator::SoItkDataInterpolator( PixelTypeEnum pixelType, unsigned int dimension )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataInterpolator );

	mItkInterpolator = 0;
	mPixelType = pixelType;
	mDimension = dimension;
}

SoItkDataInterpolator::SoItkDataInterpolator( const SoItkDataInterpolator& other )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataInterpolator );

	mItkInterpolator = other.mItkInterpolator;
	mPixelType = other.mPixelType;
	mDimension = other.mDimension;
}

SoItkDataInterpolator::~SoItkDataInterpolator()
{
	if( mItkInterpolator )
	{
		// Itk objects are reference counted so there is no way to destroy
		// directly an object. Use Unregister() to decrement the reference
		// counter.
		//
        typedef itk::Object InterpolatorType;
        InterpolatorType* interpolator = static_cast< InterpolatorType* >( mItkInterpolator );
        interpolator->UnRegister();

		mItkInterpolator = 0;
	}
}

void 
SoItkDataInterpolator::initClass()
{	
	XIP_DATA_INIT_CLASS( SoItkDataInterpolator, SoXipData, "SoXipData" );	
}

void 
SoItkDataInterpolator::setPointer( void* itkInterpolator )
{
	mItkInterpolator = itkInterpolator;
}

void*
SoItkDataInterpolator::getPointer() const
{
	return mItkInterpolator;
}

SoItkDataInterpolator::PixelTypeEnum
SoItkDataInterpolator::getPixelType() const
{
	return mPixelType;
}

unsigned int
SoItkDataInterpolator::getDimension() const
{
	return mDimension;
}
