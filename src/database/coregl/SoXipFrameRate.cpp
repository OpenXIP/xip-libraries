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

#include <xip/system/standard.h>
#include <xip/inventor/coregl/SoXipFrameRate.h>

SO_NODE_SOURCE(SoXipFrameRate);

SoXipFrameRate::SoXipFrameRate()
{
    SO_NODE_CONSTRUCTOR(SoXipFrameRate);
    
	SO_NODE_ADD_FIELD(frameRate, (0));
	SO_NODE_ADD_FIELD(printOutput, (false));
    
#ifdef WIN32
	last.QuadPart = 0;
	QueryPerformanceFrequency(&freq);
#else
	//set the time value to zero
	last.tv_sec=0;
	last.tv_usec=0;
#endif // WIN32
}

void SoXipFrameRate::initClass() {
	SO_NODE_INIT_CLASS(SoXipFrameRate, SoNode, "SoNode");
}

void SoXipFrameRate::GLRender(SoGLRenderAction* action)
{
    glFinish();
    
#ifdef WIN32
	LARGE_INTEGER now;

	QueryPerformanceCounter(&now);

	float fps = (double)freq.QuadPart / (now.QuadPart - last.QuadPart);

	frameRate.setValue(fps);

	if (printOutput.getValue())
		SoDebugError::postInfo(__FUNCTION__, "FPS: %f", fps);
	last = now;
#else
	struct timeval now;

	gettimeofday(&now, &tz);
	
	//TODO: check if this is correct...
	float fps = 1.0f / (float( ((int64_t)now.tv_sec * (1000*1000) + (int64_t)now.tv_usec) -
                             ((int64_t)last.tv_sec * (1000*1000) + (int64_t)last.tv_usec)) / (1000.0f * 1000.0f));

	frameRate.setValue(fps);

	if (printOutput.getValue())
		SoDebugError::postInfo(__FUNCTION__, "FPS: %f", fps);

	last.tv_sec= now.tv_sec;
	last.tv_usec=now.tv_usec;
#endif
}


