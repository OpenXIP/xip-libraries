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
#include <xip/inventor/core/SoXipValueConvertBase.h>
#include <xip/inventor/core/SoXipValueConvertElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoHandleEventAction.h>

SO_NODE_SOURCE( SoXipValueConvertBase );

SoXipValueConvertBase::SoXipValueConvertBase()
{
	SO_NODE_CONSTRUCTOR( SoXipValueConvertBase);
}

void SoXipValueConvertBase::initClass()
{
	SO_NODE_INIT_CLASS( SoXipValueConvertBase, SoNode, "Node" );

	SO_ENABLE(SoHandleEventAction,	SoXipValueConvertElement	);
	SO_ENABLE(SoGLRenderAction,		SoXipValueConvertElement	);
}

float SoXipValueConvertBase::getValueConverted(float val_in)
{
	//base class just return the input
	return val_in;
}

void
SoXipValueConvertBase::GLRender(SoGLRenderAction *action)
{
	doAction(action);
}

void
SoXipValueConvertBase::handleEvent(SoGLRenderAction *action)
{
	doAction(action);
}

void
SoXipValueConvertBase::doAction(SoGLRenderAction *action)
{
	if (this!=SoXipValueConvertElement::getConvertObject(action->getState()))
		SoXipValueConvertElement::setConvertObject(action->getState(), this, this);
}
