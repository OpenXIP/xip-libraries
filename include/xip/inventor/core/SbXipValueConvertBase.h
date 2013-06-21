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
*/#ifndef SBXIPVALUECONVERTBASE_H
#define SBXIPVALUECONVERTBASE_H

#include <xip/inventor/core/xipivcore.h>

/*! \class SbXipValueConvertBase 
 *  \brief A base pure virtual interface for value converter classes.
 *
 *  This class serves as the base interface for converting a given
 *  input value to an output value.  Derive classes are to implement 
 *  the given interfaces.
 */
class XIPIVCORE_API SbXipValueConvertBase
{
public:
	/// Constructor
    SbXipValueConvertBase() {};
    virtual ~SbXipValueConvertBase() {};

    virtual SbXipValueConvertBase* clone() const = 0;

	virtual float getConvertedValue(float val_in) const = 0;
	virtual float getConvertedScale(float scale_in) const = 0;

};




#endif // SBXIPVALUECONVERTERBASE_H
