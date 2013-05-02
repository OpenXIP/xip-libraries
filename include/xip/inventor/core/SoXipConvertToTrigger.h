



#ifndef SOXIPCONVERTTOTRIGGER_H
#define SOXIPCONVERTTOTRIGGER_H

#include <Inventor/fields/SoFields.h>
#include <Inventor/engines/SoFieldConverter.h>

////////////////////////////////////////////////////////////
//
// Converter from various XIP classes to trigger
//
////////////////////////////////////////////////////////////

// Since typeId  is only internal, we need this to add converters for our own types 
class SoXipConvertToTrigger : public SoFieldConverter {

    SO_ENGINE_HEADER(SoXipConvertToTrigger);

  public:
    SoField				*convertFrom;
    SoEngineOutput		convertTo; /* SoSFTrigger */

 public:
    static void			initClass();

    virtual void		evaluate();
    virtual void		changed(SoField *whichField);

  private:
    SoXipConvertToTrigger();
    ~SoXipConvertToTrigger();

    virtual SoField		*getInput(SoType);
    virtual SoEngineOutput	*getOutput(SoType);

 

    SoFieldData *data;
};

#endif // SOXIPCONVERTTOTRIGGER_H