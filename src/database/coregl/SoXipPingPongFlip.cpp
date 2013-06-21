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
#include "SoXipPingPongFlip.h"
#include <xip/inventor/coregl/FramebufferObject.h>
#include <xip/inventor/coregl/SoXipFboElement.h>
#include <xip/inventor/coregl/SoXipDrawBuffersElement.h>

SO_NODE_SOURCE(SoXipPingPongFlip);

/**
 *  Constructor.
 */
SoXipPingPongFlip::SoXipPingPongFlip()
{
    SO_NODE_CONSTRUCTOR(SoXipPingPongFlip);
}

/**
 *  Destructor.
 */
SoXipPingPongFlip::~SoXipPingPongFlip()
{
}

/**
 *  Class initiation.
 */
void SoXipPingPongFlip::initClass()
{
    SO_NODE_INIT_CLASS(SoXipPingPongFlip, SoGroup, "SoGroup");

	SO_ENABLE(SoGLRenderAction, SoXipFboElement);
	SO_ENABLE(SoGLRenderAction, SoXipDrawBuffersElement);
}


/**
 *  Clears buffers according to user input.
 *  Reads current setup from draw buffers element.
 */
void SoXipPingPongFlip::flip(SoGLRenderAction* action)
{
    SoXipFboElement::flip(action->getState(), this);
    FboSetup * fbo = SoXipFboElement::getActive(action->getState(), this);
    if (fbo->isComplete)
        SoXipDrawBuffersElement::set(action->getState(), this, fbo->numColorAttachments);
    else
        SoXipDrawBuffersElement::set(action->getState(), this, 0);
}

void SoXipPingPongFlip::GLRender(SoGLRenderAction* action)
{
    if (SoXipFboElement::isPingPong(action->getState(), this))
        flip(action);

    // Render children
	SoGroup::GLRender(action);
}


