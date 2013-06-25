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

#ifndef SOXIPCONVERTTOENUM_H
#define SOXIPCONVERTTOENUM_H

#include <Inventor/fields/SoFields.h>
#include <Inventor/engines/SoFieldConverter.h>


class SoXipConvertToEnum : public SoFieldConverter 
{
	SO_ENGINE_HEADER(SoXipConvertToEnum);

public:
	SoField *input;
	SoEngineOutput output;

	static void  initClass();
	virtual void evaluate();

protected:
	SoXipConvertToEnum();
	virtual ~SoXipConvertToEnum();

	virtual SoField *getInput(SoType);
	virtual SoEngineOutput *getOutput(SoType);

	// cannot use inputData member of inherited class in field containers
	// due to funky handling of getFieldData/getEngineOutputData
	// (would cause access violation when deserializing scene objects)
	SoFieldData *mInputData;
};


#endif // SOXIPCONVERTTOENUM_H
