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
#ifndef SO_XIP_FRAME_RATE_H
#define SO_XIP_FRAME_RATE_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/system/GL/gl.h>
#include <xip/inventor/coregl/xipivcoregl.h>

class XIPIVCOREGL_API SoXipFrameRate : public SoNode {
	SO_NODE_HEADER(SoXipFrameRate);

public:
	SoXipFrameRate();

	void GLRender(SoGLRenderAction* action);
	
	static void initClass();

private:
	SoSFFloat frameRate;
	SoSFBool printOutput;
#ifdef WIN32
	LARGE_INTEGER last;
	LARGE_INTEGER freq;
#else // WIN32
	struct timeval  last;
	struct timezone tz;
#endif // WIN32
};

#endif // SO_FRAME_RATE_H




