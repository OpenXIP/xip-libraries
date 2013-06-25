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
#ifndef SO_XIP_BLEND_FUNC_H
#define SO_XIP_BLEND_FUNC_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/inventor/coregl/xipivcoregl.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>

//XIPIVCOREGL_API
class SoXipBlendFunc : public SoNode
{
	SO_NODE_HEADER(SoXipBlendFunc);
public:
	SoXipBlendFunc();

	static void initClass();

private:
	~SoXipBlendFunc();

	enum BlendFactor
    {
        ZERO                        = GL_ZERO,
        ONE                         = GL_ONE,
        SRC_COLOR                   = GL_SRC_COLOR,
        DST_COLOR                   = GL_DST_COLOR,
        SRC_ALPHA                   = GL_SRC_ALPHA,
        DST_ALPHA                   = GL_DST_ALPHA,
        ONE_MINUS_SRC_COLOR         = GL_ONE_MINUS_SRC_COLOR,
        ONE_MINUS_DST_COLOR         = GL_ONE_MINUS_DST_COLOR,
        ONE_MINUS_SRC_ALPHA         = GL_ONE_MINUS_SRC_ALPHA,
        ONE_MINUS_DST_ALPHA         = GL_ONE_MINUS_DST_ALPHA,
        CONSTANT_COLOR              = GL_CONSTANT_COLOR,
        CONSTANT_ALPHA              = GL_CONSTANT_ALPHA,
        ONE_MINUS_CONSTANT_COLOR    = GL_ONE_MINUS_CONSTANT_COLOR,
        ONE_MINUS_CONSTANT_ALPHA    = GL_ONE_MINUS_CONSTANT_ALPHA,
        SRC_ALPHA_SATURATE          = GL_SRC_ALPHA_SATURATE
	};

	SoSFBool enableBlending;
	SoSFEnum srcFunc;
	SoSFEnum dstFunc;

protected:
	virtual void GLRender(SoGLRenderAction *action);
};

#endif
