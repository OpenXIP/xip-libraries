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
#ifndef SOXIPSCALEBAR_H
#define SOXIPSCALEBAR_H


#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/fields/SoSFBool.h>

class SoSeparator;
class SoOrthographicCamera;
class SoXipText2;
class SoScale;
class SoTranslation;
class SoSwitch;
class SoBaseColor;


/** ***********************************************************
 **
 **  Name: SoXipScaleBar
 **
 **  Description: Class required to display scale bar on the image
 **
 ** **********************************************************/
class SoXipScaleBar : public SoNode  
{
	SO_NODE_HEADER(SoXipScaleBar);

public:
	SoXipScaleBar();
	static void initClass();

	SoSFBool on;

protected:
	virtual ~SoXipScaleBar();
	virtual void GLRender(SoGLRenderAction *action);
	virtual void getBoundingBox(SoGetBoundingBoxAction *action);

	SoSeparator *mTopSeparator;
	SoOrthographicCamera *mCamera;
	SoTranslation *mTranslation; 
	SoXipText2 *mText;
	SoScale *mScale;
	SoSwitch *mScaleSwitch;
	SoSwitch *mShadowSwitch;
	SoTranslation *mShadowTranslation; 
	SoBaseColor *mShadowColor; 
};

#endif // SOXIPSCALEBAR_H

