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
#ifndef SOXIPMENUITEMBASE_H
#define SOXIPMENUITEMBASE_H

#include <xip/inventor/core/SoXipSubKit.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFEnum.h>
#include "SoXipIcon.h"

class SoXipMenuItemBase : public SoXipKit
{
	SO_NODE_ABSTRACT_HEADER( SoXipMenuItemBase );

	SO_XIP_KIT_TYPE_ENTRY_HEADER(     mSeparator, SoSeparator);
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mSubMenuSwitch, SoSwitch );

public:
	enum IconType
	{
		IC_NONE		=	SoXipIcon::IC_NONE,
		IC_COPY		=	SoXipIcon::IC_COPY,
		IC_CUT		=	SoXipIcon::IC_CUT,
		IC_PASTE	=	SoXipIcon::IC_PASTE
	};

	SoXipMenuItemBase();

	SoSFBool			focused;
	SoSFBool			enabled;
	SoSFString			caption;
	SoSFEnum			icon;

	static void initClass();

	virtual SbBool isEnabled() const;
	virtual SbBool isFocused() const;

	virtual float getWidth() const = 0;
	virtual float getHeight() const = 0;

	virtual void enable( SbBool state = TRUE );
	virtual void focus( SbBool state = TRUE );
	virtual void updateCaption() {}
	virtual void updateIcon() {}

protected:
	~SoXipMenuItemBase();

	virtual void rayPick( SoRayPickAction* action );

	virtual void onFocus() {}
	virtual void onEnable()	{}

	virtual void fieldChanged( SoField* whichField );

private:
    static void fieldSensorCB( void* userData, SoSensor* sensor);
	SoFieldSensor*		mFieldSensors[4];

};

#endif // SOXIPMENUITEMBASE_H
