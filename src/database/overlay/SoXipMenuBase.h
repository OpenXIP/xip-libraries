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
#ifndef SOXIPMENUBASE_H
#define SOXIPMENUBASE_H

#include <xip/inventor/core/SoXipSubKit.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFShort.h>
#include "SoXipMenuItemBase.h"

class SoXipMenuBase : public SoXipKit
{
	SO_NODE_ABSTRACT_HEADER( SoXipMenuBase );

	SO_XIP_KIT_TYPE_ENTRY_HEADER(    mMenuSwitch, SoSwitch );	
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mMenuSeparator, SoSeparator );
	SO_XIP_KIT_TYPE_ENTRY_HEADER(    mMenuOffset, SoTranslation );

public:
	SoXipMenuBase();

	static void initClass();

	SoSFBool				on;
	SoSFVec2f				position;
	SoSFShort				itemFocused;
	SoSFShort				itemClicked; 

protected:
	~SoXipMenuBase();

	virtual SbBool getPickedItem( SoHandleEventAction* action, int& pickedItem ) const;
	virtual void handleEvent( SoHandleEventAction* action );
	virtual void GLRender( SoGLRenderAction* action );

	SoNode*					mActionNode;

	virtual void saveViewInformation( SoAction* action );

	class SbPlaneProjector*	mPlaneProj;
	SbViewVolume			mViewVolume;
	SbViewportRegion		mViewport;
	SbMatrix				mModelMatrix;

	virtual void onMenuChange() = 0;

private:
    static void fieldSensorCB( void* userData, SoSensor* sensor);

	void fieldChanged( SoField* whichField );

	SoFieldSensor*			mFieldSensors[2];


// Menu common methods
//
public:
	virtual int  size() const;
	virtual void addItem( SoXipMenuItemBase* item );
	virtual void insertItem( int position, SoXipMenuItemBase* item );
    virtual void removeItem( int position );
    virtual void removeItem( SoXipMenuItemBase* item );
    virtual int  findItem( SoXipMenuItemBase* item );
    virtual int  findItem( const SbString& itemCaption );
    virtual SoXipMenuItemBase* getItem( int position );
    virtual const SoXipMenuItemBase* getItem( int position ) const;
	virtual void enableItem( int position, SbBool state = TRUE );
	virtual void enableItem( const SbString& itemCaption, SbBool state = TRUE );

private:
    SoMFNode        mItems;

public:
	virtual SbBool isSubMenu() { return mIsSubMenu; }
	virtual void setIsSubMenu( SbBool flag ) { mIsSubMenu = flag; }
	SbBool mIsSubMenu;
    
};

#endif // SOXIPMENUBASE_H
