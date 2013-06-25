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
#include "SoXipDepthTest.h"
#include <xip/inventor/coregl/SoXipDepthTestElement.h>

SO_NODE_SOURCE(SoXipDepthTest);

SoXipDepthTest::SoXipDepthTest() {
	SO_NODE_CONSTRUCTOR(SoXipDepthTest);

	SO_NODE_ADD_FIELD(enableDepthTest, (true));

	SO_NODE_DEFINE_ENUM_VALUE(DepthFunc, NEVER);
	SO_NODE_DEFINE_ENUM_VALUE(DepthFunc, ALWAYS);
	SO_NODE_DEFINE_ENUM_VALUE(DepthFunc, LESS);
	SO_NODE_DEFINE_ENUM_VALUE(DepthFunc, LEQUAL);
	SO_NODE_DEFINE_ENUM_VALUE(DepthFunc, EQUAL);
	SO_NODE_DEFINE_ENUM_VALUE(DepthFunc, GEQUAL);
	SO_NODE_DEFINE_ENUM_VALUE(DepthFunc, GREATER);
	SO_NODE_DEFINE_ENUM_VALUE(DepthFunc, NOTEQUAL);
	SO_NODE_SET_SF_ENUM_TYPE(depthFunc, DepthFunc);

	SO_NODE_ADD_FIELD(depthFunc, (LESS));
}

SoXipDepthTest::~SoXipDepthTest() {
}

void SoXipDepthTest::initClass() {
	SO_NODE_INIT_CLASS(SoXipDepthTest, SoNode, "Node");

	SO_ENABLE(SoGLRenderAction, SoXipDepthTestElement);
}

void SoXipDepthTest::GLRender(SoGLRenderAction *action) {
	SoXipDepthTestElement::setEnabled(action->getState(), enableDepthTest.getValue());
	SoXipDepthTestElement::setDepthFunc(action->getState(), depthFunc.getValue());
}


