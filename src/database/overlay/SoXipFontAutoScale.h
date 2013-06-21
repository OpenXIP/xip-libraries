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
*	@file	SoXipFontAutoScale.h
*	@brief	Declaration of the SoXipFontAutoScale class
*	@author	Ravi Kumar
*	@author	Julien gein
**/

#ifndef SOXIPFONTAUTOSCALE_H
#define SOXIPFONTAUTOSCALE_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFBool.h>

/**
*   @class SoXipFontAutoScale
*
* Automatically sets up the font size that would fit with the
* viewport size and aspect ratio.
*
**/
class SoXipFontAutoScale : public SoNode  
{
	SO_NODE_HEADER(SoXipFontAutoScale);

public:
	/// Constructor
	SoXipFontAutoScale();

	// Tells whether the font size should be calculated from the original font size
	// or not (original font size is set with the SoFont node)
    SoSFBool        relative;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	virtual ~SoXipFontAutoScale();
	
	/// Rendering method
	virtual void GLRender( SoGLRenderAction* action );
};

#endif // SOXIPFONTAUTOSCALE_H
