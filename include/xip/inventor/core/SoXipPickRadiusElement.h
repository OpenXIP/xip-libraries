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
*/#ifndef SOXIPPICKRADIUSELEMENT_H
#define SOXIPPICKRADIUSELEMENT_H

#include <xip/inventor/core/xipivcore.h>
#include <Inventor/elements/SoFloatElement.h>
#include <Inventor/fields/SoSFInt32.h>


//Element that will store the index of the active slice
class XIPIVCORE_API SoXipPickRadiusElement : public SoFloatElement 
{
	SO_ELEMENT_HEADER(SoXipPickRadiusElement);

public:
	// Initializes the SoRadIndexElement class
	static void    initClass();

	// Initializes element
	virtual void   init(SoState *state);

	// Sets the current index
	static void    set(SoState *state, float index);

	// get the current index
	static float   get(SoState *state);


protected:
	virtual ~SoXipPickRadiusElement();

};


#endif // SOXIPPICKRADIUSELEMENT_H
