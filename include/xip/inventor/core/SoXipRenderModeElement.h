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
*/#ifndef SORADRENDERMODEELEMENT_H
#define SORADRENDERMODEELEMENT_H

#include <xip/inventor/core/xipivcore.h>
#include <Inventor/elements/SoInt32Element.h>


class XIPIVCORE_API SoXipRenderModeElement : public SoInt32Element 
{
	SO_ELEMENT_HEADER(SoXipRenderModeElement);

public:
    enum RenderModes
	{
		MPR,
		MAXIP,
		MINIP,
		SSD,
		SSD_COLOR,
		VRT_COLOR,
		DRR,
		MPR_AND_GRAD_SEGMENT
	};

	// Initializes the SoRadRenderModeElement class
	static void initClass();

	// Initializes element
	virtual void init(SoState *state);

	// Sets the current temperature in the state to the given
	// temperature (in degrees Fahrenheit)
	static void set(SoState *state, SoNode *node, RenderModes mode);

	// Returns the current temperature from the state
	static RenderModes get(SoState *state);

	// Returns the default temperature
	static RenderModes getDefault() { return MPR; }

private:
	virtual ~SoXipRenderModeElement();
};

#endif // SORADRENDERMODEELEMENT_H

