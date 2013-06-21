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
#ifndef SOXIPANTIALIASING_H
#define SOXIPANTIALIASING_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor\actions\SoGLRenderAction.h>


// node to set the AntiAliasing Element
class SoXipAntiAliasing : public SoNode
{
	SO_NODE_HEADER(SoXipAntiAliasing);

public:

	SoSFBool active;

	SoXipAntiAliasing();
	static void initClass();

	virtual void GLRender(SoGLRenderAction *action);

protected:
	virtual ~SoXipAntiAliasing();

	SbBool					mActive;
	SoGLRenderAction::TransparencyType		mTransparencyType;
};


#endif // SOXIPANTIALIASING_H
