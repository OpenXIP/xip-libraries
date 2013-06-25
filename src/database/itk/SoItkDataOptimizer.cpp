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
#include <itkOptimizer.h>
#include <xip/inventor/itk/SoItkDataOptimizer.h>

XIP_DATA_SOURCE( SoItkDataOptimizer );

SoItkDataOptimizer::SoItkDataOptimizer()
{
	XIP_DATA_CONSTRUCTOR( SoItkDataOptimizer );

	mItkOptimizer = 0;
}

SoItkDataOptimizer::SoItkDataOptimizer( const SoItkDataOptimizer& other )
{
	XIP_DATA_CONSTRUCTOR( SoItkDataOptimizer );

	mItkOptimizer = other.mItkOptimizer;
}

SoItkDataOptimizer::~SoItkDataOptimizer()
{
	if( mItkOptimizer )
	{
		// Itk objects are reference counted so there is no way to destroy
		// directly an object. Use Unregister() to decrement the reference
		// counter.
		//
        itk::Object* optimizer = static_cast< itk::Object* >( mItkOptimizer );
        optimizer->UnRegister();

		mItkOptimizer = 0;
	}
}

void 
SoItkDataOptimizer::initClass()
{
	XIP_DATA_INIT_CLASS( SoItkDataOptimizer, SoXipData, "SoXipData" );
}

void 
SoItkDataOptimizer::setPointer( void* itkOptimizer )
{
	mItkOptimizer = itkOptimizer;
}

void*
SoItkDataOptimizer::getPointer() const
{
	return mItkOptimizer;
}
