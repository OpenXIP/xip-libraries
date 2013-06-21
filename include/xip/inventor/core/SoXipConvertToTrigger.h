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
