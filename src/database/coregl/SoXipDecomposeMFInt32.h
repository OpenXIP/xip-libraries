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

#ifndef SO_XIP_DECOMPOSE_MFINT32_H
#define SO_XIP_DECOMPOSE_MFINT32_H


/**
 *  Component       : XIP
 *  Name            : SoXipDecomposeMFInt32
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
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFInt32.h>


class SoXipDecomposeMFInt32 : public SoEngine
{
    SO_ENGINE_HEADER(SoXipDecomposeMFInt32);

public:

    SoXipDecomposeMFInt32();
    static void initClass();

    // field variables
    SoMFInt32       intMF;
    SoEngineOutput  int0;
    SoEngineOutput  int1;
    SoEngineOutput  int2;
    SoEngineOutput  int3;
    SoEngineOutput  int4;
    SoEngineOutput  int5;
    SoEngineOutput  int6;
    SoEngineOutput  int7;

private:

    ~SoXipDecomposeMFInt32();
    virtual void    evaluate();
    int             sizeMF;
};

#endif // SO_XIP_SPLIT_MFINT32_H
