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
/*
  ------------------------------------------------------------------------

    SoXipStringConcatenate.h

    Concatenate multifield string inputs to a single separated string.

    Copyright (C) 2007 - 2008, Siemens Corporate Research, Inc.

    Authors:
      Patric Ljung, patric.ljung@siemens.com

    This file is part of Open XIP, see license at end of file for details.

  ------------------------------------------------------------------------
*/

/*
  Scope:

*/

/*
  Definition Notes:

*/

#ifndef SO_XIP_STRING_CONCATENATE_H
#define SO_XIP_STRING_CONCATENATE_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFString.h>

/*
  Forward class declarations
*/

/*
  ------------------------------------------------------------------------
    Class definition: SoXipStringConcatenate


  ------------------------------------------------------------------------
*/

class SoXipStringConcatenate : public SoEngine {

    SO_ENGINE_HEADER(SoXipStringConcatenate);

public:

    static const int cmNumberOfInputs = 10;

    SoXipStringConcatenate();
    virtual ~SoXipStringConcatenate();

    static void initClass();

    SoSFString		separator;
    SoMFString		input[cmNumberOfInputs];
    SoEngineOutput      output;

    // References to the input array
    SoMFString &	input0;
    SoMFString &	input1;
    SoMFString &	input2;
    SoMFString &	input3;
    SoMFString &	input4;
    SoMFString &	input5;
    SoMFString &	input6;
    SoMFString &	input7;
    SoMFString &	input8;
    SoMFString &	input9;

protected:
    // Make copy constructor and assignement operator protected
    // to prevent accidental out of class use.
    SoXipStringConcatenate(const SoXipStringConcatenate & source) :
        input0(input[0]), input1(input[1]), input2(input[2]), input3(input[3]),
        input4(input[4]), input5(input[5]), input6(input[6]), input7(input[7]),
        input8(input[8]), input9(input[9])
    {
	// Not really allowed so far
    }

    SoXipStringConcatenate & operator = (const SoXipStringConcatenate & source)
    {
	// Not really allowed so far
	return *this;
    }

    virtual void	evaluate();
};

// local Variables:
//   mode: c++
//   indent-tabs-mode: nil
//   c-indentation-style: k&r
//   c-basic-offset: 4
// End:

#endif // SO_XIP_STRING_CONCATENATE_H
