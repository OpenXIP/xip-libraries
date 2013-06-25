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
#include <xip/inventor/itk/SoItkDataNeighborhood.h>

XIP_DATA_SOURCE( SoItkDataNeighborhood );

SoItkDataNeighborhood::SoItkDataNeighborhood()
{
	XIP_DATA_CONSTRUCTOR( SoItkDataNeighborhood );

	mItkNeighborhood = 0;
	mPixelType = UNDEFINED;
	mNumDimension = 0;
}

SoItkDataNeighborhood::SoItkDataNeighborhood( pixel_type_t pixelType, unsigned int numDimension )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataNeighborhood );

	mItkNeighborhood = 0;
	mPixelType = pixelType;
	mNumDimension = numDimension;
}

SoItkDataNeighborhood::SoItkDataNeighborhood( const SoItkDataNeighborhood& other )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataNeighborhood );

	mItkNeighborhood = other.mItkNeighborhood;
	mPixelType = other.mPixelType;
	mNumDimension = other.mNumDimension;
}

SoItkDataNeighborhood::~SoItkDataNeighborhood()
{
	if( mItkNeighborhood )
	{
		// Itk objects are reference counted so there is no way to destroy
		// directly an object. Use Unregister() to decrement the reference
		// counter.
		//
        delete mItkNeighborhood;
		mItkNeighborhood = 0;
	}
}

void 
SoItkDataNeighborhood::initClass()
{
	XIP_DATA_INIT_CLASS( SoItkDataNeighborhood, SoXipData, "SoXipData" );		
}

void 
SoItkDataNeighborhood::setPointer( const void* itkNeighborhood )
{
	mItkNeighborhood = const_cast< void* >( itkNeighborhood );
}

SoItkDataNeighborhood::pixel_type_t
SoItkDataNeighborhood::getType() const
{
	return mPixelType;
}

unsigned int
SoItkDataNeighborhood::getNumDimension() const
{
	return mNumDimension;
}

void*
SoItkDataNeighborhood::getPointer() const
{
	return mItkNeighborhood;
}
