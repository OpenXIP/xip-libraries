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
  Scope:

  This component is intended to extract the current VR Clip Planes and
  pass them on to a shader program and/or output them to a buffer to
  be stored into a texture.

  Component should be part of XIP
*/

/*
  Implementation Notes:

*/

#include "SoXipStringConcatenate.h"


SO_ENGINE_SOURCE(SoXipStringConcatenate);


SoXipStringConcatenate::SoXipStringConcatenate() :
    input0(input[0]), input1(input[1]), input2(input[2]), input3(input[3]),
    input4(input[4]), input5(input[5]), input6(input[6]), input7(input[7]),
    input8(input[8]), input9(input[9])
{
    SO_ENGINE_CONSTRUCTOR(SoXipStringConcatenate);

    SO_ENGINE_ADD_INPUT(separator, (SbString(", ")));

    SO_ENGINE_ADD_INPUT(input0, (""));
    SO_ENGINE_ADD_INPUT(input1, (""));
    SO_ENGINE_ADD_INPUT(input2, (""));
    SO_ENGINE_ADD_INPUT(input3, (""));
    SO_ENGINE_ADD_INPUT(input4, (""));
    SO_ENGINE_ADD_INPUT(input5, (""));
    SO_ENGINE_ADD_INPUT(input6, (""));
    SO_ENGINE_ADD_INPUT(input7, (""));
    SO_ENGINE_ADD_INPUT(input8, (""));
    SO_ENGINE_ADD_INPUT(input9, (""));

    for (int i = 0; i < cmNumberOfInputs; i++)
    {
        input[i].setNum(0);
    }

    SO_ENGINE_ADD_OUTPUT(output, SoSFString);
}

SoXipStringConcatenate::~SoXipStringConcatenate()
{
}


void SoXipStringConcatenate::initClass()
{
    SO_ENGINE_INIT_CLASS(SoXipStringConcatenate, SoEngine, "SoEngine");
}


/*
  ------------------------------------------------------------------------
    virtual evaluate()

    Evaluate all input fields and generate output
  ------------------------------------------------------------------------
*/

void SoXipStringConcatenate::evaluate()
{
    SbString out;
    bool empty = true;
    const SbString & sep(separator.getValue());

    for (int i = 0; i < cmNumberOfInputs; i++)
    {
        int count = input[i].getNum();

        for (int j = 0; j < count; j++)
        {
            if (!empty) out += sep;

            out += input[i][j];
            empty = false;
        }
    }

    SO_ENGINE_OUTPUT(output, SoSFString, setValue(out));
}

// local Variables:
//   mode: c++
//   indent-tabs-mode: nil
//   c-indentation-style: k&r
//   c-basic-offset: 4
// End:
