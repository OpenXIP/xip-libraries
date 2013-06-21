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
#include "SoXipClearFbo.h"
#include <xip/system/standard.h>
#include <xip/inventor/coregl/FramebufferObject.h>
#include <xip/inventor/coregl/SoXipFboElement.h>
#include <xip/inventor/coregl/SoXipDrawBuffersElement.h>

const GLenum SoXipClearFbo::avaliableColorTargets[16] = 
{
    GL_COLOR_ATTACHMENT0_EXT,  GL_COLOR_ATTACHMENT1_EXT,
    GL_COLOR_ATTACHMENT2_EXT,  GL_COLOR_ATTACHMENT3_EXT,
    GL_COLOR_ATTACHMENT4_EXT,  GL_COLOR_ATTACHMENT5_EXT,
    GL_COLOR_ATTACHMENT6_EXT,  GL_COLOR_ATTACHMENT7_EXT,
    GL_COLOR_ATTACHMENT8_EXT,  GL_COLOR_ATTACHMENT9_EXT,
    GL_COLOR_ATTACHMENT10_EXT, GL_COLOR_ATTACHMENT11_EXT,
    GL_COLOR_ATTACHMENT12_EXT, GL_COLOR_ATTACHMENT13_EXT,
    GL_COLOR_ATTACHMENT14_EXT, GL_COLOR_ATTACHMENT15_EXT
};

SO_NODE_SOURCE(SoXipClearFbo);

/**
 *  Constructor.
 */
SoXipClearFbo::SoXipClearFbo()
{
    SO_NODE_CONSTRUCTOR(SoXipClearFbo);

    // add fields
    SO_NODE_ADD_FIELD(clearColorTargets, (ALL));
    SO_NODE_ADD_FIELD(clearColor,(0.0, 0.0, 0.0, 0.0));
    SO_NODE_ADD_FIELD(clearDepthBuffer, (TRUE));
    SO_NODE_ADD_FIELD(depthValue, (1.0));
    SO_NODE_ADD_FIELD(clearOnlyCurrentViewport, (TRUE));

    // enums
    SO_NODE_DEFINE_ENUM_VALUE(ClearTargets, ALL);
    SO_NODE_DEFINE_ENUM_VALUE(ClearTargets, NONE);
    SO_NODE_DEFINE_ENUM_VALUE(ClearTargets, FIRST);
    SO_NODE_DEFINE_ENUM_VALUE(ClearTargets, FIRST_TWO);
    SO_NODE_DEFINE_ENUM_VALUE(ClearTargets, FIRST_THREE);
    SO_NODE_DEFINE_ENUM_VALUE(ClearTargets, FIRST_FOUR);
    SO_NODE_SET_SF_ENUM_TYPE(clearColorTargets, ClearTargets);
}

/**
 *  Destructor.
 */
SoXipClearFbo::~SoXipClearFbo()
{
}

/**
 *  Class initiation.
 */
void SoXipClearFbo::initClass()
{
    SO_NODE_INIT_CLASS(SoXipClearFbo, SoNode, "Node");

    SO_ENABLE(SoGLRenderAction, SoXipFboElement);
    SO_ENABLE(SoGLRenderAction, SoXipDrawBuffersElement);
}


/**
 *  Clears buffers according to user input.
 *  Reads current setup from draw buffers element.
 */
void SoXipClearFbo::clear(SoGLRenderAction* action)
{
    GLenum clearMask = 0;
    float savedDepth = 0;

    if (clearColorTargets.getValue())
    {
        clearMask |= GL_COLOR_BUFFER_BIT;
        // set the clear color
        SbVec4f color = clearColor.getValue();
        glClearColor(color[0], color[1], color[2], color[3]);
    }

    if (clearDepthBuffer.getValue())
    {
        clearMask |= GL_DEPTH_BUFFER_BIT;
        // set the clear depth value
        glGetFloatv(GL_DEPTH_CLEAR_VALUE, &savedDepth);
        glClearDepth(depthValue.getValue());
    }

    // check if something has to be cleared
    if (clearMask)
    {
        GLint   scissor[4];
        // use the scissor test to just clear the current viewport region
        if (clearOnlyCurrentViewport.getValue())
        {            
            glGetIntegerv(GL_SCISSOR_BOX, scissor);
            glPushAttrib(GL_SCISSOR_BIT);
            glEnable(GL_SCISSOR_TEST);
            SbViewportRegion viewport = action->getViewportRegion();
            glScissor(viewport.getViewportOriginPixels()[0],
                      viewport.getViewportOriginPixels()[1],
                      viewport.getViewportSizePixels()[0],
                      viewport.getViewportSizePixels()[1]);
        }
        // clear the buffer
        glPushAttrib(GL_COLOR_BUFFER_BIT);

#if 0
        FboSetup * foo = SoXipFboElement::getActive(action->getState(), this);
        int rt = SoXipDrawBuffersElement::getNum(action->getState(), this);
        SoDebugError::postInfo("SoXipClearFbo", "Clearing fbo (fbo %d, rt %d)", foo->fboHandle, rt);
#endif

#if 0
        int numB = SoXipDrawBuffersElement::getNum(action->getState(), this);
        GLenum buffers[16];
        SoXipDrawBuffersElement::getSubBuffers(action->getState(), this, numB, buffers);
        (numB == 1 && buffers[0] == GL_BACK) ? glDrawBuffer(GL_BACK) : glDrawBuffers(numB, buffers);
#endif

#if 1
        // Support to clear multiple buffers and a whole 3D buffer
        int fboNum = SoXipDrawBuffersElement::getNum(action->getState(), this);
        int newNum = clearColorTargets.getValue();
        newNum = (newNum > fboNum) ? fboNum : newNum;

        SoXipDrawBuffersElement::set(action->getState(), this, newNum);

        FboSetup * activeFbo = SoXipFboElement::getActive(action->getState(), this);

        if (activeFbo && activeFbo->colorStorage == GL_TEXTURE_3D)
            SoXipFboElement::reattachAs3D(action->getState(), this);

        glClear(clearMask);

        SoXipDrawBuffersElement::set(action->getState(), this, fboNum);
#else
        glClear(clearMask);
#endif

        glPopAttrib();  // GL_COLOR_BUFFER_BIT

        if (clearOnlyCurrentViewport.getValue())
        {
            glScissor(scissor[0], scissor[1], scissor[2], scissor[3]);
            glPopAttrib();      // GL_SCISSOR_BIT
        }
    }

    if (clearDepthBuffer.getValue())
    {
        glClearDepth(savedDepth);
    }
}

void SoXipClearFbo::GLRender(SoGLRenderAction* action)
{
    if (action->isRenderingDelayedPaths())
        return;

    clear(action);
}
