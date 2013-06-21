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
#include "SoXipClearBuffer.h"
#include <xip/system/standard.h>

SO_NODE_SOURCE(SoXipClearBuffer);

SoXipClearBuffer::SoXipClearBuffer()
{
    SO_NODE_CONSTRUCTOR(SoXipClearBuffer);

    // add fields
    SO_NODE_ADD_FIELD(clearColorBuffer, (true));
    SO_NODE_ADD_FIELD(clearOnlyCurrentViewport, (true));
    SO_NODE_ADD_FIELD(clearColor,(0.0f, 0.0f, 0.0f, 0.0f));
    SO_NODE_ADD_FIELD(clearDepthBuffer, (false));
    SO_NODE_ADD_FIELD(depthValue, (1.0f));
}


SoXipClearBuffer::~SoXipClearBuffer()
{
}


void SoXipClearBuffer::initClass()
{
    SO_NODE_INIT_CLASS(SoXipClearBuffer, SoNode, "Node");
}


void SoXipClearBuffer::GLRender(SoGLRenderAction* action)
{
	if (action->isRenderingDelayedPaths())
		return;

	GLenum clearMask = 0;
	float savedDepth = 0.0f;

    if (clearColorBuffer.getValue())
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
            glScissor(viewport.getViewportOriginPixels()[0], viewport.getViewportOriginPixels()[1],
                    viewport.getViewportSizePixels()[0], viewport.getViewportSizePixels()[1]);
        }
		// clear the buffer
        glClear(clearMask);
        
        if (clearOnlyCurrentViewport.getValue())
        {
            glScissor(scissor[0], scissor[1], scissor[2], scissor[3]);
            glPopAttrib();
        }
    }
    // reset depthClear value
    if (clearDepthBuffer.getValue())
    {
		glClearDepth(savedDepth);
	}
}

