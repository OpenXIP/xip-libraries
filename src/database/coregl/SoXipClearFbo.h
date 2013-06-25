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
#ifndef SO_XIP_CLEAR_FBO_H
#define SO_XIP_CLEAR_FBO_H

/**
 *  Component       : XIP
 *  Name            : SoXipFbo
 *  Author          : Lindholm S, SCR, Princeton
 *  Language        : C++
 *  Creation Date   : 2-Oct-2007
 *  Description     :   This group is an extention from SoXipClearBuffer
 *                      and allowes for clearing multiple rendering targets.
 *                      It is also updated to use the new version of element
 *                      driven FBO handling.
 *
 *  Copyright © Siemens AG 2006-2007. All Rights Reserved.
 */

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFBool.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/inventor/coregl/xipivcoregl.h>
#include <xip/inventor/coregl/SoXipFramebufferElement.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>

class SoXipClearFbo : public SoNode
{
    SO_NODE_HEADER(SoXipClearFbo);

public:
	enum ClearTargets {
		ALL         = 16,
        NONE        = 0,
        FIRST       = 1,
        FIRST_TWO   = 2,
        FIRST_THREE = 3,
        FIRST_FOUR  = 4
	};

    SoXipClearFbo();
    ~SoXipClearFbo();

    static void initClass();

    // field variables
    SoSFEnum        clearColorTargets;
    SoSFVec4f       clearColor;
    SoSFBool        clearDepthBuffer;
    SoSFFloat       depthValue;
    SoSFBool        clearOnlyCurrentViewport;

protected:
    virtual void    GLRender(SoGLRenderAction* action);
    void            clear(SoGLRenderAction* action);

private:
    static const    GLenum avaliableColorTargets[16];
};

#endif // SO_XIP_CLEAR_BUFFERS_H



