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

#ifndef SO_XIP_GET_CAMERA_PROPERTIES_H
#define SO_XIP_GET_CAMERA_PROPERTIES_H


#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/actions/SoGLRenderAction.h>

class SoXipGetCameraProperties : public SoNode
{
	SO_NODE_HEADER(SoXipGetCameraProperties);

public:

	SoXipGetCameraProperties();

	void GLRender(SoGLRenderAction* action);
	
	static void initClass();

	SoSFVec3f camPos;
	SoSFVec3f camDir;
	SoSFVec4f viewport;

private:

    SbVec3f mCamPos;
    SbVec3f mCamDir;
    SbVec4f mViewport;

};

#endif // SO_XIP_GET_CAMERA_PROPERTIES_H
