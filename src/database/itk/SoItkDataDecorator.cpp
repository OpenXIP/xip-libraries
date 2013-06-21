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
#include <itkSimpleDataObjectDecorator.h>
#include <xip/inventor/itk/SoItkDataDecorator.h>

XIP_DATA_SOURCE( SoItkDataDecorator );

SoItkDataDecorator::SoItkDataDecorator()
{
	XIP_DATA_CONSTRUCTOR( SoItkDataDecorator );

	mItkDecorator = 0;
	mPixelType = UNSIGNED_SHORT;
}

SoItkDataDecorator::SoItkDataDecorator( pixel_type_t pixelType )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataDecorator );

	mItkDecorator = 0;
	mPixelType = pixelType;
}

SoItkDataDecorator::SoItkDataDecorator( const SoItkDataDecorator& other )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataDecorator );

	mItkDecorator = other.mItkDecorator;
	mPixelType = other.mPixelType;
}

SoItkDataDecorator::~SoItkDataDecorator()
{
	if( mItkDecorator )
	{
		// Itk objects are reference counted so there is no way to destroy
		// directly an object. Use Unregister() to decrement the reference
		// counter.
		//
        typedef itk::Object DecoratorType;
        DecoratorType* Decorator = static_cast< DecoratorType* >( mItkDecorator );
        Decorator->UnRegister();

		mItkDecorator = 0;
	}
}

void 
SoItkDataDecorator::initClass()
{
	XIP_DATA_INIT_CLASS( SoItkDataDecorator, SoXipData, "SoXipData" );	
}

void 
SoItkDataDecorator::setPointer( void* itkDecorator )
{
	mItkDecorator = itkDecorator;
}

SoItkDataDecorator::pixel_type_t
SoItkDataDecorator::getType() const
{
	return mPixelType;
}

void*
SoItkDataDecorator::getPointer() const
{
	return mItkDecorator;
}
