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
#include <xip/inventor/dicom/SoXipSFDataDicom.h>
#include <xip/inventor/dicom/SoXipDataDicom.h>

#include "SoXipConvertDicom.h"


SO_ENGINE_SOURCE(SoXipConvertMFDicomToSFDicom);


void SoXipConvertMFDicomToSFDicom::initClass()
{
   SO_ENGINE_INIT_CLASS(SoXipConvertMFDicomToSFDicom,
                        SoFieldConverter, "FieldConverter");

   // Register this converter's type with the Inventor database
   // to convert from a field (or engine output) of type
   // SoSFShort to a field of type SoSFFloat.
   // We only call this once, since this engine offers only one
   // type conversion.
   SoDB::addConverter(SoXipMFDataDicom::getClassTypeId(),
                      SoXipSFDataDicom::getClassTypeId(),
                      getClassTypeId());
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SoXipConvertMFDicomToSFDicom::SoXipConvertMFDicomToSFDicom()
{
   // Do standard constructor tasks
   SO_ENGINE_CONSTRUCTOR(SoXipConvertMFDicomToSFDicom);

   // Define input field and its default value
   SO_ENGINE_ADD_INPUT(input, (0));
   SO_ENGINE_ADD_INPUT(index, (0));

   // Define the output, specifying its type
   SO_ENGINE_ADD_OUTPUT(output, SoXipSFDataDicom);

}

SoXipConvertMFDicomToSFDicom::~SoXipConvertMFDicomToSFDicom()
{
}

// This is the evaluation routine.
void SoXipConvertMFDicomToSFDicom::evaluate()
{
	SoXipDataDicom * out = 0;

	int numSlices = input.getNum();
	int sliceId = index.getValue();
	
	if (sliceId >= 0 && sliceId < numSlices)
	{
		out = (SoXipDataDicom*) *(input.getValues(sliceId));
	}

	// set output to NULL
	SO_ENGINE_OUTPUT(output, SoXipSFDataDicom, setValue(out));
}

// This returns the input field for the given type. Since we
// have only one input field, we don't have to check the type.
SoField *SoXipConvertMFDicomToSFDicom::getInput(SoType)
{
   return &input;
}

// This does the same for the output.
SoEngineOutput *SoXipConvertMFDicomToSFDicom::getOutput(SoType)
{
   return &output;
}




SO_ENGINE_SOURCE(SoXipConvertSFDicomToMFDicom);


void SoXipConvertSFDicomToMFDicom::initClass()
{
   SO_ENGINE_INIT_CLASS(SoXipConvertSFDicomToMFDicom,
                        SoFieldConverter, "FieldConverter");

   // Register this converter's type with the Inventor database
   // to convert from a field (or engine output) of type
   // SoSFShort to a field of type SoSFFloat.
   // We only call this once, since this engine offers only one
   // type conversion.
   SoDB::addConverter(SoXipSFDataDicom::getClassTypeId(),
                      SoXipMFDataDicom::getClassTypeId(),
                      getClassTypeId());
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SoXipConvertSFDicomToMFDicom::SoXipConvertSFDicomToMFDicom()
{
   // Do standard constructor tasks
   SO_ENGINE_CONSTRUCTOR(SoXipConvertSFDicomToMFDicom);

   // Define input field and its default value
   SO_ENGINE_ADD_INPUT(input, (0));

   // Define the output, specifying its type
   SO_ENGINE_ADD_OUTPUT(output, SoXipMFDataDicom);
}


SoXipConvertSFDicomToMFDicom::~SoXipConvertSFDicomToMFDicom()
{
}


// This is the evaluation routine.
void SoXipConvertSFDicomToMFDicom::evaluate()
{
	SoXipDataDicom * out = input.getValue();
	SO_ENGINE_OUTPUT(output, SoXipMFDataDicom, setValue(out));
}


// This returns the input field for the given type. Since we
// have only one input field, we don't have to check the type.
SoField *SoXipConvertSFDicomToMFDicom::getInput(SoType)
{
   return &input;
}


// This does the same for the output.
SoEngineOutput *SoXipConvertSFDicomToMFDicom::getOutput(SoType)
{
   return &output;
}
