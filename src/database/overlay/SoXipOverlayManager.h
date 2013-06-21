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
*  @file    SoXipOverlayManager.h
*  @brief   Node responsible for handling of multiple overlays
*  @author  Julien Gein
**/

#ifndef SOXIPOVERLAYMANAGER_H
#define SOXIPOVERLAYMANAGER_H

#include <xip/inventor/core/SoXipKit.h>
#include <Inventor/SoLists.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSFNode.h>
#include <xip/inventor/overlay/SoXipShape.h>

/**
*  @class SoXipOverlayManager
*
*  This node is used to handle multiple overlay objects, of different type.
*
**/
class SoXipOverlayManager : public SoXipKit
{
	SO_NODE_HEADER( SoXipOverlayManager );

	SO_XIP_KIT_ENTRY_HEADER( mTopSeparator );
	SO_XIP_KIT_ENTRY_HEADER( mGeomSeparator );

	SO_XIP_KIT_TYPE_ENTRY_HEADER( mShapeSwitch, SoSwitch );
	SO_XIP_KIT_ENTRY_HEADER( mShapeList );
	
	SO_XIP_KIT_ENTRY_HEADER( mMenuSwitch );
	SO_XIP_KIT_ENTRY_HEADER( mMenuSeparator );
	SO_XIP_KIT_ENTRY_HEADER( mMenuFont );
	SO_XIP_KIT_ENTRY_HEADER( mMenuNoShadows );
	SO_XIP_KIT_ENTRY_HEADER( mMenuStyle );
	SO_XIP_KIT_ENTRY_HEADER( mMenuCamera );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mMenu, SoXipMenu );

public:
    /// Constructor
	SoXipOverlayManager();

    /// Should a context menu be used
	SoSFBool			menuEnabled;
    /// Is the manager in creation mode
	SoSFBool			create;
    /// Class name of the next shape to be created
	SoSFString			shapeClassName;
    /// Label of the next shape to be created
	SoMFString			shapeLabel;
    /// Caption of the next shape to be created
	SoSFString			shapeCaption;
    /// Single or multiple shapes
	SoSFBool			multipleShapes;
	///
	SoMFNode			overlays;
	///
	SoSFTrigger			add;
	///
	SoSFTrigger			remove;
	///
	SoSFTrigger			clear;

	SoSFNode			node;

    /// Class initialization
	static void initClass();

    /// Create a new shape given shapeClassName, shapeLabel and shapeCaption
	SoXipShape*  createNewShape();

    /// Internal.
    /// Get a pointer to the internal list of shape.
	virtual class SoXipShapeList* getCurrentList();	

protected:
    /// Destructor
	~SoXipOverlayManager();

	/// Compute the next rank available. Each overlay is enumerated starting from 1.
	/// Return the smallest available index.
	virtual int getNextRank();

    /// Create the context menu
	virtual void initContextMenu();

    /// Set up the sensors on internal nodes 
    virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );	

    /// Event manager
	virtual void handleEvent( SoHandleEventAction* action );	

	/// Returns the picked shape, null if none were picked
	SoXipShape* isShapePicked( SoHandleEventAction* action );

    /// Current overlay selection
	SoNodeList			mSelection;
	int					mPickedControlPoint;
	SbVec2s				mMousePosition;
	SoNode*				mActionNode;

	/// Call when a menu item is clicked
	virtual void onMenuItemClick();
	/// Call when the menu is enabled
	virtual void onMenuEnable();

	/// Call from the menu or when the user press CTRL+C
	virtual void onCopy();
	/// Call from the menu or when the user press CTRL+V
	virtual void onPaste();
	/// Call from the menu or when the user press CTRL+X
	virtual bool onDelete();

	virtual void addOverlays();
	virtual void removeOverlays();
	virtual void clearOverlays();

private:	
	static void menuClickSensorCB( void* userData, SoSensor* );
	static void menuEnabledSensorCB( void* userData, SoSensor* );
	static void fieldSensorCB( void* userData, SoSensor* );

	SoFieldSensor*		mMenuClickSensor;
	SoFieldSensor*		mMenuEnabledSensor;
	SoFieldSensor*		mFieldSensors[3];	

};

#endif // SOXIPOVERLAYMANAGER_H

