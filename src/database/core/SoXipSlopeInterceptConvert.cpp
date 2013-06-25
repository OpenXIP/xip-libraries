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
#include <xip/inventor/core/SoXipSlopeInterceptConvert.h>
#include <xip/inventor/core/SoXipValueConvertElement.h>

#include <Inventor/actions/SoActions.h>

#include <Inventor/sensors/SoFieldSensor.h>

SO_NODE_SOURCE( SoXipSlopeInterceptConvert );

SoXipSlopeInterceptConvert::SoXipSlopeInterceptConvert()
: mConvertParams()
{
	SO_NODE_CONSTRUCTOR( SoXipSlopeInterceptConvert);

	SO_NODE_ADD_FIELD(		slope,		(1.0)	);
	SO_NODE_ADD_FIELD(	intercept,		(0.0)	);

}

void
SoXipSlopeInterceptConvert::initClass()
{
	SO_NODE_INIT_CLASS( SoXipSlopeInterceptConvert, SoNode, "SoNode" );

	SO_ENABLE(SoGLRenderAction, SoXipValueConvertElement);
	SO_ENABLE(SoPickAction,     SoXipValueConvertElement);
	SO_ENABLE(SoCallbackAction, SoXipValueConvertElement);
	SO_ENABLE(SoGetBoundingBoxAction, SoXipValueConvertElement);
}


void
SoXipSlopeInterceptConvert::GLRender(SoGLRenderAction *action)
{
	doAction(action);
}

void
SoXipSlopeInterceptConvert::handleEvent(SoGLRenderAction *action)
{
	doAction(action);
}

void
SoXipSlopeInterceptConvert::doAction(SoGLRenderAction *action)
{
    mConvertParams.set(slope.getValue(), intercept.getValue());

	SoXipValueConvertElement::add(action->getState(), this, &mConvertParams);

}
