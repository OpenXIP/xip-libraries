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
#include <xip/inventor/core/SoXipMFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include "SoXipConvertSFImageToMFImage.h"

SO_ENGINE_SOURCE( SoXipConvertSFImageToMFImage );

SoXipConvertSFImageToMFImage::SoXipConvertSFImageToMFImage()
{
   // Do standard constructor tasks
   SO_ENGINE_CONSTRUCTOR( SoXipConvertSFImageToMFImage );

   // Define input field and its default value
   SO_ENGINE_ADD_INPUT(input, (0));

   // Define the output, specifying its type
   SO_ENGINE_ADD_OUTPUT( output, SoXipMFDataImage );
}


SoXipConvertSFImageToMFImage::~SoXipConvertSFImageToMFImage()
{

}

void 
SoXipConvertSFImageToMFImage::initClass()
{
   SO_ENGINE_INIT_CLASS( SoXipConvertSFImageToMFImage,
	   SoFieldConverter, "FieldConverter" );

   // Register this converter's type with the Inventor database
   // to convert from a field (or engine output) of type
   // SoXipSFDataImage to a field of type SoXipMFDataImage.
   // We only call this once, since this engine offers only one
   // type conversion.
   SoDB::addConverter( SoXipSFDataImage::getClassTypeId(),
	   SoXipMFDataImage::getClassTypeId(),
	   getClassTypeId() );
}

void 
SoXipConvertSFImageToMFImage::evaluate()
{
	SO_ENGINE_OUTPUT( output, SoXipMFDataImage, setValue( input.getValue() ) );
}
SoField*
SoXipConvertSFImageToMFImage::getInput( SoType )
{
   return &input;
}

SoEngineOutput*
SoXipConvertSFImageToMFImage::getOutput( SoType )
{
   return &output;
}
