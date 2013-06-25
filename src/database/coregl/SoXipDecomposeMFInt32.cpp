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

#include <xip/system/standard.h>
#include "SoXipDecomposeMFInt32.h"

SO_ENGINE_SOURCE(SoXipDecomposeMFInt32);

/**
 *  Constructor.
 */
SoXipDecomposeMFInt32::SoXipDecomposeMFInt32()
{
    SO_ENGINE_CONSTRUCTOR(SoXipDecomposeMFInt32);

    // add fields
    SO_ENGINE_ADD_INPUT(intMF, (0));
	SO_ENGINE_ADD_OUTPUT(int0, SoSFInt32);
	SO_ENGINE_ADD_OUTPUT(int1, SoSFInt32);
	SO_ENGINE_ADD_OUTPUT(int2, SoSFInt32);
	SO_ENGINE_ADD_OUTPUT(int3, SoSFInt32);
	SO_ENGINE_ADD_OUTPUT(int4, SoSFInt32);
	SO_ENGINE_ADD_OUTPUT(int5, SoSFInt32);
	SO_ENGINE_ADD_OUTPUT(int6, SoSFInt32);
	SO_ENGINE_ADD_OUTPUT(int7, SoSFInt32);
}

/**
 *  Destructor.
 */
SoXipDecomposeMFInt32::~SoXipDecomposeMFInt32()
{
}

/**
 *  Class initiation.
 */
void SoXipDecomposeMFInt32::initClass()
{
    SO_ENGINE_INIT_CLASS(SoXipDecomposeMFInt32, SoEngine, "Engine");
}


/**
 *  Split the multifields to single fields.
 */
void SoXipDecomposeMFInt32::evaluate()
{
    sizeMF = intMF.getNum();
    sizeMF = (sizeMF < 0) ? 0 : sizeMF;

    switch (sizeMF) {
        case 0:
            SO_ENGINE_OUTPUT(int0, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int1, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int2, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int3, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int4, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int5, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int6, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int7, SoSFInt32, setValue(0));
            break;
        case 1:
            SO_ENGINE_OUTPUT(int0, SoSFInt32, setValue(intMF[0]));
            SO_ENGINE_OUTPUT(int1, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int2, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int3, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int4, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int5, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int6, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int7, SoSFInt32, setValue(0));
            break;
        case 2:
            SO_ENGINE_OUTPUT(int0, SoSFInt32, setValue(intMF[0]));
            SO_ENGINE_OUTPUT(int1, SoSFInt32, setValue(intMF[1]));
            SO_ENGINE_OUTPUT(int2, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int3, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int4, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int5, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int6, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int7, SoSFInt32, setValue(0));
            break;
        case 3:
            SO_ENGINE_OUTPUT(int0, SoSFInt32, setValue(intMF[0]));
            SO_ENGINE_OUTPUT(int1, SoSFInt32, setValue(intMF[1]));
            SO_ENGINE_OUTPUT(int2, SoSFInt32, setValue(intMF[2]));
            SO_ENGINE_OUTPUT(int3, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int4, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int5, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int6, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int7, SoSFInt32, setValue(0));
            break;
        case 4:
            SO_ENGINE_OUTPUT(int0, SoSFInt32, setValue(intMF[0]));
            SO_ENGINE_OUTPUT(int1, SoSFInt32, setValue(intMF[1]));
            SO_ENGINE_OUTPUT(int2, SoSFInt32, setValue(intMF[2]));
            SO_ENGINE_OUTPUT(int3, SoSFInt32, setValue(intMF[3]));
            SO_ENGINE_OUTPUT(int4, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int5, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int6, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int7, SoSFInt32, setValue(0));
            break;
        case 5:
            SO_ENGINE_OUTPUT(int0, SoSFInt32, setValue(intMF[0]));
            SO_ENGINE_OUTPUT(int1, SoSFInt32, setValue(intMF[1]));
            SO_ENGINE_OUTPUT(int2, SoSFInt32, setValue(intMF[2]));
            SO_ENGINE_OUTPUT(int3, SoSFInt32, setValue(intMF[3]));
            SO_ENGINE_OUTPUT(int4, SoSFInt32, setValue(intMF[4]));
            SO_ENGINE_OUTPUT(int5, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int6, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int7, SoSFInt32, setValue(0));
            break;
        case 6:
            SO_ENGINE_OUTPUT(int0, SoSFInt32, setValue(intMF[0]));
            SO_ENGINE_OUTPUT(int1, SoSFInt32, setValue(intMF[1]));
            SO_ENGINE_OUTPUT(int2, SoSFInt32, setValue(intMF[2]));
            SO_ENGINE_OUTPUT(int3, SoSFInt32, setValue(intMF[3]));
            SO_ENGINE_OUTPUT(int4, SoSFInt32, setValue(intMF[4]));
            SO_ENGINE_OUTPUT(int5, SoSFInt32, setValue(intMF[5]));
            SO_ENGINE_OUTPUT(int6, SoSFInt32, setValue(0));
            SO_ENGINE_OUTPUT(int7, SoSFInt32, setValue(0));
            break;
        case 7:
            SO_ENGINE_OUTPUT(int0, SoSFInt32, setValue(intMF[0]));
            SO_ENGINE_OUTPUT(int1, SoSFInt32, setValue(intMF[1]));
            SO_ENGINE_OUTPUT(int2, SoSFInt32, setValue(intMF[2]));
            SO_ENGINE_OUTPUT(int3, SoSFInt32, setValue(intMF[3]));
            SO_ENGINE_OUTPUT(int4, SoSFInt32, setValue(intMF[4]));
            SO_ENGINE_OUTPUT(int5, SoSFInt32, setValue(intMF[5]));
            SO_ENGINE_OUTPUT(int6, SoSFInt32, setValue(intMF[6]));
            SO_ENGINE_OUTPUT(int7, SoSFInt32, setValue(0));
            break;
        default:
            SO_ENGINE_OUTPUT(int0, SoSFInt32, setValue(intMF[0]));
            SO_ENGINE_OUTPUT(int1, SoSFInt32, setValue(intMF[1]));
            SO_ENGINE_OUTPUT(int2, SoSFInt32, setValue(intMF[2]));
            SO_ENGINE_OUTPUT(int3, SoSFInt32, setValue(intMF[3]));
            SO_ENGINE_OUTPUT(int4, SoSFInt32, setValue(intMF[4]));
            SO_ENGINE_OUTPUT(int5, SoSFInt32, setValue(intMF[5]));
            SO_ENGINE_OUTPUT(int6, SoSFInt32, setValue(intMF[6]));
            SO_ENGINE_OUTPUT(int7, SoSFInt32, setValue(intMF[7]));
    }
}


