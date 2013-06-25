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
#include <xip/inventor/itk/SoItkMFDataImage.h>
#include "SoItkComposeMFDataImage.h"

SO_ENGINE_SOURCE( SoItkComposeMFDataImage );

SoItkComposeMFDataImage::SoItkComposeMFDataImage()
{
	SO_ENGINE_CONSTRUCTOR( SoItkComposeMFDataImage );

	SO_ENGINE_ADD_INPUT( input1, (0) );
	SO_ENGINE_ADD_INPUT( input2, (0) );
	SO_ENGINE_ADD_INPUT( input3, (0) );
	SO_ENGINE_ADD_INPUT( input4, (0) );
	SO_ENGINE_ADD_INPUT( input5, (0) );
	SO_ENGINE_ADD_INPUT( input6, (0) );
	SO_ENGINE_ADD_INPUT( input7, (0) );
	SO_ENGINE_ADD_INPUT( input8, (0) );

	SO_ENGINE_ADD_OUTPUT( output, SoItkMFDataImage );
}

SoItkComposeMFDataImage::~SoItkComposeMFDataImage()
{

}

void
SoItkComposeMFDataImage::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkComposeMFDataImage, SoEngine, "Engine" );
}

void
SoItkComposeMFDataImage::evaluate()
{
	SoItkMFDataImage tmp;
	tmp.setNum(8);

	SoItkDataImage** tmpPtr = tmp.startEditing();
	{
		tmpPtr[0] = input1.getValue();
		tmpPtr[1] = input2.getValue();
		tmpPtr[2] = input3.getValue();
		tmpPtr[3] = input4.getValue();
		tmpPtr[4] = input5.getValue();
		tmpPtr[5] = input6.getValue();
		tmpPtr[6] = input7.getValue();
		tmpPtr[7] = input8.getValue();
	}
	tmp.finishEditing();

	SO_ENGINE_OUTPUT( output, SoItkMFDataImage, copyFrom(tmp) );
}
