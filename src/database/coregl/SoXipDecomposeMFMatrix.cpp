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
#include "SoXipDecomposeMFMatrix.h"

SO_ENGINE_SOURCE(SoXipDecomposeMFMatrix);

/**
 *  Constructor.
 */
SoXipDecomposeMFMatrix::SoXipDecomposeMFMatrix()
{
    SO_ENGINE_CONSTRUCTOR(SoXipDecomposeMFMatrix);

    // add fields
    SO_ENGINE_ADD_INPUT(matMF, (SbMatrix::identity()));
	SO_ENGINE_ADD_OUTPUT(mat0, SoSFMatrix);
	SO_ENGINE_ADD_OUTPUT(mat1, SoSFMatrix);
	SO_ENGINE_ADD_OUTPUT(mat2, SoSFMatrix);
	SO_ENGINE_ADD_OUTPUT(mat3, SoSFMatrix);
	SO_ENGINE_ADD_OUTPUT(mat4, SoSFMatrix);
	SO_ENGINE_ADD_OUTPUT(mat5, SoSFMatrix);
	SO_ENGINE_ADD_OUTPUT(mat6, SoSFMatrix);
	SO_ENGINE_ADD_OUTPUT(mat7, SoSFMatrix);
}

/**
 *  Destructor.
 */
SoXipDecomposeMFMatrix::~SoXipDecomposeMFMatrix()
{
}

/**
 *  Class initiation.
 */
void SoXipDecomposeMFMatrix::initClass()
{
    SO_ENGINE_INIT_CLASS(SoXipDecomposeMFMatrix, SoEngine, "Engine");
}


/**
 *  Split the multifields to single fields.
 */
void SoXipDecomposeMFMatrix::evaluate()
{
    sizeMF = matMF.getNum();
    sizeMF = (sizeMF < 0) ? 0 : sizeMF;

    switch (sizeMF) {
        case 0:
            SO_ENGINE_OUTPUT(mat0, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat1, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat2, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat3, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat4, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat5, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat6, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat7, SoSFMatrix, setValue(SbMatrix::identity()));
            break;
        case 1:
            SO_ENGINE_OUTPUT(mat0, SoSFMatrix, setValue(matMF[0]));
            SO_ENGINE_OUTPUT(mat1, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat2, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat3, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat4, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat5, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat6, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat7, SoSFMatrix, setValue(SbMatrix::identity()));
            break;
        case 2:
            SO_ENGINE_OUTPUT(mat0, SoSFMatrix, setValue(matMF[0]));
            SO_ENGINE_OUTPUT(mat1, SoSFMatrix, setValue(matMF[1]));
            SO_ENGINE_OUTPUT(mat2, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat3, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat4, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat5, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat6, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat7, SoSFMatrix, setValue(SbMatrix::identity()));
            break;
        case 3:
            SO_ENGINE_OUTPUT(mat0, SoSFMatrix, setValue(matMF[0]));
            SO_ENGINE_OUTPUT(mat1, SoSFMatrix, setValue(matMF[1]));
            SO_ENGINE_OUTPUT(mat2, SoSFMatrix, setValue(matMF[2]));
            SO_ENGINE_OUTPUT(mat3, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat4, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat5, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat6, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat7, SoSFMatrix, setValue(SbMatrix::identity()));
            break;
        case 4:
            SO_ENGINE_OUTPUT(mat0, SoSFMatrix, setValue(matMF[0]));
            SO_ENGINE_OUTPUT(mat1, SoSFMatrix, setValue(matMF[1]));
            SO_ENGINE_OUTPUT(mat2, SoSFMatrix, setValue(matMF[2]));
            SO_ENGINE_OUTPUT(mat3, SoSFMatrix, setValue(matMF[3]));
            SO_ENGINE_OUTPUT(mat4, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat5, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat6, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat7, SoSFMatrix, setValue(SbMatrix::identity()));
            break;
        case 5:
            SO_ENGINE_OUTPUT(mat0, SoSFMatrix, setValue(matMF[0]));
            SO_ENGINE_OUTPUT(mat1, SoSFMatrix, setValue(matMF[1]));
            SO_ENGINE_OUTPUT(mat2, SoSFMatrix, setValue(matMF[2]));
            SO_ENGINE_OUTPUT(mat3, SoSFMatrix, setValue(matMF[3]));
            SO_ENGINE_OUTPUT(mat4, SoSFMatrix, setValue(matMF[4]));
            SO_ENGINE_OUTPUT(mat5, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat6, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat7, SoSFMatrix, setValue(SbMatrix::identity()));
            break;
        case 6:
            SO_ENGINE_OUTPUT(mat0, SoSFMatrix, setValue(matMF[0]));
            SO_ENGINE_OUTPUT(mat1, SoSFMatrix, setValue(matMF[1]));
            SO_ENGINE_OUTPUT(mat2, SoSFMatrix, setValue(matMF[2]));
            SO_ENGINE_OUTPUT(mat3, SoSFMatrix, setValue(matMF[3]));
            SO_ENGINE_OUTPUT(mat4, SoSFMatrix, setValue(matMF[4]));
            SO_ENGINE_OUTPUT(mat5, SoSFMatrix, setValue(matMF[5]));
            SO_ENGINE_OUTPUT(mat6, SoSFMatrix, setValue(SbMatrix::identity()));
            SO_ENGINE_OUTPUT(mat7, SoSFMatrix, setValue(SbMatrix::identity()));
            break;
        case 7:
            SO_ENGINE_OUTPUT(mat0, SoSFMatrix, setValue(matMF[0]));
            SO_ENGINE_OUTPUT(mat1, SoSFMatrix, setValue(matMF[1]));
            SO_ENGINE_OUTPUT(mat2, SoSFMatrix, setValue(matMF[2]));
            SO_ENGINE_OUTPUT(mat3, SoSFMatrix, setValue(matMF[3]));
            SO_ENGINE_OUTPUT(mat4, SoSFMatrix, setValue(matMF[4]));
            SO_ENGINE_OUTPUT(mat5, SoSFMatrix, setValue(matMF[5]));
            SO_ENGINE_OUTPUT(mat6, SoSFMatrix, setValue(matMF[6]));
            SO_ENGINE_OUTPUT(mat7, SoSFMatrix, setValue(SbMatrix::identity()));
            break;
        default:
            SO_ENGINE_OUTPUT(mat0, SoSFMatrix, setValue(matMF[0]));
            SO_ENGINE_OUTPUT(mat1, SoSFMatrix, setValue(matMF[1]));
            SO_ENGINE_OUTPUT(mat2, SoSFMatrix, setValue(matMF[2]));
            SO_ENGINE_OUTPUT(mat3, SoSFMatrix, setValue(matMF[3]));
            SO_ENGINE_OUTPUT(mat4, SoSFMatrix, setValue(matMF[4]));
            SO_ENGINE_OUTPUT(mat5, SoSFMatrix, setValue(matMF[5]));
            SO_ENGINE_OUTPUT(mat6, SoSFMatrix, setValue(matMF[6]));
            SO_ENGINE_OUTPUT(mat7, SoSFMatrix, setValue(matMF[7]));
    }
}


