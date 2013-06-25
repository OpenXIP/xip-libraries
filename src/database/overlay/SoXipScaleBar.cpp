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
//#include <xip/system/GL/glu.h>
//#include <xip/system/standard.h>
#include <Inventor/system/SoStandard.h>
#include "SoXipScaleBar.h"
#include <Inventor/errors/SoError.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoScale.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/elements/SoFontSizeElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include "SoXipDropShadowElement.h"
#include <xip/inventor/overlay/SoXipText2.h>
#include <algorithm>

SO_NODE_SOURCE(SoXipScaleBar);



static SbString xipFormatScaleText(float length)
{
	const char *unit = "mm";
	char tmp[30];
	double intr, frac;

	if (length >= 10.f)
	{
		length /= 10.f;
		unit = "cm";
	}
	else if (length < 0.010f)
	{
		length *= 1000.f;
		unit = "µm";
	}

	frac = modf(length, &intr);
	if (fabs(frac) > 0.00001)
		sprintf(tmp, "%.*f %s", 2 - (int) log10(fabs(frac) * 100.), length, unit);
	else
		sprintf(tmp, "%d %s", (int) intr, unit);

	return SbString(tmp);
}


void SoXipScaleBar::initClass()
{
	SO_NODE_INIT_CLASS(SoXipScaleBar, SoNode, "Node");

	SO_ENABLE(SoGLRenderAction, SoXipDropShadowElement);
}


/** ******************************************************************
 **	  Name: SoXipScaleBar
 **
 **   Description: Constructor
 ** ******************************************************************/
SoXipScaleBar::SoXipScaleBar()
{
	int i;

	SO_NODE_CONSTRUCTOR(SoXipScaleBar);
	SO_NODE_ADD_FIELD(on, (TRUE));

	mTopSeparator = new SoSeparator;
	mTopSeparator->ref();

	mCamera = new SoOrthographicCamera;
	mText = new SoXipText2;
	mScale = new SoScale;
	mTranslation= new SoTranslation;
	mScaleSwitch = new SoSwitch;
	mShadowSwitch = new SoSwitch;

	SoCoordinate3 *coordinates = new SoCoordinate3;
	SoIndexedLineSet *lineSet = new SoIndexedLineSet;
	SoCoordinate3 *coordinates2 = new SoCoordinate3;
	SoIndexedLineSet *lineSet2 = new SoIndexedLineSet;
	SoTranslation *textTrans = new SoTranslation;

	mTopSeparator->addChild(mCamera);
	mTopSeparator->addChild(mTranslation);
	mTopSeparator->addChild(mScale);

	mTopSeparator->addChild(mShadowSwitch);
	SoSeparator *shadowGroup = new SoSeparator;
	mShadowSwitch->addChild(shadowGroup);
	mShadowTranslation = new SoTranslation;
	mShadowColor = new SoBaseColor;
	shadowGroup->addChild(mShadowColor);
	shadowGroup->addChild(mShadowTranslation);
	shadowGroup->addChild(coordinates);
	shadowGroup->addChild(lineSet);
	shadowGroup->addChild(coordinates2);
	shadowGroup->addChild(mScaleSwitch);

	mTopSeparator->addChild(coordinates);
	mTopSeparator->addChild(lineSet);
	mTopSeparator->addChild(coordinates2);
	mTopSeparator->addChild(mScaleSwitch);
	mScaleSwitch->addChild(lineSet2);
	mTopSeparator->addChild(textTrans);
	mTopSeparator->addChild(mText);

	textTrans->translation.setValue(SbVec3f(0, -5.1f, 0));
	mCamera->height.setValue(10);

	// it is very important to disable automatic camera adjustment in order to display the correct scale
	mCamera->viewportMapping.setValue(SoCamera::LEAVE_ALONE);

	mText->vAlignment.setValue(SoXipText2::TOP);
	mText->justification.setValue(SoXipText2::RIGHT);

	for (i = 0; i <= 10; i++)
	{
		coordinates->point.set1Value(i * 2, SbVec3f(0, i - 5, 0));
		coordinates->point.set1Value(i * 2 + 1, SbVec3f(-0.2, i - 5, 0));

		lineSet->coordIndex.set1Value(i * 3 + 0, i * 2);
		lineSet->coordIndex.set1Value(i * 3 + 1, i * 2 + 1);
		lineSet->coordIndex.set1Value(i * 3 + 2, -1);
	}
	lineSet->coordIndex.set1Value(i * 3 + 0, 0);
	lineSet->coordIndex.set1Value(i * 3 + 1, 20);
	lineSet->coordIndex.set1Value(i * 3 + 2, -1);

	for (i = 0; i < 10; i++)
	{
		coordinates2->point.set1Value(i * 2, SbVec3f(0, i - 4.5, 0));
		coordinates2->point.set1Value(i * 2 + 1, SbVec3f(-0.1, i - 4.5, 0));

		lineSet2->coordIndex.set1Value(i * 3 + 0, i * 2);
		lineSet2->coordIndex.set1Value(i * 3 + 1, i * 2 + 1);
		lineSet2->coordIndex.set1Value(i * 3 + 2, -1);
	}
}


/** ******************************************************************
 **	  Name: ~SoXipScaleBar
 **
 **   Description: Destructor
 ** ******************************************************************/
SoXipScaleBar::~SoXipScaleBar()
{
	mTopSeparator->unref();
}


/** ******************************************************************
 **	  Name: GLRender
 **
 **   Description: 
 ** ******************************************************************/
void SoXipScaleBar::GLRender(SoGLRenderAction *action)
{
	// don't do anything if turned off
	if (!on.isIgnored() && !on.getValue()) return;

	SbViewportRegion vpRegion = SoViewportRegionElement::get(action->getState());
	SbVec2s pixels = vpRegion.getViewportSizePixels();

	SbViewVolume viewVolume = SoViewVolumeElement::get(action->getState());
	float height = viewVolume.getHeight();

	if (viewVolume.getProjectionType() != SbViewVolume::ORTHOGRAPHIC)
	{
		// can only show a ruler when in orthographic projection
		return;
	}

	float maxDisplayHeigth = height * 0.666f;
	int markers = 1;
	int digits = log10(maxDisplayHeigth);
	float scale = 1.f;

	if (digits > 0)
	{
		scale = 1.f / pow(10.f, digits);
	}
	else if (digits < 0)
	{
		scale = pow(10.f, 1 - digits);
	}
	else if (maxDisplayHeigth < 1.f)
	{
		scale = 10.f;
	}
	
	if ((scale * maxDisplayHeigth) >= 5.f)
	{
		markers = 5;
	}

	float displayHeight = ((float) markers) / scale;
	float ratio = displayHeight / height;

	if ((displayHeight > 0.000005) && (std::min(pixels[0], pixels[1]) >= 200))
	{
		// this node never notifies changes in children
		enableNotify(FALSE);

		SbBool depthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);

		float xs = 1.f / (pixels[0] / 400.);

		SoState *state = action->getState();
		if (SoXipDropShadowElement::isOn(state))
		{
			mShadowSwitch->whichChild.setValue(0);
			mShadowColor->rgb.setValue(SoXipDropShadowElement::getColor(state));
			SbVec2s offset = SoXipDropShadowElement::getPixelOffset(state);
			float pixelX = 10.f / (float) pixels[0];
			float pixelY = 10.f / (float) pixels[1];
			mShadowTranslation->translation.setValue(SbVec3f((pixelX * ((float) offset[0] - 0.0f)) / xs, pixelY * ((float) offset[1] - 0.0f) / ratio, 0));
		}
		else
		{
			mShadowSwitch->whichChild.setValue(-1);
		}

		float dx = 120.f / pixels[0];
		mTranslation->translation.setValue(SbVec3f((5.f - dx), 0, 0));

		mScaleSwitch->whichChild.setValue((displayHeight >= (maxDisplayHeigth / 2.f)) ? 0 : -1);
		mText->string.setValue(xipFormatScaleText(markers * (1.f / scale)).getString());

		mScale->scaleFactor.setValue(SbVec3f(xs, ratio, 1));

		glPushMatrix();
		action->traverse(mTopSeparator);
		glPopMatrix();

		if (depthTestEnabled)
			glEnable(GL_DEPTH_TEST);
	}
}


void SoXipScaleBar::getBoundingBox(SoGetBoundingBoxAction *action)
{
	// scale bar does not affect bounding box
}


