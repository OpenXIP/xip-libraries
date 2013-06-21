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

#ifndef SO_WINDOW_SIZE_H
#define SO_WINDOW_SIZE_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/actions/SoGLRenderAction.h>

class SoXipWindowSize : public SoNode {
	SO_NODE_HEADER(SoXipWindowSize);

public:
	SoXipWindowSize();

	void GLRender(SoGLRenderAction* action);
	
	static void initClass();

	SoSFInt32 width;
	SoSFInt32 height;
	SoSFVec2f pixelScale;
};


#endif // SO_WINDOW_SIZE_H
