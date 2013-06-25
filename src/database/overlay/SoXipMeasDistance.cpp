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

#include "geomutils.h"
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/elements/SoGLCoordinateElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/SoPickedPoint.h>
#include "SoXipMeasDistance.h"
#include <xip/inventor/overlay/SoXipText2.h>
#include "SoXipDropShadowElement.h"


SO_KIT_SOURCE(SoXipMeasDistance);


void SoXipMeasDistance::initClass()
{
	SO_KIT_INIT_CLASS(SoXipMeasDistance, SoBaseKit, "BaseKit");
	SO_ENABLE(SoGLRenderAction, SoXipDropShadowElement);
}


SoXipMeasDistance::SoXipMeasDistance()
{
	SO_KIT_CONSTRUCTOR(SoXipMeasDistance);

	SO_KIT_ADD_CATALOG_ENTRY(separator, SoSeparator, FALSE, this, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(coordinate, SoCoordinate3, FALSE, separator, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(lineset, SoLineSet, FALSE, separator, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(pointset, SoPointSet, FALSE, separator, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(translation, SoTranslation, FALSE, separator, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(text, SoXipText2, FALSE, separator, \0 , FALSE);

	SO_KIT_INIT_INSTANCE();

	SO_NODE_ADD_FIELD(on, (TRUE));

	SO_NODE_DEFINE_ENUM_VALUE(locationType, NEAR_PLANE);
	SO_NODE_DEFINE_ENUM_VALUE(locationType, FOCAL_PLANE);
	SO_NODE_DEFINE_ENUM_VALUE(locationType, PICKING);

	SO_NODE_SET_SF_ENUM_TYPE(location, locationType);
	SO_NODE_ADD_FIELD(location, (FOCAL_PLANE));
	SO_NODE_ADD_FIELD(point, (SbVec3f(0, 0, 0)));
	point.setNum(0);

	mPointToBeModified = 0;
	mPlaneProj = new SbPlaneProjector(FALSE);
	mViewport = SbViewportRegion(1, 1);

	mShadowColor = new SoBaseColor;
	mShadowColor->ref();
	mShadowTranslation = new SoTranslation;
	mShadowTranslation->ref();
}


SoXipMeasDistance::~SoXipMeasDistance()
{
	if (mPlaneProj)
	{
		delete mPlaneProj;
		mPlaneProj = 0;
	}

	mShadowColor->unref();
	mShadowTranslation->unref();
}


void SoXipMeasDistance::GLRender(SoGLRenderAction *action)
{
	SoCoordinate3 *coord = (SoCoordinate3*) getAnyPart("coordinate", TRUE);
	if (!coord) return;

	if (on.getValue())
	{
		SbBool saveNotify = enableNotify( FALSE );

		// update coordinate node within the kit
		coord->point = point;

		if (coord->point.getNum() == 2)
		{
			const SbVec3f *points = coord->point.getValues(0);
			if ((points[0] - points[1]).length() > 0.0)
			{
				// update text
				SbVec3f p1 = points[0];
				SbVec3f p2 = points[1];
				SbVec3f s1, s2;

				SbMatrix affine, proj;
				SbViewVolume vv = SoViewVolumeElement::get(action->getState());
				vv.getMatrices(affine, proj);

				// project to screen
				SbMatrix mat = affine;
				mat.multVecMatrix(p1, s1);
				mat.multVecMatrix(p2, s2);

				SbBool down;
				if (s1[0] < s2[0])
				{
					down = (s1[1] < s2[1]);
				}
				else
				{
					down = (s1[1] > s2[1]);
				}

				SbVec3f pos = p1 + (p2 - p1) / 2.f;

				SoTranslation *trans = (SoTranslation*) getAnyPart("translation", TRUE);
				trans->translation.setValue(pos);

				SoXipText2 *text2 = (SoXipText2*) getAnyPart("text", TRUE);
				text2->vAlignment.setValue(down ? SoXipText2::TOP : SoXipText2::BOTTOM);

				char strDistance[30];
				sprintf(strDistance, "\n  %s\n", formatLength((p2 - p1).length()));
				text2->string.setValue(strDistance);

				GLboolean isDepthOn = glIsEnabled(GL_DEPTH_TEST);
				glDisable(GL_DEPTH_TEST);

				// push state because we will turn drop shadow for the text off since it is handled here
				action->getState()->push();

				// render shadow first
				if (SoXipDropShadowElement::isOn(action->getState()))
				{
					SbVec2s offset = SoXipDropShadowElement::getPixelOffset(action->getState());
					SbVec3f xPixelVec, yPixelVec;
					getScreenPixelVectors(action, points[0], xPixelVec, yPixelVec);
					xPixelVec *= offset[0];
					yPixelVec *= offset[1];

					mShadowColor->rgb.setValue(SoXipDropShadowElement::getColor(action->getState()));
					mShadowTranslation->translation.setValue(xPixelVec + yPixelVec);

					// push state to restore default diffuse color after rendering the shadows
					action->getState()->push();
					SoXipDropShadowElement::set(action->getState(), this, FALSE, SbColor(0, 0, 0), 0, SbVec2s(0, 0));

					action->traverse(mShadowColor);
					action->traverse(mShadowTranslation);
					SoBaseKit::GLRender(action);

					action->getState()->pop();
				}

				SoBaseKit::GLRender(action);
				action->getState()->pop();

				if (isDepthOn)
					glEnable(GL_DEPTH_TEST);
			}
		}

		enableNotify( saveNotify );
	}
	else
	{
		coord->point.setNum(0);
	}
}


void SoXipMeasDistance::handleEvent(SoHandleEventAction *action)
{
	if (on.getValue())
	{
		if (!action->getGrabber())
		{
			SoState *state = action->getState();

			mViewVolume = SoViewVolumeElement::get(state);
			mPlaneProj->setViewVolume(mViewVolume);
			float distance = mViewVolume.getDepth() / 2.f;
			if (location.getValue() == NEAR_PLANE)
			{
				// move slighty inwards of nearplane to ensure proper drawing
				distance = 0.001;
			}
			mPlaneProj->setPlane(mViewVolume.getPlane(mViewVolume.getNearDist() + distance));
			mViewport = SoViewportRegionElement::get(state);

			mPixelSpacing = mViewVolume.getHeight() / (float) mViewport.getViewportSizePixels()[1];
		}

		const SoEvent *event = action->getEvent();
		SbVec3f pos = mPlaneProj->project(event->getNormalizedPosition(mViewport));

		if (location.getValue() == PICKING)
		{
			// CULLING is on when getting picked point from SoHandleEventAction but IVT has some problem with it
			//const SoPickedPoint *pickedPoint = action->getPickedPoint();
			SoRayPickAction pa(action->getViewportRegion());
			pa.setPoint(action->getEvent()->getPosition());
			pa.setRadius(3);
			pa.enableCulling(FALSE);
			pa.apply(action->getNodeAppliedTo());
			const SoPickedPoint *pickedPoint = pa.getPickedPoint();

			if (pickedPoint)
			{
				pos = pickedPoint->getPoint();
			}
		}

		if (SO_MOUSE_PRESS_EVENT(event, BUTTON1) && !action->getGrabber())
		{
			mLastMousePos = pos;
			mPointToBeModified = 1;

			if (point.getNum() == 2)
			{
				SbLine line(point.getValues(0)[0], point.getValues(0)[1]);

				if ((point.getValues(0)[0] - pos).length() <= (mPixelSpacing * 6.f))
				{
					// modify first point
					mPointToBeModified = 0;
				}
				else if ((point.getValues(0)[1] - pos).length() <= (mPixelSpacing * 6.f))
				{
					// modify second point
				}
				else if ((line.getClosestPoint(pos) - pos).length() <= (mPixelSpacing * 6.f))
				{
					SbVec3f p1 = point.getValues(0)[0];
					SbVec3f p2 = point.getValues(0)[1];
					SbVec3f center = p1 + (p2 - p1) / 2.f;
					float len = (p2 - p1).length();

					if ( (pos - center).length() <= (len / 2.f) )
					{
						// move line
						mPointToBeModified = -1;
					}
					else
					{
						point.setValue(pos);
					}
				}
				else
				{
					point.setValue(pos);
				}
			}
			else
			{
				point.setValue(pos);
			}

			action->setGrabber(this);
			action->setHandled();

			if (point.getNum() == 1)
			{
				SoXipText2 *text2 = (SoXipText2*) getAnyPart("text", TRUE);
				text2->string.setValue("");
			}
		}
		else if ((action->getGrabber() == this) && 
				(SO_MOUSE_RELEASE_EVENT(event, BUTTON1) || event->isOfType(SoLocation2Event::getClassTypeId())))
		{
			if (mPointToBeModified < 0)
			{
				// move line and text
				point.set1Value(0, point.getValues(0)[0] + (pos - mLastMousePos));
				point.set1Value(1, point.getValues(0)[1] + (pos - mLastMousePos));

				SoTranslation *trans = (SoTranslation*) getAnyPart("translation", TRUE);
				trans->translation.setValue(trans->translation.getValue() + (pos - mLastMousePos));
			}
			else
			{
				// move end point
				point.set1Value(mPointToBeModified, pos);
				point.setNum(2);
			}

			if (SO_MOUSE_RELEASE_EVENT(event, BUTTON1))
			{
				action->releaseGrabber();
			}

			action->setHandled();
		}

		mLastMousePos = pos;

		SoBaseKit::handleEvent(action);
	}
}

void SoXipMeasDistance::getBoundingBox(SoGetBoundingBoxAction *action)
{
	if (on.getValue())
	{
		SoBaseKit::getBoundingBox(action);
	}
}


