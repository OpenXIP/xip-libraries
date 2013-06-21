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
#ifndef SOXIPMENUSTYLE_H
#define SOXIPMENUSTYLE_H

#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/nodes/SoSubNode.h>

class SoXipMenuStyle : public SoNode
{
	SO_NODE_HEADER( SoXipMenuStyle );

public:
	SoXipMenuStyle();

	SoMFUInt32	color;
	SoMFUInt32	focusedColor;
	SoMFUInt32	disabledColor;

	SoSFColor	textColor;
	SoSFColor	focusedTextColor;
	SoSFColor	disabledTextColor;

	static void initClass();

protected:
	~SoXipMenuStyle();

	virtual void GLRender( SoGLRenderAction* action );

};

#endif // SOXIPMENUSTYLE_H
