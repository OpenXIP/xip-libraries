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


#include <xip/inventor/core/SoXipConvertToTrigger.h>

//
// Can't use regular SO_ENGINE_SOURCE macro because of the funky
// handling of getFieldData/getEngineOutputData:
// 
SO__ENGINE_VARS(SoXipConvertToTrigger);



SoXipConvertToTrigger::SoXipConvertToTrigger()

{
    SO_ENGINE_CONSTRUCTOR(SoXipConvertToTrigger);
    SO_ENGINE_ADD_OUTPUT(convertTo, SoSFTrigger);
    data = new SoFieldData(inputData);
    convertFrom = NULL;
}


SoXipConvertToTrigger::~SoXipConvertToTrigger()

{
    delete data;
    if (convertFrom != NULL) {
	delete convertFrom;
    }
}


SoField *
SoXipConvertToTrigger::getInput(SoType type)
{
    convertFrom = (SoField *) type.createInstance();
    convertFrom->setContainer(this);
   data->addField(this, "convertFrom", convertFrom);

    return convertFrom;
}



SoEngineOutput *
SoXipConvertToTrigger::getOutput(SoType)
{
    return &convertTo;
}


void
SoXipConvertToTrigger::changed(SoField *whichField)
{
    whichField->evaluate();
}



void
SoXipConvertToTrigger::evaluate()
{
    convertFrom->evaluate();
}


SoType SoXipConvertToTrigger::getTypeId() const
{
    return classTypeId;
}


const SoFieldData * SoXipConvertToTrigger::getFieldData() const 
{
    return data;
}

const SoEngineOutputData * SoXipConvertToTrigger::getOutputData() const
{
    return outputData;
}


void * SoXipConvertToTrigger::createInstance()
{
    return new SoXipConvertToTrigger;
}

void SoXipConvertToTrigger::initClass()
{
    SO__ENGINE_INIT_CLASS(SoXipConvertToTrigger,"SoXipConvertToTrigger",SoFieldConverter);
}
