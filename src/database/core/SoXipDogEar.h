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

#ifndef SOXIPDOGEAR_H
#define SOXIPDOGEAR_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/SbViewportRegion.h>

class SoTimerSensor;
class SoSensor;

class SoXipDogEar : public SoNode
{
SO_NODE_HEADER(SoXipDogEar);

public:
	SoSFTrigger next;
	SoSFTrigger previous;

	/// Static method providing Open Inventor runtype type information.
	static void initClass();

	///	Default constructor
	SoXipDogEar();

protected:
	/// Default destructor
	virtual ~SoXipDogEar();
	virtual int getDogEarSize(const SbViewportRegion &viewportRegion);

protected:
	virtual void rayPick (SoRayPickAction *action);
	virtual void GLRender(SoGLRenderAction * action);
	virtual void handleEvent (SoHandleEventAction *action);
	virtual void timer(SoSensor *sensor);

	SoTimerSensor *mTimerSensor;
	SbBool mForwardDirection;
	SbVec2s mMouseDownPosition;

private:
	static void timerSensorCBFunc(void *usr, SoSensor *sensor);
};


#endif // SOXIPDOGEAR_H
