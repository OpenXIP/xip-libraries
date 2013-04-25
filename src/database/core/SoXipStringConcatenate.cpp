/*
  ------------------------------------------------------------------------

    SoXipStringConcatenate.cc

    Setting up clip planes for use in shader programs

    Copyright (C) 2007 - 2008, Siemens Corporate Research, Inc.

    Authors:
      Patric Ljung, patric.ljung@siemens.com

    This file is part of XIP Pro, Siemens proprietary software.

  ------------------------------------------------------------------------
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
