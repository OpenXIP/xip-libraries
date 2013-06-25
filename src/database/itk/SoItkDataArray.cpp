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
#include <itkArray.h>
#include <xip/inventor/itk/SoItkDataArray.h>

XIP_DATA_SOURCE( SoItkDataArray );

SoItkDataArray::SoItkDataArray()
{
	XIP_DATA_CONSTRUCTOR( SoItkDataArray );

	mItkArray = 0;
	mValueType = UNDEFINED;
	mNumElements = 0;
}

SoItkDataArray::SoItkDataArray( ValueType valueType, unsigned int numElements )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataArray );

	mItkArray = 0;
	mValueType = valueType;
	mNumElements = numElements;
}

SoItkDataArray::SoItkDataArray( const SoItkDataArray& other )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataArray );

	mItkArray = other.mItkArray;
	mValueType = other.mValueType;
	mNumElements = other.mNumElements;
}

SoItkDataArray::~SoItkDataArray()
{
	if( mItkArray )
	{
		// Itk objects are reference counted so there is no way to destroy
		// directly an object. Use Unregister() to decrement the reference
		// counter.
		//
		switch( mValueType )
		{
		case UNSIGNED_SHORT:
			{
				typedef itk::Array< unsigned short > ArrayType;
				ArrayType* array = static_cast< ArrayType* >( mItkArray );
				delete array;
			}
			break ;

		case FLOAT:
			{
				typedef itk::Array< float > ArrayType;
				ArrayType* array = static_cast< ArrayType* >( mItkArray );
				delete array;
			}
			break ;

		case DOUBLE:
			{
				typedef itk::Array< double > ArrayType;
				ArrayType* array = static_cast< ArrayType* >( mItkArray );
				delete array;
			}
			break ;
		}
		mItkArray = 0;
	}
}

void 
SoItkDataArray::initClass()
{
	XIP_DATA_INIT_CLASS( SoItkDataArray, SoXipData, "SoXipData" );	
}

void 
SoItkDataArray::setPointer( void* itkArray )
{
	mItkArray = itkArray;
}

void*
SoItkDataArray::getPointer() const
{
	return mItkArray;
}

SoItkDataArray::ValueType
SoItkDataArray::getValueType() const
{
	return mValueType;
}

unsigned int
SoItkDataArray::getNumElements() const
{
	return mNumElements;
}
