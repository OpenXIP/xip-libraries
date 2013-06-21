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
#include "SoXipBlendFunc.h"
#include <xip/inventor/coregl/SoXipBlendFuncElement.h>

SO_NODE_SOURCE(SoXipBlendFunc);

SoXipBlendFunc::SoXipBlendFunc()
{
	SO_NODE_CONSTRUCTOR(SoXipBlendFunc);

	SO_NODE_ADD_FIELD(enableBlending, (true));

	SO_NODE_DEFINE_ENUM_VALUE(BlendFactor, ZERO);
	SO_NODE_DEFINE_ENUM_VALUE(BlendFactor, ONE);
	SO_NODE_DEFINE_ENUM_VALUE(BlendFactor, SRC_COLOR);
	SO_NODE_DEFINE_ENUM_VALUE(BlendFactor, DST_COLOR);
	SO_NODE_DEFINE_ENUM_VALUE(BlendFactor, SRC_ALPHA);
	SO_NODE_DEFINE_ENUM_VALUE(BlendFactor, DST_ALPHA);
	SO_NODE_DEFINE_ENUM_VALUE(BlendFactor, ONE_MINUS_SRC_COLOR);
	SO_NODE_DEFINE_ENUM_VALUE(BlendFactor, ONE_MINUS_DST_COLOR);
	SO_NODE_DEFINE_ENUM_VALUE(BlendFactor, ONE_MINUS_SRC_ALPHA);
	SO_NODE_DEFINE_ENUM_VALUE(BlendFactor, ONE_MINUS_DST_ALPHA);
	SO_NODE_DEFINE_ENUM_VALUE(BlendFactor, CONSTANT_COLOR);
	SO_NODE_DEFINE_ENUM_VALUE(BlendFactor, CONSTANT_ALPHA);
	SO_NODE_DEFINE_ENUM_VALUE(BlendFactor, ONE_MINUS_CONSTANT_COLOR);
	SO_NODE_DEFINE_ENUM_VALUE(BlendFactor, ONE_MINUS_CONSTANT_ALPHA);
	SO_NODE_DEFINE_ENUM_VALUE(BlendFactor, SRC_ALPHA_SATURATE);
	SO_NODE_SET_SF_ENUM_TYPE(srcFunc, BlendFactor);
	SO_NODE_SET_SF_ENUM_TYPE(dstFunc, BlendFactor);

	SO_NODE_ADD_FIELD(srcFunc, (SRC_ALPHA));
	SO_NODE_ADD_FIELD(dstFunc, (ONE_MINUS_SRC_ALPHA));
}

SoXipBlendFunc::~SoXipBlendFunc()
{
}

void SoXipBlendFunc::initClass()
{
	SO_NODE_INIT_CLASS(SoXipBlendFunc, SoNode, "Node");
	SO_ENABLE(SoGLRenderAction, SoXipBlendFuncElement);
}

void SoXipBlendFunc::GLRender(SoGLRenderAction *action)
{
	SoXipBlendFuncElement::setEnabled(action->getState(), enableBlending.getValue());
	SoXipBlendFuncElement::setBlendFunc(action->getState(), srcFunc.getValue(), dstFunc.getValue());
}
