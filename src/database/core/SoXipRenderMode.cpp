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
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/errors/SoMemoryError.h> 
#include <Inventor/actions/SoActions.h> 
#include <xip/inventor/core/SoXipRenderModeElement.h>
#include "SoXipRenderMode.h"


SO_NODE_SOURCE(SoXipRenderMode);


SoXipRenderMode::SoXipRenderMode()
{
	SO_NODE_CONSTRUCTOR(SoXipRenderMode);

    SO_NODE_DEFINE_ENUM_VALUE(render_mode_t, MPR);
	SO_NODE_DEFINE_ENUM_VALUE(render_mode_t, MAXIP);
	SO_NODE_DEFINE_ENUM_VALUE(render_mode_t, MINIP);
	SO_NODE_DEFINE_ENUM_VALUE(render_mode_t, SSD);
    SO_NODE_DEFINE_ENUM_VALUE(render_mode_t, COLORSSD);
	SO_NODE_DEFINE_ENUM_VALUE(render_mode_t, VRT);
    SO_NODE_DEFINE_ENUM_VALUE(render_mode_t, DRR);
	SO_NODE_SET_SF_ENUM_TYPE(mode, render_mode_t);

	SO_NODE_ADD_FIELD(mode, (MPR));
}


void SoXipRenderMode::initClass()
{
	SO_NODE_INIT_CLASS(SoXipRenderMode, SoNode, "Node");

	SO_ENABLE(SoGLRenderAction, SoXipRenderModeElement);
	SO_ENABLE(SoPickAction,     SoXipRenderModeElement);
	SO_ENABLE(SoCallbackAction, SoXipRenderModeElement);
	SO_ENABLE(SoGetBoundingBoxAction, SoXipRenderModeElement);
}


void SoXipRenderMode::doAction(SoAction * action)
{
	SoXipRenderModeElement::set(action->getState(), this, 
		(SoXipRenderModeElement::RenderModes) mode.getValue());
}
