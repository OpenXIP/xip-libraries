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
#include <xip/inventor/coregl/SoXipBufferMaskElement.h>
#include "SoXipBufferMask.h"

SO_NODE_SOURCE(SoXipBufferMask);

SoXipBufferMask::SoXipBufferMask() {
	SO_NODE_CONSTRUCTOR(SoXipBufferMask);
	SO_NODE_ADD_FIELD(maskRed, (true));
	SO_NODE_ADD_FIELD(maskGreen, (true));
	SO_NODE_ADD_FIELD(maskBlue, (true));
	SO_NODE_ADD_FIELD(maskAlpha, (true));
	SO_NODE_ADD_FIELD(maskDepth, (true));
}

SoXipBufferMask::~SoXipBufferMask() {
}

void SoXipBufferMask::initClass() {
	SO_NODE_INIT_CLASS(SoXipBufferMask, SoNode, "Node");
	SO_ENABLE(SoGLRenderAction, SoXipBufferMaskElement);
}

void SoXipBufferMask::GLRender(SoGLRenderAction *action) {
	SoXipBufferMaskElement::setColorMask(action->getState(), maskRed.getValue(), maskGreen.getValue(), maskBlue.getValue(), maskAlpha.getValue());
	SoXipBufferMaskElement::setDepthMask(action->getState(), maskDepth.getValue());
}


