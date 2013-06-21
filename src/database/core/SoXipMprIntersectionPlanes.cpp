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

#include <xip/system/GL/gl.h>

#include "SoXipMprIntersectionPlanes.h"
#include <Inventor/nodes/SoSeparator.h>
#include <xip/inventor/core/SoXipMprPlaneElement.h>
#include "SoXipIntersectionPlane.h"
#include <xip/inventor/core/XipGeomUtils.h>



SO_NODE_SOURCE(SoXipMprIntersectionPlanes);


SoXipMprIntersectionPlanes::SoXipMprIntersectionPlanes()
{
	SO_NODE_CONSTRUCTOR(SoXipMprIntersectionPlanes);

	SO_NODE_ADD_FIELD(on, (TRUE));

	SO_NODE_DEFINE_ENUM_VALUE(partsType, ALL);
	SO_NODE_DEFINE_ENUM_VALUE(partsType, FRONT);
	SO_NODE_DEFINE_ENUM_VALUE(partsType, BACK);
	SO_NODE_SET_SF_ENUM_TYPE(parts, partsType);
	SO_NODE_ADD_FIELD(parts, (ALL));

	SO_NODE_ADD_FIELD(viewBoundingBox, (SbMatrix::identity()));

	mColor = 0;
	mIntersectionPlane = 0;

	mSeparator = new SoSeparator;
	if (mSeparator)
	{
		mSeparator->ref();

/*		mSeparator->renderCaching.setValue(SoSeparator::OFF);
		mSeparator->boundingBoxCaching.setValue(SoSeparator::OFF);
		mSeparator->renderCulling.setValue(SoSeparator::OFF);
		mSeparator->pickCulling.setValue(SoSeparator::OFF);
*/
		mColor = new SoBaseColor;
		if (mColor)
		{
			mSeparator->addChild(mColor);
		}

		mIntersectionPlane = new SoXipIntersectionPlane;
		if (mIntersectionPlane)
		{
			mSeparator->addChild(mIntersectionPlane);
		}
	}
}


SoXipMprIntersectionPlanes::~SoXipMprIntersectionPlanes()
{
	if (mSeparator)
	{
		mSeparator->unref();
	}
}


void SoXipMprIntersectionPlanes::initClass()
{
	SO_NODE_INIT_CLASS(SoXipMprIntersectionPlanes, SoNode, "Node");

	SO_ENABLE(SoGLRenderAction, SoXipMprPlaneElement);
}


void SoXipMprIntersectionPlanes::GLRender(SoGLRenderAction * action)
{
	if (!mIntersectionPlane || !mColor) return;
	if (!on.getValue()) return;

	// check state
	SoState *state = action->getState();
	if (!state) return;

	SoXipMprPlaneElement *element = SoXipMprPlaneElement::getInstance(state);
	if (!element) return;

	int numPlanes = element->getNum();
	if (numPlanes <= 0) return;

	GLboolean lightEnabled = glIsEnabled(GL_LIGHTING);
	glDisable(GL_LIGHTING);

	mIntersectionPlane->boundingBox.setValue(viewBoundingBox.getValue());

	SbPlane plane;
	SbColor color;
	for (int i = 0; i < numPlanes; i++)
	{
		plane = XipGeomUtils::planeFromMatrix(element->getMatrix(i));
		color = element->getColor(i);

		if (i > 0)
		{
			SbPlane newPlane = mIntersectionPlane->plane.getValue();
			if ((newPlane.getNormal() - plane.getNormal()).length() < 0.001)
			{
				if (fabs(newPlane.getDistanceFromOrigin() - plane.getDistanceFromOrigin()) <= 0.001)
				{
					continue;
				}
			}
		}

		mIntersectionPlane->plane.setValue(plane);

		if ((parts.getValue() == BACK) || (parts.getValue() == ALL))
		{
			mColor->rgb.setValue(color * 0.6f);
			mIntersectionPlane->parts.setValue(SoXipIntersectionPlane::BACK);
			
			action->traverse(mSeparator);
		}

		if ((parts.getValue() == FRONT) || (parts.getValue() == ALL))
		{
			mColor->rgb.setValue(color);
			mIntersectionPlane->parts.setValue(SoXipIntersectionPlane::FRONT);

			action->traverse(mSeparator);
		}
	}

	if (lightEnabled)
		glEnable(GL_LIGHTING);
}


