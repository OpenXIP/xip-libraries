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
*	@file    SoXipOverlaySettings.h
*	@brief   Declaration of the SoXipOverlaySettings class
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYSETTINGS_H
#define SOXIPOVERLAYSETTINGS_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>
#include <xip/inventor/overlay/SoXipOverlayElement.h>

/**
*	@class SoXipOverlaySettings
*
* Sets some properties for all the overlay
*
**/
class SoXipOverlaySettings : public SoNode
{
	SO_NODE_HEADER( SoXipOverlaySettings );

public:	
	/// Location: where to get the points from ?
	enum LocationType
	{
		PICKING			= SoXipOverlayElement::PICKING,			//< through a pick action
		FOCAL_PLANE		= SoXipOverlayElement::FOCAL_PLANE,		//< on the focal plane
        NEAR_PLANE      = SoXipOverlayElement::NEAR_PLANE		//< on the near plane
	};

	/// Constructor
	SoXipOverlaySettings();

	/// Location
	SoSFEnum		location;
	/// Should the annotation be displayed ? 
	SoSFBool		showAnnotation;
	/// Should the enumeration be displayed ? 
	SoSFBool		showEnumeration;
	
	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipOverlaySettings();

	virtual void doAction( SoAction* action );
	virtual void GLRender( SoGLRenderAction* action );
	virtual void handleEvent( SoHandleEventAction* action );

};

#endif // SOXIPOVERLAYSETTINGS_H
