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
#include <itkPointSet.h>
#include <xip/inventor/itk/SoItkDataPointSet.h>

XIP_DATA_SOURCE( SoItkDataPointSet );

SoItkDataPointSet::SoItkDataPointSet()
{
	XIP_DATA_CONSTRUCTOR( SoItkDataPointSet );

	mItkPointSet = 0;
	mPixelType = UNSIGNED_SHORT;
	mDimension = 0;
}

SoItkDataPointSet::SoItkDataPointSet( PixelTypeEnum pixelType, unsigned int dimension )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataPointSet );

	mItkPointSet = 0;
	mPixelType = pixelType;
	mDimension = dimension;
}

SoItkDataPointSet::SoItkDataPointSet( const SoItkDataPointSet& other )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataPointSet );

	mItkPointSet = other.mItkPointSet;
	mPixelType = other.mPixelType;
	mDimension = other.mDimension;
}

SoItkDataPointSet::~SoItkDataPointSet()
{
	if( mItkPointSet )
	{
		// Itk objects are reference counted so there is no way to destroy
		// directly an object. Use Unregister() to decrement the reference
		// counter.
		//
        typedef itk::Object PointSetType;
        PointSetType* pointset = static_cast< PointSetType* >( mItkPointSet );
        pointset->UnRegister();

		mItkPointSet = 0;
	}
}

void 
SoItkDataPointSet::initClass()
{
	XIP_DATA_INIT_CLASS( SoItkDataPointSet, SoXipData, "SoXipData" );	
}

void 
SoItkDataPointSet::setPointer( void* itkPointSet )
{
	mItkPointSet = itkPointSet;
}

void*
SoItkDataPointSet::getPointer() const
{
	return mItkPointSet;
}

SoItkDataPointSet::PixelTypeEnum
SoItkDataPointSet::getPixelType() const
{
	return mPixelType;
}

unsigned int
SoItkDataPointSet::getDimension() const
{
	return mDimension;
}
