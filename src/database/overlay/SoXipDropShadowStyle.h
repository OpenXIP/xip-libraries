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
*  \file SoXipDropShadowStyle.h
*  \brief Declaration of the SoXipDropShadowStyle node
*  \author Julien Gein
*
**/

#ifndef SOXIPDROPSHADOWSTYLE_H
#define SOXIPDROPSHADOWSTYLE_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFVec2s.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFFloat.h>

/**
*  @class SoXipDropShadowStyle
*
*  This node allows the user to set the properties of drop shadows that
*  affect 2D annotations (text, ROIs, etc.)
*  Those properties are propagated in the scene via a SoXipDropShadowElement
*
*  @see SoXipDropShadowElement
*
**/
class SoXipDropShadowStyle : public SoNode
{
	SO_NODE_HEADER( SoXipDropShadowStyle );

public:
    /// Constructor
	SoXipDropShadowStyle();

    /// Enable/disable drop shadows
	SoSFBool	    on;
    /// Drop shadows offset in screen coordinates
	SoSFVec2s	    pixelOffset;
    /// Drop shadows color
	SoSFColor	    color;
    /// Drop shadows transparency
	SoSFFloat	    transparency;

    /// Class initialization
	static void initClass();

protected:
    /// Destructor
	~SoXipDropShadowStyle();

	virtual void GLRender( SoGLRenderAction* action );

};

#endif // SOXIPDROPSHADOWSTYLE_H
