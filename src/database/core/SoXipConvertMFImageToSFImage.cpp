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

#include <Inventor/SoDB.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include "SoXipConvertMFImageToSFImage.h"

SO_ENGINE_SOURCE( SoXipConvertMFImageToSFImage );

SoXipConvertMFImageToSFImage::SoXipConvertMFImageToSFImage()
{
   // Do standard constructor tasks
   SO_ENGINE_CONSTRUCTOR( SoXipConvertMFImageToSFImage );

   // Define input field and its default value
   SO_ENGINE_ADD_INPUT( input, (0) );
   input.setNum(0);

   // Define the output, specifying its type
   SO_ENGINE_ADD_OUTPUT( output, SoXipSFDataImage );
}

SoXipConvertMFImageToSFImage::~SoXipConvertMFImageToSFImage()
{

}

void
SoXipConvertMFImageToSFImage::initClass()
{
   SO_ENGINE_INIT_CLASS( SoXipConvertMFImageToSFImage,
	   SoFieldConverter, "FieldConverter");

   // Register this converter's type with the Inventor database
   // to convert from a field (or engine output) of type
   // SoXipMFDataImage to a field of type SoXipSFDataImage.
   // We only call this once, since this engine offers only one
   // type conversion.
   SoDB::addConverter( SoXipMFDataImage::getClassTypeId(),
	   SoXipSFDataImage::getClassTypeId(),
	   getClassTypeId() );
}

void 
SoXipConvertMFImageToSFImage::evaluate()
{
	SoXipDataImage* imageData = 0;
	if( input.getNum() )
		imageData = input[0];
	
	SO_ENGINE_OUTPUT( output, SoXipSFDataImage, setValue(imageData) );
}

SoField*
SoXipConvertMFImageToSFImage::getInput( SoType )
{
   return &input;
}

SoEngineOutput*
SoXipConvertMFImageToSFImage::getOutput( SoType )
{
   return &output;
}

