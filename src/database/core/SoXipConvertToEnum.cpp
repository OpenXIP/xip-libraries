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
#include "SoXipConvertToEnum.h"

#ifdef TGS_VERSION
#if (SO_VERSION >= 7)

int SoXipConvertToEnum::getIsBuiltIn() const
{
	return 0;
}

#endif
#endif

void SoXipConvertToEnum::initClass()
{
	SO_ENGINE_INIT_CLASS(SoXipConvertToEnum, SoFieldConverter, "FieldConverter");

	SoDB::addConverter(SoSFShort::getClassTypeId(), SoSFEnum::getClassTypeId(), getClassTypeId());
	SoDB::addConverter(SoSFUShort::getClassTypeId(), SoSFEnum::getClassTypeId(), getClassTypeId());
	SoDB::addConverter(SoSFInt32::getClassTypeId(), SoSFEnum::getClassTypeId(), getClassTypeId());
	SoDB::addConverter(SoSFUInt32::getClassTypeId(), SoSFEnum::getClassTypeId(), getClassTypeId());
	SoDB::addConverter(SoSFFloat::getClassTypeId(), SoSFEnum::getClassTypeId(), getClassTypeId());

	SoDB::addConverter(SoMFShort::getClassTypeId(), SoSFEnum::getClassTypeId(), getClassTypeId());
	SoDB::addConverter(SoMFUShort::getClassTypeId(), SoSFEnum::getClassTypeId(), getClassTypeId());
	SoDB::addConverter(SoMFInt32::getClassTypeId(), SoSFEnum::getClassTypeId(), getClassTypeId());
	SoDB::addConverter(SoMFUInt32::getClassTypeId(), SoSFEnum::getClassTypeId(), getClassTypeId());
	SoDB::addConverter(SoMFFloat::getClassTypeId(), SoSFEnum::getClassTypeId(), getClassTypeId());
}


SoXipConvertToEnum::SoXipConvertToEnum()
{
	SO_ENGINE_CONSTRUCTOR(SoXipConvertToEnum);
	SO_ENGINE_ADD_OUTPUT(output, SoSFEnum);
	input = 0;

	mInputData = new SoFieldData(inputData);
}


SoXipConvertToEnum::~SoXipConvertToEnum()
{
	delete mInputData;

	if (input) 
	{
		delete input;
	}
}


void SoXipConvertToEnum::evaluate()
{
	int value = 0;
	if (input)
	{
		SbString str;
		input->get(str);

		// for multi-fields skip first two characters ("[ ")
		if (str.getSubString(0, 1) == SbString("[ "))
		{
			str.deleteSubString(0, 1);
		}

		value = atof(str.getString());
	}

	SO_ENGINE_OUTPUT(output, SoSFEnum, setValue(value));
}


SoField * SoXipConvertToEnum::getInput(SoType type)
{
	input = (SoField *) type.createInstance();
	mInputData->addField(this, "input", input);

	input->set("0");
	input->setContainer(this);

	return input;
}


SoEngineOutput * SoXipConvertToEnum::getOutput(SoType)
{
	return &output;
}


//
// Can't use regular SO_ENGINE_SOURCE macro because of the funky
// handling of getFieldData/getEngineOutputData:
//
SO__ENGINE_VARS(SoXipConvertToEnum);


SoType SoXipConvertToEnum::getTypeId() const
{
	return classTypeId;
}


const SoFieldData * SoXipConvertToEnum::getFieldData() const 
{
	return mInputData;
}


const SoEngineOutputData * SoXipConvertToEnum::getOutputData() const
{
	return outputData;
}

#ifndef TGS_VERSION

void * SoXipConvertToEnum::createInstance()
{
	return new SoXipConvertToEnum;
}

#else

void * SoXipConvertToEnum::createInstance(class SoType *)
{
	return new SoXipConvertToEnum;
}

SoType	SoXipConvertToEnum::getClassTypeId(void)
{
	return classTypeId;
}

#endif


