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
*	@file    SoXipOverlayDrawStyle.h
*	@brief   Declaration of the SoXipOverlayDrawStyle class
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYDRAWSTYLE_H
#define SOXIPOVERLAYDRAWSTYLE_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/fields/SoSFFloat.h>

/**
*	@class SoXipOverlayDrawStyle
*
* Set the color of one or more overlay object that have the specified labels
*
**/
class SoXipOverlayDrawStyle : public SoNode
{
	SO_NODE_HEADER( SoXipOverlayDrawStyle );

public:
	/// Constructor
	SoXipOverlayDrawStyle();

	/// color is applied to overlay with following label
	SoMFString		label;
	/// point size
	SoSFFloat		pointSize;
	/// lineWidth
	SoSFFloat		lineWidth;
	/// transparency
	SoSFUShort		linePattern;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipOverlayDrawStyle();	

	/// Rendering method
	virtual void GLRender( SoGLRenderAction* action );

};

#endif // SOXIPOVERLAYDRAWSTYLE_H
