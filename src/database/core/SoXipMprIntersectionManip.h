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

#ifndef SOXIPMPRINTERSECTIONMANIP_H
#define SOXIPMPRINTERSECTIONMANIP_H

#include "SoXipPlaneManipBase.h"
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/SbColor.h>
#include <Inventor/SbLinear.h>
#include <vector>


class SoSeparator;
class SoCoordinate3;
class SoDrawStyle;
class SoLineSet;
class SoFieldSensor;
class SoXipMprIntersectionLine;
class SoSFMatrix;
class SoSFVec3f;
class SoSensor;


class SoXipMprIntersectionManip : public SoXipPlaneManipBase
{
	SO_NODE_HEADER(SoXipMprIntersectionManip);

public:
	SoXipMprIntersectionManip();
	static void initClass();
	static void setPickRadius(float radius);

protected:
	virtual ~SoXipMprIntersectionManip();

public:
	/// enum for Blending modes 
	enum modeType {
		INTERSECTION,
		TRANSLATION,
		FREE
	};

	SoSFBool on;
	SoSFEnum mode;
	SoSFBool   stubs;
	SoSFFloat  stubScale;

protected:
	virtual SbBool dragBegin();
	virtual SbBool dragMove();
	virtual SbBool dragEnd();
	virtual void dragMoveFree();
	virtual void dragMoveIntersection();
	virtual int  getPickedLine();
	virtual void GLRender(SoGLRenderAction * action);
	virtual void callback(SoCallbackAction *action);
	virtual void pick(SoPickAction *action);
	virtual void updateElement(SoAction *action);
	virtual void updateGeometry();
	virtual void fieldSensorCB(SoSensor *sensor);
	virtual void handleEvent(SoHandleEventAction *action);
	virtual void getBoundingBox(SoGetBoundingBoxAction *action);
	virtual void inputChanged(SoField *which, SoSensor *sensor);


	// Member Variables
	struct planeStruct
	{
		SbMatrix matrix;
		SbVec3f center;
		SbColor color;
		SoSFMatrix *matrixField;
		SoSFVec3f *centerField;
		SoXipMprIntersectionLine *node;
		int id;
		SbVec3f translateOrigin;
	};

	int mPickedLine;
	SbBool mPickedCenter;
	SbBool mPickedRotate;
	SbVec3f mPickPosition;
	SbVec3f mIntersectionPosition;
	SbVec3f mRotatePosition;
	std::vector<planeStruct> mMprPlaneList;
	
	SoFieldSensor *mModeFieldSensor;
	std::vector<SoFieldSensor *> mInputSensors;
	
	int32_t mMprLock;

	static float mPickRadius;

private:
	SbVec3f projectCenterOnPlane(const SbMatrix &intersectMatrix, const SbVec3f &center);
	void updateModeAndCursor();
	static void fieldSensorCBFunc(void *, SoSensor *);
};

#endif // SOXIPMPRINTERSECTIONMANIP_H


