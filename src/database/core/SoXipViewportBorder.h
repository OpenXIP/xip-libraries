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

#ifndef SOXIPVIEWPORTBORDER_H
#define SOXIPVIEWPORTBORDER_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFUShort.h>


class SoXipViewportBorder : public SoNode
{
SO_NODE_HEADER(SoXipViewportBorder);

public:
	SoSFColor	activeColor;
	SoSFFloat	activeLineWidth;
	SoSFUShort	activeLinePattern;

	SoSFColor	inactiveColor;
	SoSFFloat	inactiveLineWidth;
	SoSFUShort	inactiveLinePattern;

	/// Static method providing Open Inventor runtype type information.
	static void initClass();

	///	Default constructor
	SoXipViewportBorder();

protected:
	/// Default destructor
	virtual ~SoXipViewportBorder();

protected:
	virtual void GLRender(SoGLRenderAction * action);
};


#endif // SOXIPVIEWPORTBORDER_H
