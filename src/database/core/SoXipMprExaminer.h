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

#ifndef SOXIPMPREXAMINER_H
#define SOXIPMPREXAMINER_H

#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFPlane.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/SbLinear.h>
#include <vector>


class SoCamera;
class SbSphereSheetProjector;
class SoTimerSensor;
class SoXipMprPlaneElement;


// utility class for grouping nodes of the intersection line geometry
class SoXipMprExaminer : public SoBaseKit 
{
	SO_KIT_HEADER(SoXipMprExaminer);

public:
	SoXipMprExaminer();
	static void initClass();

public:
	// Defines fields for the new parts in the catalog
	SO_KIT_CATALOG_ENTRY_HEADER(camera);
	SO_KIT_CATALOG_ENTRY_HEADER(annotation);
	SO_KIT_CATALOG_ENTRY_HEADER(complexity);
	SO_KIT_CATALOG_ENTRY_HEADER(interactionSwitch);
	SO_KIT_CATALOG_ENTRY_HEADER(intersectionManip);
	SO_KIT_CATALOG_ENTRY_HEADER(dogEarSwitch);
	SO_KIT_CATALOG_ENTRY_HEADER(dogEarNode);
	SO_KIT_CATALOG_ENTRY_HEADER(borderSwitch);
	SO_KIT_CATALOG_ENTRY_HEADER(borderNode);
	SO_KIT_CATALOG_ENTRY_HEADER(orientationSwitch);
	SO_KIT_CATALOG_ENTRY_HEADER(orientationNode);

	enum keyButtonType 
	{
		SHIFT_KEY = 1,
		CTRL_KEY = 2
	};

	enum mouseButtonType 
	{
		BUTTON1 = SoMouseButtonEvent::BUTTON1,
		BUTTON2 = SoMouseButtonEvent::BUTTON2,
		BUTTON3 = SoMouseButtonEvent::BUTTON3
	};

	enum modeType {
		NONE,
		ROTATE,
		PANZOOM,
		SHIFT,
		ROTATE_XY,
		PAN,
		ROTATE_NORMAL
	};

	enum intersectType {
		OFF,
		INTERSECTION,
		TRANSLATION,
		FREE
	};

	enum orientationType {
		FEET,
		HEAD,
		LEFT,
		RIGHT,
		ANTERIOR,
		POSTERIOR,
		RANGE_START,
		RANGE_END,
		AZIMUTH_START,
		AZIMUTH_END,
		ELEVATION_START,
		ELEVATION_END
	};

	SoSFBitMask	key;
	SoSFEnum mouse;
	SoSFEnum mode;
	SoSFEnum intersection;
	SoSFEnum orientation;
	SoSFTrigger viewOrientation;
        SoSFTrigger stepNext;
        SoSFTrigger stepPrevious;
//	SoSFTrigger viewCenter;
//	SoSFTrigger recenter
	SoSFTrigger viewAll;
        SoSFTrigger viewFirst;
        SoSFTrigger viewLast;

	SoSFBool rotatePinpoint;
	SoSFBool manip;
	SoSFBool pointTo;
	SoSFBool dogEar;
	SoSFBool border;
	SoSFBool orientationCube;
	SoSFRotation rotateCamera;
	SoSFFloat scaleHeight;
	SoSFBool   stubs;
	SoSFFloat  stubScale;
	SoSFMatrix plane;
	SoSFFloat accelerationFactor;


protected:
	virtual ~SoXipMprExaminer();
	virtual void inputChanged(SoField *which, SoSensor *sensor);
	virtual void timer(SoSensor *sensor);
	virtual void GLRender(SoGLRenderAction * action);
	virtual void handleEvent(SoHandleEventAction *action);
	virtual void updateCursor();
	virtual void updateElement(SoAction * action);
	virtual void updateCamera();
	virtual void callback(SoCallbackAction *action);
	virtual void pick(SoPickAction *action);
	virtual void getBoundingBox(SoGetBoundingBoxAction *action);
	virtual SbBool setUpConnections(SbBool onoff, SbBool doitalways = 0);
	virtual void updateDogEarSensors(SbBool onoff);
	virtual void scrollToCursor();
	virtual SbRotation getDefaultOrientation(int orien);

	virtual void zoomMprList(float scaleFactor);
	virtual void rotateCam(SbRotation rotation, SbVec3f center, SbBool ignoreLock = FALSE);
	virtual void panCam(SbVec3f translation);

	virtual void updateMprElement(SoAction *action);
    virtual void updateMprFirst(SoAction *action);
    virtual void updateMprLast(SoAction *action);

	// mouse/viewport handling
	virtual SbVec2f getMousePosNormalized(SoHandleEventAction *action);
	virtual void extractViewingParams(SoAction *action);

	std::vector<SoFieldSensor *> mInputSensors;
	SoFieldSensor *mDogEarNextSensor;
	SoFieldSensor *mDogEarPreviousSensor;
	SoFieldSensor *mOrientationCubeSensor;
	SoTimerSensor *mTimerSensor;
	SbBool mViewAll, mViewFirst, mViewLast;
	SbSphereSheetProjector *mSphereSheetProj;
	SbViewVolume mViewVolume;
	SbViewportRegion mVpRegion;
	SbMatrix mViewTransform;
	SbMatrix mMprModelMatrix, mLastMprModelMatrix;
	float mStepSize;
	float mThickness;				//MPR thickness
	SoSFMatrix *mMprMatrixField;
	SoSFVec3f *mMprCenterField;
	SbBox3f mBoundingBox;
	SbColor mBorderColor;

	SbBool mDragStartMouseBorder;
	SbVec2f mLastMousePos;
	SbVec2f mMouseDownPos;
	float mShift;
	int mShiftChange;
	int mMprId;

	struct mprPlanes_s
	{
		SoSFMatrix *matrixField;
		SoSFVec3f  *centerField;
	};
	typedef std::vector<mprPlanes_s> mprPlanes_t;
		
	mprPlanes_t mMprPlaneList;
	int32_t mMprLock;

private:
	SoHandleEventAction *mHandleEventAction;
	static void fieldSensorCBFunc(void *usr, SoSensor *sensor);
	static void timerSensorCBFunc(void *usr, SoSensor *sensor);
};


#endif // SOXIPMPREXAMINER_H
