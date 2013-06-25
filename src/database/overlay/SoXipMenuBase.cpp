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
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <xip/system/GL/gl.h>

#include "SoXipMenuBase.h"

SO_NODE_ABSTRACT_SOURCE( SoXipMenuBase );

SoXipMenuBase::SoXipMenuBase()
{
	SO_NODE_CONSTRUCTOR( SoXipMenuBase );

	SO_XIP_KIT_ADD_TYPE_ENTRY(    mMenuSwitch,      SoSwitch, this );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mMenuSeparator,   SoSeparator, mMenuSwitch );
	SO_XIP_KIT_ADD_TYPE_ENTRY(    mMenuOffset, SoTranslation, mMenuSeparator );
    
	SO_NODE_ADD_FIELD(           on, (FALSE) );
	SO_NODE_ADD_FIELD(     position, (0, 0) );
	SO_NODE_ADD_FIELD(  itemFocused, (-1) );
	SO_NODE_ADD_FIELD(  itemClicked, (-1) );

	mActionNode			= 0;
	mIsSubMenu			= FALSE;

	mFieldSensors[0]	= new SoFieldSensor( fieldSensorCB, this );
	mFieldSensors[0]->attach( &on );
	mFieldSensors[1]	= new SoFieldSensor( fieldSensorCB, this );
	mFieldSensors[1]->attach( &position );

	mPlaneProj			= new SbPlaneProjector;
	mPlaneProj->setPlane( SbPlane( SbVec3f(0, 0, 1), 0 ) );
}

SoXipMenuBase::~SoXipMenuBase()
{
    for( int i = 0; i < 2; ++ i )
        delete mFieldSensors[i];

	if( mPlaneProj )
		delete mPlaneProj;
	mPlaneProj = 0;
}

void
SoXipMenuBase::initClass()
{
	SO_NODE_INIT_ABSTRACT_CLASS( SoXipMenuBase, SoXipKit, "SoXipKit" );
}

void
SoXipMenuBase::fieldSensorCB( void* userData, SoSensor* sensor )
{
    SoXipMenuBase* menu = (SoXipMenuBase *) userData;    
    SoFieldSensor* fieldSensor = (SoFieldSensor *) sensor;
    
    menu->fieldChanged( fieldSensor->getAttachedField() );    
}

void
SoXipMenuBase::fieldChanged( SoField* whichField )
{
    if( whichField == &on )
    {
		mMenuSwitch->whichChild.setValue( on.getValue() ? 0 : -1 );        
    }
    else if( whichField == &position )
    {
		//mMenuOffset->translation.setValue( position.getValue() );
    }
}

SbBool
SoXipMenuBase::getPickedItem( SoHandleEventAction* action, int& pickedItem ) const
{
	SoRayPickAction pa( action->getViewportRegion() );
	pa.setPoint( action->getEvent()->getPosition() );
	pa.setRadius( 3 );
	pa.setPickAll( TRUE );
	pa.enableCulling( FALSE );
	pa.apply( mActionNode );

	for( int i = 0; i < size(); ++ i )
	{
		if( getItem(i)->isFocused() )
		{
			pickedItem = i;
			return TRUE;
		}
	}
	return FALSE;
}

void
SoXipMenuBase::GLRender( SoGLRenderAction* action )
{
	if( on.getValue() == FALSE )
		return ;

	// Compute the 3D position of the menu, given the mouse 2D position
	saveViewInformation( action );

	mMenuOffset->translation.setValue( mPlaneProj->project( position.getValue() ) );

	SoGetBoundingBoxAction bba( action->getViewportRegion() );
	bba.apply( mMenuSeparator );

	SbBox3f bbox = bba.getBoundingBox();
	bbox.transform( mModelMatrix );

	float viewportAR = mViewport.getViewportAspectRatio();
	SbVec3f screenOffset(0, 0, 0);
	if( viewportAR < 1. )
	{
		screenOffset[0] = bbox.getMax()[0] - 1.;
		screenOffset[1] = bbox.getMax()[1] - 1. / viewportAR;
	}
	else
	{
		screenOffset[0] = bbox.getMax()[0] - viewportAR;
		screenOffset[1] = bbox.getMax()[1] - 1;
	}

	if( screenOffset[0] < 0 )
		screenOffset[0] = 0;
	if( screenOffset[1] < 0 )
		screenOffset[1] = 0;

	SbVec3f worldOffset;
	mModelMatrix.inverse().multVecMatrix( screenOffset, worldOffset );

	mMenuOffset->translation.setValue( mMenuOffset->translation.getValue() - worldOffset );

	glPushAttrib( GL_ENABLE_BIT );
	glDisable( GL_DEPTH_TEST );

	SoXipKit::GLRender( action );

	glPopAttrib();
}

void
SoXipMenuBase::saveViewInformation( SoAction* action )
{
	SoState* state = action->getState();

	// Save the view volume element
	mViewVolume = SoViewVolumeElement::get( state );

	// Save the model matrix element
	mModelMatrix = SoModelMatrixElement::get( state );

	// Save the plane projector
	float distance = mViewVolume.getDepth() / 2.f;
	mPlaneProj->setViewVolume( mViewVolume );
	mPlaneProj->setWorkingSpace( mModelMatrix );
	mPlaneProj->setPlane( mViewVolume.getPlane( mViewVolume.getNearDist() + distance ) );

	// Save the viewport
	mViewport = SoViewportRegionElement::get( state );
}

void
SoXipMenuBase::handleEvent( SoHandleEventAction* action )
{
	if( on.getValue() == FALSE )
		return ;

	if( action->isHandled() || action->getGrabber() != this )
		return ;

   	const SoEvent* event = action->getEvent();
	if( !event )
		return ;

	int pickedItem;

	if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) && action->getGrabber() == this )
	{
		action->setHandled();
	}
	else if( SO_MOUSE_RELEASE_EVENT( action->getEvent(), BUTTON1 ) && action->getGrabber() == this )
	{
		if( getPickedItem( action, pickedItem ) && getItem( pickedItem )->isEnabled() )
		{
			itemClicked.setValue( pickedItem );
		}		

		on.setValue( FALSE );

		action->setHandled();
		action->releaseGrabber();
	}
	else if( event->isOfType( SoLocation2Event::getClassTypeId() ) )
	{
		mActionNode = action->getNodeAppliedTo();

		if( getPickedItem( action, pickedItem ) )
		{
			itemFocused.setValue( pickedItem );
			action->setHandled();
		}
	}	
}

int
SoXipMenuBase::size() const
{
    return mItems.getNum();    
}

void 
SoXipMenuBase::addItem( SoXipMenuItemBase* item )
{
    insertItem( size(), item );
	onMenuChange();
}

void 
SoXipMenuBase::insertItem( int position, SoXipMenuItemBase* item )
{
#ifdef _DEBUG
    if( position < 0 || position > size() )
    {
        SoDebugError::post( __FILE__, "Index out of bounds" );
        return ;
    }    
#endif
    
    mItems.set1Value( position, item );    
}

void 
SoXipMenuBase::removeItem( int position )
{
#ifdef _DEBUG
    if( position < 0 || position >= size() )
    {
        SoDebugError::post( __FILE__, "Index out of bounds" );
        return ;
    }    
#endif
    
    mItems.enableNotify( FALSE );
    mItems.setValues( position, size() - position - 1, mItems.getValues( position + 1 ) );
    mItems.enableNotify( TRUE );
    mItems.setNum( size() - 1 );    
}

void 
SoXipMenuBase::removeItem( SoXipMenuItemBase* item )
{
    removeItem( findItem( item ) );
}

int  
SoXipMenuBase::findItem( SoXipMenuItemBase* item )
{    
    for( int i = 0; i < size(); ++ i )
    {
        if( getItem(i) == item )
            return i;
    }
    return -1;
}

int  
SoXipMenuBase::findItem( const SbString& itemCaption )
{    
    for( int i = 0; i < size(); ++ i )
    {
        if( getItem(i)->caption.getValue() == itemCaption )
            return i;
    }
    return -1;
}

SoXipMenuItemBase* 
SoXipMenuBase::getItem( int position )
{
#ifdef _DEBUG
    if( position < 0 || position >= size() )
    {
        SoDebugError::post( __FILE__, "Index out of bounds" );
        return 0;
    }    
#endif
    
    return (SoXipMenuItemBase *) mItems[ position ];
}

const SoXipMenuItemBase* 
SoXipMenuBase::getItem( int position ) const
{
#ifdef _DEBUG
    if( position < 0 || position >= size() )
    {
        SoDebugError::post( __FILE__, "Index out of bounds" );
        return 0;
    }    
#endif
    
    return (SoXipMenuItemBase *) mItems[ position ];
}

void
SoXipMenuBase::enableItem( int position, SbBool state )
{
	getItem( position )->enable( state );
}

void
SoXipMenuBase::enableItem( const SbString& itemCaption, SbBool state )
{
	int position;
	if( ( position = findItem( itemCaption ) ) != -1 )
		enableItem( position, state );
}
