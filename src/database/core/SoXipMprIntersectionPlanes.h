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
#ifndef SOXIPMPRINTERSECTIONPLANES_H
#define SOXIPMPRINTERSECTIONPLANES_H

#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/nodes/SoBaseColor.h>

class SoXipIntersectionPlane;


// utility class for grouping nodes of the intersection line geometry
class SoXipMprIntersectionPlanes : public SoNode
{
	SO_NODE_HEADER(SoXipMprIntersectionPlanes);

public:
	SoXipMprIntersectionPlanes();
	static void initClass();

public:
	enum partsType {
		ALL   = 0x01,
		FRONT = 0x02,
		BACK  = 0x03
	};

	SoSFBool on;
	SoSFEnum parts;
	SoSFMatrix viewBoundingBox;

protected:
	virtual ~SoXipMprIntersectionPlanes();
	virtual void GLRender(SoGLRenderAction * action);

	SoXipIntersectionPlane *mIntersectionPlane;
	SoBaseColor *mColor;
	SoSeparator *mSeparator;
};


#endif // SOXIPMPRINTERSECTIONPLANES_H
