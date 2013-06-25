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
#ifndef SO_XIP_CLEAR_BUFFER_H
#define SO_XIP_CLEAR_BUFFER_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/inventor/coregl/xipivcoregl.h>
#include <xip/system/GL/gl.h>

/**
 * This node clears the color and depth buffer of the viewport,
 * depending on the set flags.
 */
class XIPIVCOREGL_API SoXipClearBuffer : public SoNode
{
    SO_NODE_HEADER(SoXipClearBuffer);

public:
	/**
	 * Construct initializes fields with default values.
	 */
    SoXipClearBuffer();
    ~SoXipClearBuffer();

    static void initClass();

    /// flag to clear the color buffer.
    SoSFBool clearColorBuffer;
    /// flag to clear only current viewport (using scissor test)
    SoSFBool clearOnlyCurrentViewport;
	/// RGBA color used to clear the color buffer.
    SoSFVec4f clearColor;
	/// flag to clear the depth buffer.
    SoSFBool clearDepthBuffer;
	/// depth value used to clear the depth buffer.
    SoSFFloat depthValue;

protected:
	/**
	 * clears the color and depth buffer of the viewport.
	 */
    virtual void GLRender(SoGLRenderAction* action);
};

#endif // SO_XIP_CLEAR_BUFFER_H
