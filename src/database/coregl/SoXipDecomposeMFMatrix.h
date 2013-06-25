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

#ifndef SO_XIP_DECOMPOSE_MFMATRIX_H
#define SO_XIP_DECOMPOSE_MFMATRIX_H


/**
 *  Component       : XIP
 *  Name            : SoXipDecomposeMFMatrix
 *  Author          : Lindholm S, SCR, Princeton
 *  Language        : C++
 *  Creation Date   : 2-Oct-2007
 *  Description     :   Split multifield Int32 into its components
 *                      as single field Int32's. Should be more
 *                      safe than the regular inventor node
 *                      SoSelectOne when dealing with multifields
 *                      of variable length.
 *
 *  Copyright © Siemens AG 2006-2007. All Rights Reserved.
 */


#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoMFMatrix.h>


class SoXipDecomposeMFMatrix : public SoEngine
{
    SO_ENGINE_HEADER(SoXipDecomposeMFMatrix);

public:

    SoXipDecomposeMFMatrix();
    static void initClass();

    // field variables
    SoMFMatrix      matMF;
    SoEngineOutput  mat0;
    SoEngineOutput  mat1;
    SoEngineOutput  mat2;
    SoEngineOutput  mat3;
    SoEngineOutput  mat4;
    SoEngineOutput  mat5;
    SoEngineOutput  mat6;
    SoEngineOutput  mat7;

private:

    ~SoXipDecomposeMFMatrix();
    virtual void    evaluate();
    int             sizeMF;
};

#endif // SO_XIP_DECOMPOSE_MFMATRIX_H



