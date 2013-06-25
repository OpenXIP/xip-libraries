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
/**
*	@file    SoXipMarkerSet.h
*	@brief   Declaration of the SoXipMarkerSet class
*	@author  Julien Gein
*	@author  Thomas Moeller
**/

#ifndef SOXIPMARKERSET_H
#define SOXIPMARKERSET_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFEnum.h>

class SoCoordinate3;
class SoFaceSet;
class SoScale;
class SoTranslation;
class SoRotation;

class SoXipMarkerSet : public SoShape
{
	SO_NODE_HEADER( SoXipMarkerSet );

public:
	SoXipMarkerSet();

	SoSFEnum		marker;

	static void initClass();

protected:
	virtual ~SoXipMarkerSet();

	virtual void GLRender( SoGLRenderAction* action );

	virtual void generatePrimitives( class SoAction* );
	virtual void computeBBox( SoAction* action, SbBox3f& box, SbVec3f& center );

	SoCoordinate3*	mCoord;
	SoFaceSet*		mFaceSet;
	SoTranslation*	mTranslation;
	SoScale*		mScale;
	SoRotation*		mRotation;
};

#endif // SOXIPMARKERSET_H
