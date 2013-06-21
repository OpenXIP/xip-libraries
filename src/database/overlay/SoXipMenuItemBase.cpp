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
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/sensors/SoFieldSensor.h>
# include "SoXipMenuItemBase.h"
# include "SoXipMenuBase.h"

SO_NODE_ABSTRACT_SOURCE( SoXipMenuItemBase );

SoXipMenuItemBase::SoXipMenuItemBase()
{
	SO_NODE_CONSTRUCTOR( SoXipMenuItemBase );

	SO_XIP_KIT_ADD_TYPE_ENTRY(     mSeparator, SoSeparator, this );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mSubMenuSwitch,    SoSwitch, mSeparator );

	SO_NODE_DEFINE_ENUM_VALUE( IconType, IC_NONE );
	SO_NODE_DEFINE_ENUM_VALUE( IconType, IC_COPY );
	SO_NODE_DEFINE_ENUM_VALUE( IconType, IC_CUT );
	SO_NODE_DEFINE_ENUM_VALUE( IconType, IC_PASTE );

	SO_NODE_SET_SF_ENUM_TYPE( icon, IconType );	

	SO_NODE_ADD_FIELD( focused, (FALSE) );
	SO_NODE_ADD_FIELD( enabled, (TRUE) );
	SO_NODE_ADD_FIELD( caption, ("") );
	SO_NODE_ADD_FIELD(    icon, (IC_NONE) );
	
	SoField* fields[] = { &focused, &enabled, &caption, &icon };
	
	int numFieldSensors = 4;
    for( int i = 0; i < numFieldSensors; ++ i )
    {
        mFieldSensors[i] = new SoFieldSensor( fieldSensorCB, this );
		mFieldSensors[i]->attach( fields[i] );        
    }
}

SoXipMenuItemBase::~SoXipMenuItemBase()
{
    for( int i = 0; i < 4; ++ i )
        delete mFieldSensors[i];
}

void
SoXipMenuItemBase::initClass()
{
	SO_NODE_INIT_ABSTRACT_CLASS( SoXipMenuItemBase, SoXipKit, "SoXipKit" );
}

void
SoXipMenuItemBase::fieldSensorCB( void* userData, SoSensor* sensor )
{
    SoXipMenuItemBase* item = (SoXipMenuItemBase *) userData;    
    SoFieldSensor* fieldSensor = (SoFieldSensor *) sensor;
    
    item->fieldChanged( fieldSensor->getAttachedField() );    
}

void
SoXipMenuItemBase::fieldChanged( SoField* whichField )
{
    if( whichField == &focused )
    {
		onFocus();       
    }
    else if( whichField == &enabled )
    {
		onEnable();
    }
	else if( whichField == &caption )
    {
		updateCaption();
    }
	else if( whichField == &icon )
    {
		updateIcon();
    }
}

void 
SoXipMenuItemBase::rayPick( SoRayPickAction* action )
{
	int numPickedPoints = action->getPickedPointList().getLength();

	SoXipKit::rayPick( action );

	if( focused.getValue() == FALSE && action->getPickedPointList().getLength() != numPickedPoints )
		focus( TRUE );
	else if( focused.getValue() == TRUE && action->getPickedPointList().getLength() == numPickedPoints )
		focus( FALSE );
}

SbBool
SoXipMenuItemBase::isFocused() const
{
	return focused.getValue();
}

SbBool
SoXipMenuItemBase::isEnabled() const
{
	return enabled.getValue();
}

void 
SoXipMenuItemBase::enable( SbBool state)
{
	enabled.setValue( state );
}

void 
SoXipMenuItemBase::focus( SbBool state )
{
	focused.setValue( state );
}
