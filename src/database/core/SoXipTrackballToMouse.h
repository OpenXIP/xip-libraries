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

#ifndef SOXIPTRACKBALLTOMOUSE_H
#define SOXIPTRACKBALLTOMOUSE_H

#include <xip/system/standard.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFInt32.h>

class SoTimerSensor;
class SoSensor;


class SoXipTrackballToMouse : public SoGroup
{
	SO_NODE_HEADER(SoXipTrackballToMouse);

public:
	SoXipTrackballToMouse();
	static void initClass();

	SoSFBool on;
	SoSFBitMask buttonMask;

	enum mouseButtonType 
	{
		ANY = 7,
		BUTTON1 = 1,
		BUTTON2 = 2,
		BUTTON3 = 4
	};


protected:
	virtual ~SoXipTrackballToMouse();

	virtual void handleEvent(SoHandleEventAction *action);

	virtual void grab();
	virtual void release();

	static void timerSensorCBFunc(void *usr, SoSensor *sensor);

	SoNode *mGrabber;
	#ifdef WIN32
	HWND mCaptureWnd;
	#endif
	SoTimerSensor *mTimerSensor;
	int mShowCursor;
	int mMouseButtonDown;

	SoHandleEventAction *mHandleEventAction;
	SbViewVolume mViewVolume;
	SoNode *mPickRoot;
	SbBool mReleaseOnMousePressed;

	float mPickRadius;

};

#endif // SOXIPTRACKBALLTOMOUSE_H
