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
#include <itkImageToImageMetric.h>
#include <xip/inventor/itk/SoItkDataImageMetric.h>

XIP_DATA_SOURCE( SoItkDataImageMetric );

SoItkDataImageMetric::SoItkDataImageMetric()
{
	XIP_DATA_CONSTRUCTOR( SoItkDataImageMetric );

	mItkImageMetric = 0;
	mPixelType = UNSIGNED_SHORT;
	mDimension = 0;
}

SoItkDataImageMetric::SoItkDataImageMetric( PixelTypeEnum pixelType, unsigned int dimension )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataImageMetric );

	mItkImageMetric = 0;
	mPixelType = pixelType;
	mDimension = dimension;
}

SoItkDataImageMetric::SoItkDataImageMetric( const SoItkDataImageMetric& other )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataImageMetric );

	mItkImageMetric = other.mItkImageMetric;
	mPixelType = other.mPixelType;
	mDimension = other.mDimension;
}

SoItkDataImageMetric::~SoItkDataImageMetric()
{
	if( mItkImageMetric )
	{
		// Itk objects are reference counted so there is no way to destroy
		// directly an object. Use Unregister() to decrement the reference
		// counter.
		//
        typedef itk::Object ImageMetricType;
        ImageMetricType* metric = static_cast< ImageMetricType* >( mItkImageMetric );
        metric->UnRegister();

		mItkImageMetric = 0;
	}
}

void 
SoItkDataImageMetric::initClass()
{	
	XIP_DATA_INIT_CLASS( SoItkDataImageMetric, SoXipData, "SoXipData" );	
}

void 
SoItkDataImageMetric::setPointer( void* itkImageMetric )
{
	mItkImageMetric = itkImageMetric;
}

void*
SoItkDataImageMetric::getPointer() const
{
	return mItkImageMetric;
}

SoItkDataImageMetric::PixelTypeEnum
SoItkDataImageMetric::getPixelType() const
{
	return mPixelType;
}

unsigned int
SoItkDataImageMetric::getDimension() const
{
	return mDimension;
}
