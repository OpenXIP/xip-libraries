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
#include "SoXipAntiAliasing.h"

#include <xip\inventor\core\SoXipAntiAliasingElement.h>


SO_NODE_SOURCE(SoXipAntiAliasing);


void SoXipAntiAliasing::initClass()
{
	SO_NODE_INIT_CLASS(SoXipAntiAliasing, SoNode, "Node");

	SO_ENABLE(SoGLRenderAction, SoXipAntiAliasingElement);
}


SoXipAntiAliasing::SoXipAntiAliasing()
{
	SO_NODE_CONSTRUCTOR(SoXipAntiAliasing);
	SO_NODE_ADD_FIELD(active, (FALSE));

	mActive = !active.getValue();
}


SoXipAntiAliasing::~SoXipAntiAliasing()
{
}

void SoXipAntiAliasing::GLRender(SoGLRenderAction *action)
{
//	SoXipAntiAliasingElement::set(action->getState(), this, active.getValue());

//	if (mActive != active.getValue())
//	{
		if (active.getValue())
		{
//			mTransparencyType = action->getTransparencyType();
//			action->setTransparencyType(SoGLRenderAction::TransparencyType::SCREEN_DOOR);
			action->setSmoothing(1);
		}
		else
		{
			action->setSmoothing(0);
//			action->setTransparencyType(SoGLRenderAction::TransparencyType::BLEND);
		}
//	}
}
