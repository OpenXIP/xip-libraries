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
*/#ifndef SOXIPWINDOWLEVELELEMENT_H
#define SOXIPWINDOWLEVELELEMENT_H

#include <xip/inventor/core/xipivcore.h>
#include <Inventor/elements/SoReplacedElement.h>

class XIPIVCORE_API SoXipWindowLevelElement : public SoReplacedElement
{
	SO_ELEMENT_HEADER( SoXipWindowLevelElement );

public:
	static void initClass();

	// Initializes element
	virtual void init(SoState* state);

	// Sets the current window level 
	static void setWindow(SoState* state, SoNode *node,float window);
	static void setLevel(SoState* state, SoNode *node,float level);
	static float getWindow(SoState* state);
	static float getLevel(SoState* state);

protected:
	float	mWindow;
	float	mLevel;

private:
	virtual ~SoXipWindowLevelElement();
};

#endif // SOXIPWINDOWLEVELELEMENT_H
