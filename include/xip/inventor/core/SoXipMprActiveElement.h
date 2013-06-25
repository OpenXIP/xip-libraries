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
#ifndef SOXIPMPRACTIVELEMENT_H
#define SOXIPMPRACTIVELEMENT_H


#include <xip/inventor/core/xipivcore.h>
#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/fields/SoSFInt32.h>


//Element that will store the index of the active slice
class XIPIVCORE_API SoXipMprActiveElement : public SoReplacedElement 
{
	SO_ELEMENT_HEADER(SoXipMprActiveElement);

public:
	// Initializes the SoXipActiveMPRElement class
	static void    initClass();

	// Initializes element
	virtual void   init(SoState *state);

	// Sets the current active slice index 
	static void    set(SoState *state, SoNode *node,const int32_t index, SoSFInt32* indexField);

	virtual SoElement* copyMatchInfo() const;

	virtual SbBool matches(const SoElement *elt) const;

	static const int32_t  getMprIndex(SoState *state);

	static SoSFInt32*  getMprFieldIndex(SoState *state); 

protected:
	virtual ~SoXipMprActiveElement();

	int32_t mprId;
	SoSFInt32* mprIdField;
};


#endif // SOXIPMPRACTIVELEMENT_H
