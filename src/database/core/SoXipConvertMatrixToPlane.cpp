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
#include <xip/inventor/core/XipGeomUtils.h>
#include "SoXipConvertMatrixToPlane.h"

SO_ENGINE_SOURCE(SoXipConvertMatrixToPlane);

// Initializes the SoXipConvertMatrixToPlane class.

void SoXipConvertMatrixToPlane::initClass()
{
   SO_ENGINE_INIT_CLASS(SoXipConvertMatrixToPlane,
                        SoFieldConverter, "FieldConverter");

   // Register this converter's type with the Inventor database
   // to convert from a field (or engine output) of type
   // SoSFShort to a field of type SoSFFloat.
   // We only call this once, since this engine offers only one
   // type conversion.
   SoDB::addConverter(SoSFMatrix::getClassTypeId(),
                      SoSFPlane::getClassTypeId(),
                      getClassTypeId());
}

// Constructor

SoXipConvertMatrixToPlane::SoXipConvertMatrixToPlane()
{
   // Do standard constructor tasks
   SO_ENGINE_CONSTRUCTOR(SoXipConvertMatrixToPlane);

   // Define input field and its default value
   SO_ENGINE_ADD_INPUT(input, (SbMatrix::identity()));

   // Define the output, specifying its type
   SO_ENGINE_ADD_OUTPUT(output, SoSFPlane);
}

// Destructor. Does nothing.

SoXipConvertMatrixToPlane::~SoXipConvertMatrixToPlane()
{
}

// This is the evaluation routine.

void SoXipConvertMatrixToPlane::evaluate()
{
	SO_ENGINE_OUTPUT(output, SoSFPlane, setValue(XipGeomUtils::planeFromMatrix(input.getValue())));
}

// This returns the input field for the given type. Since we
// have only one input field, we don't have to check the type.

SoField *SoXipConvertMatrixToPlane::getInput(SoType)
{
	return &input;
}

// This does the same for the output.

SoEngineOutput *SoXipConvertMatrixToPlane::getOutput(SoType)
{
	return &output;
}
