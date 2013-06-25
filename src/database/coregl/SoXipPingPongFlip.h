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

#ifndef SO_XIP_PINGPONG_FLIP_H
#define SO_XIP_PINGPONG_FLIP_H


/**
 *  Component       : XIP
 *  Name            : SoXipPingPongFlip
 *  Author          : Lindholm S, SCR, Princeton
 *  Language        : C++
 *  Creation Date   : 2-Oct-2007
 *  Description     :   Use the print method to display info while
 *                      traversing scene graph.
 *
 *  Copyright © Siemens AG 2006-2007. All Rights Reserved.
 */


#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/inventor/coregl/xipivcoregl.h>
#include <xip/inventor/coregl/SoXipFramebufferElement.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>

class SoXipPingPongFlip : public SoGroup
{
    SO_NODE_HEADER(SoXipPingPongFlip);

public:

    SoXipPingPongFlip();
    ~SoXipPingPongFlip();

    static void initClass();

protected:
    virtual void    GLRender(SoGLRenderAction* action);
    void            flip(SoGLRenderAction* action);

private:

};

#endif // SO_XIP_CLEAR_BUFFERS_H
