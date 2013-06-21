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
#ifndef SOXIPMPRLOCKELEMENT_H
#define SOXIPMPRLOCKELEMENT_H


#include <xip/inventor/core/xipivcore.h>
#include <Inventor/elements/SoInt32Element.h>


//Element that will store the index of the active slice
class XIPIVCORE_API SoXipMprLockElement : public SoInt32Element 
{
	SO_ELEMENT_HEADER(SoXipMprLockElement);

public:

	enum lockType
	{
		ORIENTATION = 1,
		POSITION = 2,
		SCALE = 4,
		LINE_ORIENTATION = 8,
		LINE_POSITION = 16
	};

	// Initializes the SoXipActiveMPRElement class
	static void    initClass();

	// Initializes element
	virtual void   init(SoState *state);

	// Sets the current active slice index 
	static void    set(SoState *state, SoNode *node, const int32_t lockMask);
	static int32_t get(SoState *state);
	static int32_t getDefault() { return 0; }
};


#endif // SOXIPMPRLOCKELEMENT_H
