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
#include <xip/inventor/core/SoXipMultiTextureElement.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>

#include "SoXipTextureUnit.h"

SO_NODE_SOURCE(SoXipTextureUnit);

//
//! ctor of SoXipTextureUnit.
//! 
//
SoXipTextureUnit::SoXipTextureUnit()
{
	SO_NODE_CONSTRUCTOR(SoXipTextureUnit);
	SO_NODE_ADD_FIELD(textureStage, (0));
	SO_NODE_ADD_FIELD(autoGenerate, (true));
}


//
//! destructor
//! 
//
SoXipTextureUnit::~SoXipTextureUnit()
{
}

void SoXipTextureUnit::initClass()
{
	SO_NODE_INIT_CLASS(SoXipTextureUnit, SoNode, "Node");
	SO_ENABLE(SoGLRenderAction, SoXipMultiTextureElement);
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
}

//
//! GLRender.
//! 
//! sets the active texture unit (via MultiTextureElement)
//
void SoXipTextureUnit::GLRender(SoGLRenderAction *action)
{
#if 1
    if (autoGenerate.getValue())
        if (textureStage.getValue() != SoXipMultiTextureElement::getFreeUnit(action->getState()))
	        textureStage.setValue(SoXipMultiTextureElement::getFreeUnit(action->getState()));
#else
	if (autoGenerate.getValue())
        textureStage.setValue(SoXipMultiTextureElement::getFreeUnit(action->getState()));
#endif
	SoXipMultiTextureElement::setUnit(action->getState(), textureStage.getValue());
}


