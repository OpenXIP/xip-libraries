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
/**
*	@file   SbXipMarkerShapes.h
*	@brief  Declaration of the SbXipMarkerShapes class
*	@author Julien Gein
*	@author Thomas Moeller
*	@author Sylvain Jaume
**/

#ifndef SBXIPMARKERSHAPES_H
#define SBXIPMARKERSHAPES_H

#include <Inventor/SbString.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFInt32.h>
#include <xip/inventor/overlay/xipivoverlay.h>

// helper macros that add all available marker values to an enum type
#define SO_ENGINE_DEFINE_ENUM_MARKER_VALUES(enumType) \
	if (firstInstance) { \
		for (int i = 0; i < SbXipMarkerShapes::getNum(); i++) \
			inputData->addEnumValue(SO__QUOTE(enumType), SbXipMarkerShapes::getName(i), i); \
	}

#define SO_NODE_DEFINE_ENUM_MARKER_VALUES(enumType) \
	if (firstInstance) { \
		for (int i = 0; i < SbXipMarkerShapes::getNum(); i++) \
			fieldData->addEnumValue(SO__QUOTE(enumType), SbXipMarkerShapes::getName(i), i); \
	}

class XIPIVOVERLAY_API SbXipMarkerShapes
{
public:
	static int getNum();
	static void getVertices(int index, SoMFVec3f &vertices);
	static void getNumVertices(int index, SoMFInt32 &numVertices);
	static const char* getName(int index);

private:
	static const char * mShapes[][3];
};

#endif // SBXIPMARKERSHAPES_H

