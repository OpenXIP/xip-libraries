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

#ifndef SOXIPMPRALIGN_H
#define SOXIPMPRALIGN_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/sensors/SoFieldSensor.h>

class SoXipMprAlign : public SoNode
{
	SO_NODE_HEADER(SoXipMprAlign);

public:
	SoSFVec3f position;
	SoSFTrigger nearestVoxel;

	SoSFMatrix modelMatrix;
	SoSFShort width;
	SoSFShort height;
	SoSFShort depth;

	SoXipMprAlign();
	static void initClass();

protected:
	virtual ~SoXipMprAlign();

	virtual void GLRender(SoGLRenderAction *action);
	virtual void align(SoAction *action, SbVec3f pt, int which = -1);

	SbBool mUpdatePosition;
	SbBool mUpdateNearestVoxel;
	SoFieldSensor *mPositionSensor;
	SoFieldSensor *mNearestVoxelSensor;
	static void fieldSensorCBFunc( void* userData, SoSensor* );
};


#endif // SOXIPMPRALIGN_H
