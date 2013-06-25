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

#ifndef SOXIPWINDOWLEVELMANIP_H
#define SOXIPWINDOWLEVELMANIP_H

#include <Inventor/SbTime.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/events/SoMouseButtonEvent.h>


class SoXipWindowLevelManip : public SoNode
{
	SO_NODE_HEADER(SoXipWindowLevelManip);

public:
	SoXipWindowLevelManip();
	static void initClass();

	enum mouseButtonType {
		BUTTON1 = SoMouseButtonEvent::BUTTON1,
		BUTTON2 = SoMouseButtonEvent::BUTTON2,
		BUTTON3 = SoMouseButtonEvent::BUTTON3
	};

	SoSFEnum    mouse;
	SoSFFloat   window;
	SoSFFloat   level;
	SoSFBool    handleComplexity;
	SoSFTrigger autoWindowing;

protected:
	virtual ~SoXipWindowLevelManip();

	virtual void handleEvent(SoHandleEventAction *action);
	virtual void GLRender(SoGLRenderAction *action);

	float mComplexity;
	float		mDefaultWindow;
	float		mDefaultLevel;
	SbVec2s mLastMousePosition;
	SbTime mLastEventTime;
};



#endif // SOXIPWINDOWLEVELMANIP_H


