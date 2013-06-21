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

#include "SoXipSwitchMFDataImage.h"

SO_ENGINE_SOURCE( SoXipSwitchMFDataImage )

SoXipSwitchMFDataImage::SoXipSwitchMFDataImage()
{
	SO_ENGINE_CONSTRUCTOR( SoXipSwitchMFDataImage );

	// Initialize the input parameter
	SO_ENGINE_ADD_INPUT( image1, (0) );
	SO_ENGINE_ADD_INPUT( image2, (0) );
	SO_ENGINE_ADD_INPUT( image3, (0) );
	SO_ENGINE_ADD_INPUT( image4, (0) );
    SO_ENGINE_ADD_INPUT( index, (-1) );

	SO_ENGINE_ADD_OUTPUT( image, SoXipMFDataImage );
}

SoXipSwitchMFDataImage::~SoXipSwitchMFDataImage()
{

}

void
SoXipSwitchMFDataImage::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipSwitchMFDataImage, SoEngine, "Engine" );
}

void
SoXipSwitchMFDataImage::evaluate()
{
	SO_ENGINE_OUTPUT( image, SoXipMFDataImage, setNum(0) );

	try
	{
		// If default value, do nothing
		if( index.getValue() == -1 )
			return ;

		if( index.getValue() < 0 || index.getValue() >= 4 )
		{
			SoDebugError::post( __FILE__, "Index %d out of bounds 0 -- 3", index.getValue() );
			return ;
		}

		SoField* imageFields[4] = { &image1, &image2, &image3, &image4 };

		SO_ENGINE_OUTPUT( image, SoXipMFDataImage, copyFrom(*imageFields[index.getValue()]) );
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unexpected error in SoXipSwitchMFDataImage::evaluate()" );
	}
}
