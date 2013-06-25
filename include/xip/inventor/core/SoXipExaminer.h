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
#ifndef SOXIPEXAMINER_H
#define SOXIPEXAMINER_H

#include <xip/inventor/core/xipivcore.h>
#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFPlane.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/SbLinear.h>
#include <vector>


class SoFieldSensor;
class SoCamera;
class SbPlaneProjector;
class SbSphereSheetProjector;
class SoTimerSensor;


// utility class for grouping nodes of the intersection line geometry
class XIPIVCORE_API SoXipExaminer : public SoBaseKit 
{
	SO_KIT_HEADER(SoXipExaminer);

public:
	SoXipExaminer();
	static void initClass();

public:
	// Defines fields for the new parts in the catalog
	SO_KIT_CATALOG_ENTRY_HEADER(cameraSwitch);
	SO_KIT_CATALOG_ENTRY_HEADER(orthoCamera);
	SO_KIT_CATALOG_ENTRY_HEADER(perspectiveCamera);
	SO_KIT_CATALOG_ENTRY_HEADER(annotation);
	SO_KIT_CATALOG_ENTRY_HEADER(complexity);
	SO_KIT_CATALOG_ENTRY_HEADER(borderSwitch);
	SO_KIT_CATALOG_ENTRY_HEADER(borderNode);

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
		ROTATE_PLANE,
		TRANSLATE_PLANE,
		PAN
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
	SoSFEnum orientation;
	SoSFTrigger viewOrientation;
	SoSFBool perspective;
	SoSFTrigger viewAll;
	SoSFTrigger resetPlane;
	SoSFBool pointTo;
	SoSFBool border;
	SoSFColor borderColor;
	SoSFBool autoSpin;
	SoSFBool rotatePinpoint;

	// camera manipulation
	SoSFRotation rotateCamera;
	SoSFFloat scaleHeight;

	// outputs
	SoSFMatrix viewBoundingBox;
	SoSFPlane plane;

	virtual void rotateCam(const SbRotation &rot, SbBool enableAnimation = FALSE);
	virtual void scaleCam(float scale);

	virtual void panCam(const SbVec2f pos);
	virtual void spinCam(const SbVec2f pos);
	virtual	void spinNormCam(const SbVec2f pos);
	virtual void rotatePlane(const SbRotation &rot, const SbVec3f &center);
	virtual void translatePlane(const SbVec3f &tvec);
	virtual void setInteractive(SbBool on);

protected:
	virtual SoCamera *findCameraInScene(SoAction *action);

	virtual ~SoXipExaminer();
	virtual void inputChanged(SoField *which);
	virtual void timer(SoSensor *sensor);
	virtual SoCamera *getCamera();
	virtual void GLRender(SoGLRenderAction * action);
	virtual void handleEvent(SoHandleEventAction *action);
	virtual void getBoundingBox(SoGetBoundingBoxAction *action);
	virtual void updateCursor();

	// mouse/viewport handling
	virtual SbVec2f getMousePosNormalized(SoHandleEventAction *action);
	virtual void extractViewingParams(SoHandleEventAction *action);
	virtual void mouseRotatePlane(const SbVec2f &mousePos);
	virtual void mouseTranslatePlane(const SbVec2f &mousePos);
	virtual void scrollToCursor(SoHandleEventAction *action);

	std::vector<SoFieldSensor *> mInputSensors;
	SoTimerSensor *mTimerSensor;
	SbBool mViewAll;
	SbBool mResetPlane;
	SbPlaneProjector *mPlaneProj;
	SbSphereSheetProjector *mSphereSheetProj;
	SbViewVolume mViewVolume;
	SbViewportRegion mVpRegion;
	SbMatrix mViewTransform;

	SbBool mDragStartMouseBorder;
	SbVec3f mDragStartMouse;
	SbVec3f mDragStartMouseOnPlane;
	SbVec3f mDragStartCameraPos;
	SbRotation mAutoSpinRotation;
	SbRotation *mRotBuffer;
	int mRotFirstIndex;
	int mRotLastIndex;
	SbVec2f mRotLastNormPos;
	SbTime mLastHandleEventTime;
	SbVec2f mLastMousePos;
	SbVec2f mMouseDownPos;
	SbBool mIsFirstMouseDown;
	uint32_t mParentId;
	SoCamera *mSceneCamera;
	SbBool mShowPlaneRotationPoint;
	SbRotation mAnimRotationStart;
	SbRotation mAnimRotationStop;
	float mAnimSlerp;

	struct mprPlanes_s
	{
		SoSFMatrix *matrixField;
		SoSFVec3f  *centerField;
	};
	typedef std::vector<mprPlanes_s> mprPlanes_t;
	mprPlanes_t mMprPlaneList;
	uint32_t mSceneCameraId;

private:
	SoHandleEventAction *mHandleEventAction;
	static void fieldSensorCBFunc(void *usr, SoSensor *sensor);
	static void timerSensorCBFunc(void *usr, SoSensor *sensor);
};


#endif // SOXIPEXAMINER_H
