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
#ifndef SOXIPIMAGETEXTCOLOR_H
#define SOXIPIMAGETEXTCOLOR_H

#include <xip/inventor/core/SoXipImageTextElement.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFColor.h>

class SoXipImageTextColor : public SoNode
{
	SO_NODE_HEADER( SoXipImageTextColor );

public:
	enum TextPosition
	{
		TP_UPPER_LEFT		= SoXipImageTextElement::TP_UPPER_LEFT,
		TP_UPPER_CENTER		= SoXipImageTextElement::TP_UPPER_CENTER,
		TP_UPPER_RIGHT		= SoXipImageTextElement::TP_UPPER_RIGHT,
		TP_CENTER_LEFT		= SoXipImageTextElement::TP_CENTER_LEFT,
		TP_CENTER_RIGHT		= SoXipImageTextElement::TP_CENTER_RIGHT,
		TP_LOWER_LEFT		= SoXipImageTextElement::TP_LOWER_LEFT,
		TP_LOWER_CENTER		= SoXipImageTextElement::TP_LOWER_CENTER,
		TP_LOWER_RIGHT		= SoXipImageTextElement::TP_LOWER_RIGHT,
	};

	SoXipImageTextColor();
	
	SoSFEnum		position;
	SoSFColor		color;

	static void initClass();

protected:
	~SoXipImageTextColor();

	virtual void GLRender( SoGLRenderAction* action );
};

#endif // SOXIPIMAGETEXTCOLOR_H
