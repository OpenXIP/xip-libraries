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
*	@file    SoXipIcon.h
*	@brief   Icon class, to be used for 2D GUI purposes
*	@author  Julien Gein
**/

#ifndef SOXIPICON_H
#define SOXIPICON_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/sensors/SoFieldSensor.h>

/**
*	@class   SoXipIcon
*
*	Display a toolbar icon.
*  
**/
class SoXipIcon : public SoNode
{
	SO_NODE_HEADER( SoXipIcon );

public:
    /// Type of the icon
	enum IconType
	{
		IC_NONE,    //< No icon
		IC_COPY,    //< Copy
		IC_CUT,     //< Cut
		IC_PASTE    //< Paste
	};

    /// Constructor
	SoXipIcon();

    /// Type of the icon displayed
	SoSFEnum			icon;    
    /// Does the icon texture have a transparent color
	SoSFBool			isTransparent;
    /// Transparent color to be looked up for in the texture
	SoSFColor			transparentColor;

    /// Open Inventor class initialization
	static void initClass();

protected:
    /// Destructor
	~SoXipIcon();
    
    /// Internal texture used to render the icon
	class SoTexture2*	mTexture;

	virtual void callback( SoCallbackAction* action );
	virtual void GLRender( SoGLRenderAction* action );
         
    /// Force the update of the internal texture
	virtual void fieldChanged( SoField* whichField );

private:
    /// Callback triggered when the inputs have changed
	static void fieldSensorsCB( void* userData, SoSensor* sensor );

    /// Field sensors
	SoFieldSensor*		mFieldSensors[3];

};

#endif // SOXIPICON_H
