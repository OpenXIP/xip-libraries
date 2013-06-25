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

#ifndef SOXIPORIENTATIONCUBE_H
#define SOXIPORIENTATIONCUBE_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFEnum.h>


class SoXipOrientationCube : public SoNode
{
SO_NODE_HEADER(SoXipOrientationCube);

public:

	enum orientationType 
	{
		FEET,
		HEAD,
		LEFT,
		RIGHT,
		ANTERIOR,
		POSTERIOR
	};

	SoSFFloat size;
	SoSFVec2f position;

	SoSFEnum orientation;

	/// Static method providing Open Inventor runtype type information.
	static void initClass();

	///	Default constructor
	SoXipOrientationCube();

protected:
	/// Default destructor
	virtual ~SoXipOrientationCube();

protected:
	virtual void GLRender(SoGLRenderAction * action);
	virtual void handleEvent(SoHandleEventAction *action);

	virtual orientationType getPickedSide(SoHandleEventAction *action);

private:
	SbVec2f getTranslation(float aspectRatio) const;
	SbVec3f getScale(float aspectRatio) const;
	SbRotation getRotation(SoAction *action) const;
};


#endif // SOXIPORIENTATIONCUBE_H


