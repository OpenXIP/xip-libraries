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
#include <xip/inventor/coregl/SoXipFramebufferElement.h>
#include <xip/inventor/coregl/SoXipFramebufferFlip.h>

SO_NODE_SOURCE(SoXipFramebufferFlip);

SoXipFramebufferFlip::SoXipFramebufferFlip() {
	SO_NODE_CONSTRUCTOR(SoXipFramebufferFlip);
}

void SoXipFramebufferFlip::initClass() {
	SO_NODE_INIT_CLASS(SoXipFramebufferFlip, SoNode, "SoNode");

	SO_ENABLE(SoGLRenderAction, SoXipFramebufferElement);
}

void SoXipFramebufferFlip::GLRender(SoGLRenderAction* action) {
	SoXipFramebufferElement::flip(action->getState());
}


