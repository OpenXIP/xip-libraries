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

#ifndef SOXIPVIEWPORTGROUP_H
#define SOXIPVIEWPORTGROUP_H

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFVec4f.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/SbLinear.h>


class SoFieldSensor;
class SoSensor;

class SoXipViewportGroup : public SoGroup 
{
	SO_NODE_HEADER(SoXipViewportGroup);

public:
	static void initClass();
	SoXipViewportGroup();
	SoXipViewportGroup( int numChildren );
	int pickViewportGroup(SoAction *action, SbVec2s point) const;

protected:
	virtual ~SoXipViewportGroup();

public:
	SoSFBool  on;
	SoSFBool  activateOnClick;
	SoSFBool  maximizeOnDoubleClick;
	SoSFBool  resizable;
	SoSFBool  relative;
	SoMFVec4f viewports;
	SoSFInt32 current;
	SoSFBool  maximized;
	SoSFBool  nested;

protected:


	enum viewportBorder_t
	{
		VIEWPORT_LEFT,
		VIEWPORT_RIGHT,
		VIEWPORT_TOP,
		VIEWPORT_BOTTOM
	};

	enum resizeMode_t
	{
		RESIZE_NONE = 0,
		RESIZE_HORIZONTAL = 1,
		RESIZE_VERTICAL = 2,
		RESIZE_ALL = 3
	};

	virtual void doAction(SoAction * action);
	virtual void getBoundingBox(SoGetBoundingBoxAction * action);
	virtual void GLRender(SoGLRenderAction * action);
	virtual void callback(SoCallbackAction * action);
	virtual void pick(SoPickAction * action);
	virtual void rayPick (SoRayPickAction *action);
	virtual void handleEvent (SoHandleEventAction *action);
	virtual void fieldSensorCB(SoSensor *sensor);

	virtual resizeMode_t resize(SbVec2s from, SbVec2s to, SbBool applyChange = TRUE);
	virtual SbBool isOnBorder(SbVec2s origin, SbVec2s size, viewportBorder_t which, SbVec2s pos, int epsilon) const;
	virtual SbBool isOverlapping(int num, const SbVec4f *v) const;
	virtual void updateCursor();

	SoFieldSensor *mFieldSensorRelative;
	SoFieldSensor *mFieldSensorNested;
	int mWindowWidth;
	int mWindowHeight;
	int mActiveViewport;
	int mPickViewport;
	SbTime mLastButtonDownTime;

	SbVec2s mResizeStart;
	SbVec2s mResizePos;
	resizeMode_t mResizeMode;
	SbBool mResizeValid;
	SoIndexedLineSet *mLineSet;

private:
	static void fieldSensorCBFunc(void *, SoSensor *);
};

#endif // SOXIPVIEWPORTGROUP_H
