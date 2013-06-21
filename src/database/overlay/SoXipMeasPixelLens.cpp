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

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/elements/SoGLCoordinateElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/elements/SoBBoxModelMatrixElement.h>
#include <xip/inventor/core/SbXipCoordinateTransform.h>
#include "SoXipMeasPixelLens.h"
#include <xip/inventor/overlay/SoXipText2.h>
#include "SoXipDropShadowElement.h"
#include "geomutils.h"

SO_KIT_SOURCE(SoXipMeasPixelLens);


void SoXipMeasPixelLens::initClass()
{
	SO_KIT_INIT_CLASS(SoXipMeasPixelLens, SoBaseKit, "BaseKit");
	SO_ENABLE(SoGLRenderAction, SoXipDropShadowElement);
}


SoXipMeasPixelLens::SoXipMeasPixelLens()
{
	mHasPickedPoint = FALSE;
	mHasPickedPointChanged = TRUE;

	SO_KIT_CONSTRUCTOR(SoXipMeasPixelLens);

	SO_KIT_ADD_CATALOG_ENTRY(separator, SoSeparator, FALSE, this, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(pickStyle, SoPickStyle, FALSE, separator, \0, FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(coordinate, SoCoordinate3, FALSE, separator, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(pointset, SoPointSet, FALSE, separator, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(translation, SoTranslation, FALSE, separator, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(text, SoXipText2, FALSE, separator, \0 , FALSE);

	SO_KIT_INIT_INSTANCE();

	SO_NODE_ADD_FIELD(on, (TRUE));
	SO_NODE_ADD_FIELD(image, (0));
	SO_NODE_ADD_FIELD(offset, (0));

	// output
	SO_NODE_ADD_FIELD(position, (SbVec3f(0, 0, 0)) );

	mShadowColor = new SoBaseColor;
	mShadowColor->ref();
	mShadowTranslation = new SoTranslation;
	mShadowTranslation->ref();

	pickStyle.getValue()->set( "style UNPICKABLE" );
}


SoXipMeasPixelLens::~SoXipMeasPixelLens()
{
	mShadowColor->unref();
	mShadowTranslation->unref();
}


void SoXipMeasPixelLens::GLRender(SoGLRenderAction *action)
{
	SoCoordinate3 *coord = (SoCoordinate3*) getAnyPart("coordinate", TRUE);
	if (!coord) return;

	SoXipText2 *text2 = (SoXipText2*) getAnyPart("text", TRUE);
	if (!text2) return;

	if (on.getValue() && image.getValue() && mHasPickedPoint)
	{
		if (mHasPickedPointChanged)
		{
			// need to get voxel value in the GLRender() method since
			// the model matrix element is not set in handleEvent()
			SbMatrix transformMatrix = SoBBoxModelMatrixElement::get(action->getState());
			SbVec3f noTransPt, pickPt = mPickedPoint;
			transformMatrix.inverse().multVecMatrix(pickPt, noTransPt);
			
			float value = 0;
			if (getVoxelValue(noTransPt, value))
			{
				SoTranslation *trans = (SoTranslation*) getAnyPart("translation", TRUE);
				trans->translation.setValue(noTransPt);
				coord->point.setValue(noTransPt);

				char tmp[30];
				SbBool isFloat = FALSE;

				SbXipImage *img = image.getValue()->get();
				if (img)
				{
					if (img->getType() == SbXipImage::FLOAT)
					{
						isFloat = TRUE;
					}
				}

				sprintf(tmp, isFloat ? "  %.3f" : "  %.0f", value + (float) offset.getValue());

				text2->string.setValue(tmp);
				text2->vAlignment.setValue(SoXipText2::BOTTOM);

				mHasPickedPointChanged = FALSE;
			}
			else
			{
				// mouse is outside of volume
				text2->string.setValue("");
			}
		}

		GLboolean isDepthOn = glIsEnabled(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);

		// push state because we will turn drop shadow for the text off since it is handled here
		action->getState()->push();

		// render shadow first
		if (SoXipDropShadowElement::isOn(action->getState()))
		{
			SbVec2s offset = SoXipDropShadowElement::getPixelOffset(action->getState());
			SbVec3f xPixelVec, yPixelVec;
			getScreenPixelVectors(action, mPickedPoint, xPixelVec, yPixelVec);
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
	else
	{
		coord->point.setNum(0);
		text2->string.setValue("");

		mHasPickedPoint = FALSE;
	}
}


void SoXipMeasPixelLens::handleEvent(SoHandleEventAction *action)
{
	if (on.getValue() && !action->getGrabber() && image.getValue())
	{
		SoState *state = action->getState();
		const SoEvent *event = action->getEvent();

		if (event->isOfType(SoLocation2Event::getClassTypeId()))		
		{
			// CULLING is on when getting picked point from SoHandleEventAction but IVT has some problem with it
			//const SoPickedPoint *pickedPoint = action->getPickedPoint();

			mHasPickedPoint = FALSE;

			SoRayPickAction pa(action->getViewportRegion());
			pa.setPoint(action->getEvent()->getPosition());
			pa.setRadius(3);
			pa.enableCulling(FALSE);
			pa.apply(action->getNodeAppliedTo());
			const SoPickedPoint *pickedPoint = pa.getPickedPoint();

			if (pickedPoint)
			{
				mPickedPoint = pickedPoint->getPoint();
				mHasPickedPoint = TRUE;
				mHasPickedPointChanged = TRUE;

				position.setValue(mPickedPoint);
			}
			else
			{
				position.setValue(SbVec3f(0, 0, 0));
			}

			startNotify();
		}
	}

	SoBaseKit::handleEvent(action);
}


SbBool SoXipMeasPixelLens::getVoxelValue(const SbVec3f &position, float &value)
{
	SbXipImage *img = image.getValue()->get();
	if (img)
	{
		if (img->getComponents() == 1)
		{
			XipWorldToImageConvert cvt( img->getModelMatrix(), img->getDimStored() );
			
			SbVec3s index;
			if( cvt.getIndexTest( position, index ) )
			{
				int x = index[0];
				int y = index[1];
				int z = index[2];

				const void *ptr = img->refBufferPtr();

				int lineSize = img->getDimAllocated()[0];
				int sliceSize = lineSize * img->getDimAllocated()[1];

				switch (img->getType())
				{
				case SbXipImage::UNSIGNED_BYTE:
					{
						unsigned char *p = (unsigned char *) ptr;
						value = p[sliceSize * z + lineSize * y + x];
					} break;
				case SbXipImage::UNSIGNED_SHORT:
					{
						unsigned short *p = (unsigned short *) ptr;
						value = p[sliceSize * z + lineSize * y + x];
					} break;
				case SbXipImage::FLOAT:
					{
						float *p = (float *) ptr;
						value = p[sliceSize * z + lineSize * y + x];
					} break;
				default:
					img->unrefBufferPtr();
					return FALSE;
				}

				img->unrefBufferPtr();

				return TRUE;
			}
		}
	}

	return FALSE;
}

void SoXipMeasPixelLens::getBoundingBox(SoGetBoundingBoxAction *action)
{
	if (on.getValue())
	{
		SoBaseKit::getBoundingBox(action);
	}
}


