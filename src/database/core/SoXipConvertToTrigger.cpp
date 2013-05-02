

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
