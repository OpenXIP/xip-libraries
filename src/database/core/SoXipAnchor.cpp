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


#include "SoXipAnchor.h"
#include <Inventor/actions/SoActions.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>


SO_NODE_SOURCE(SoXipAnchor);


void SoXipAnchor::initClass()
{
	SO_NODE_INIT_CLASS(SoXipAnchor, SoNode, "Node");

	// enable elements goes here
	// SO_ENABLE(SoGLRenderAction, ...);
}


SoXipAnchor::SoXipAnchor()
{
	SO_NODE_CONSTRUCTOR(SoXipAnchor);

	mTranslation = SbVec3f(0, 0, 0);

	SO_NODE_ADD_FIELD(left, (FALSE));
	SO_NODE_ADD_FIELD(top, (FALSE));
	SO_NODE_ADD_FIELD(right, (FALSE));
	SO_NODE_ADD_FIELD(bottom, (FALSE));
}


SoXipAnchor::~SoXipAnchor()
{
}


void SoXipAnchor::doAction(SoAction *action)
{
	SoModelMatrixElement::translateBy(action->getState(), this, mTranslation);
}


void SoXipAnchor::GLRender(SoGLRenderAction *action)
{
	SbViewVolume vv = SoViewVolumeElement::get(action->getState());

	SbVec3f centerVec = vv.getPlanePoint(vv.getNearDist(), SbVec2f(0.5, 0.5));
	SbVec3f rightVec = vv.getPlanePoint(vv.getNearDist(), SbVec2f(1, 0.5));
	SbVec3f upVec = vv.getPlanePoint(vv.getNearDist(), SbVec2f(0.5, 1));

	mTranslation = SbVec3f(0, 0, 0);

	if (vv.getWidth() > vv.getHeight())
	{
		if (left.getValue())
		{
			mTranslation = rightVec - centerVec;
			mTranslation.normalize();
			mTranslation *= -0.5f * (vv.getWidth() - vv.getHeight());
		}

		if (right.getValue())
		{
			mTranslation = rightVec - centerVec;
			mTranslation.normalize();
			mTranslation *= 0.5f * (vv.getWidth() - vv.getHeight());
		}
	}
	else
	{
		if (top.getValue())
		{
			mTranslation = upVec - centerVec;
			mTranslation.normalize();
			mTranslation *= 0.5f * (vv.getHeight() - vv.getWidth());
		}

		if (bottom.getValue())
		{
			mTranslation = upVec - centerVec;
			mTranslation.normalize();
			mTranslation *= -0.5f * (vv.getHeight() - vv.getWidth());
		}
	}

	doAction(action);
}


void SoXipAnchor::handleEvent(SoHandleEventAction *action)
{
	doAction(action);
}


void SoXipAnchor::callback(SoCallbackAction *action)
{
	doAction(action);
}


void SoXipAnchor::getBoundingBox(SoGetBoundingBoxAction *action)
{
	doAction(action);
}


void SoXipAnchor::pick(SoPickAction *action)
{
	doAction(action);
}
