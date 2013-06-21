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
#include <xip/inventor/core/SoXipActiveViewportElement.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/events/SoEvent.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <xip/inventor/overlay/SoXipShape.h>

SO_NODE_ABSTRACT_SOURCE( SoXipShape );

SoXipShape::SoXipShape()
{
	SO_NODE_CONSTRUCTOR( SoXipShape );

	SO_NODE_DEFINE_ENUM_VALUE( StatusType, NONE );
	SO_NODE_DEFINE_ENUM_VALUE( StatusType, CREATE );
	SO_NODE_DEFINE_ENUM_VALUE( StatusType, EDIT );
	SO_NODE_DEFINE_ENUM_VALUE( StatusType, CLEAR );


	SO_NODE_SET_SF_ENUM_TYPE( status, StatusType );	

	SO_NODE_ADD_FIELD(           on, (TRUE) );
	SO_NODE_ADD_FIELD(       status, (CREATE) );
	SO_NODE_ADD_FIELD(        order, (-1) );
	SO_NODE_ADD_FIELD(         rank, (-1) );
	SO_NODE_ADD_FIELD(        label, ("") );
	SO_NODE_ADD_FIELD(      caption, ("") );

	SoField* fields[5] = { &on, &status, &label, &rank, &caption };
	for( int i = 0; i < 5; ++ i )
	{
		mFieldSensors[i] = new SoFieldSensor( fieldSensorCallback, this );
		mFieldSensors[i]->attach( fields[i] );
	}

	mPlaneProj		= new SbPlaneProjector(FALSE);
	mPlaneProj->setPlane( SbPlane( SbVec3f(0, 0, 1), 0 ) );

	mIsSelected		= FALSE;
}

SoXipShape::~SoXipShape()
{
	if( mPlaneProj )
	{
		delete mPlaneProj;
		mPlaneProj = 0;
	}

	for( int i = 0; i < 5; ++ i )
	{
		if( mFieldSensors[i] )
		{
			delete mFieldSensors[i];
			mFieldSensors[i] = 0;
		}
	}
}

void
SoXipShape::initClass()
{
	SO_NODE_INIT_ABSTRACT_CLASS( SoXipShape, SoXipKit, "SoXipKit" );
}

void 
SoXipShape::setLabel( const SoMFString& label )
{
	this->label.copyFrom( label );
}

void 
SoXipShape::setRank( int rank )
{
	this->rank.setValue( rank );
}

void 
SoXipShape::setCaption( const SbString& caption )
{
	this->caption.setValue( caption );
}

SbBool
SoXipShape::isEditing() const
{
	return status.getValue() == EDIT;
}

SbBool
SoXipShape::isCreating() const
{
	return status.getValue() == CREATE;
}

SbBool 
SoXipShape::isSelected() const
{
	return mIsSelected;
}

SbBool
SoXipShape::isDeleted() const
{
	return status.getValue() == CLEAR;
}
	
void 
SoXipShape::select( SbBool state )
{
	mIsSelected = state;

	// Because the selection state is not a field, the node won't be flagged as
	// modified, so we need to call startNotify() to force a re-rendering of the
	// scene
	startNotify();
}

void
SoXipShape::fieldSensorCallback( void* userData, SoSensor* sensor )
{
	SoField* whichField = ((SoFieldSensor *) sensor)->getAttachedField();

	SoXipShape* self = (SoXipShape *) userData;

	if( whichField == &self->status )
	{
		switch( self->status.getValue() )
		{
		case EDIT:
			self->select( FALSE );
			self->startEditing();
			break ;

		case CREATE:
			self->beforeCreation();
			self->finishEditing();
			break ;

		case NONE:
			self->afterCreation();
			self->finishEditing();
			break ;

		case CLEAR:
			self->beforeCreation();
			self->select(FALSE);
			break;
		}
	}
	else if( whichField == &self->on )
	{
		// Unselect the shape if necessary
		if( self->on.getValue() == FALSE && self->isSelected() )
			self->select( FALSE );
	}

	// Dirty fix to force re-rendering when setting the label, caption, rank from the outside
	// (required for SoXipOverlayProperties). Needs clean-up!
	else if( whichField == &self->label || whichField == &self->caption  || whichField == &self->rank )
	{
		self->startNotify();
	}
}

void
SoXipShape::saveViewInformation( SoAction* action )
{
	SoState* state = action->getState();
	if( !state )
		return ;

	SbBool canSave = FALSE;
	if( action->isOfType( SoGLRenderAction::getClassTypeId() ) )
	{
		// FIXME: see if we need to test for active viewport!!
		if( SoXipActiveViewportElement::get(state) && status.getValue()==NONE)
			canSave = TRUE;
	}

	if( action->isOfType( SoHandleEventAction::getClassTypeId() ) )
	{
		// make sure no grabber is active
		if( !((SoHandleEventAction*) action)->getGrabber() )
			canSave = TRUE;
	}

	if( canSave )
	{
		mOverlaySettings = SoXipOverlayElement::get( state );

		// Save the view volume element
		mViewVolume = SoViewVolumeElement::get( state );

		// Save the viewport
		mViewport = SoViewportRegionElement::get( state );

		// NEAR_PLANE : move slighty inwards of nearplane to ensure proper drawing
		float distance = 0.001;
		if( mOverlaySettings.getLocation() == SoXipOverlayElement::FOCAL_PLANE )
			distance = mViewVolume.getDepth() / 2.f;

		mPlaneProj->setViewVolume( mViewVolume );
		mPlaneProj->setPlane( mViewVolume.getPlane( mViewVolume.getNearDist() + distance ) );
	}
}

const SbVec2f
SoXipShape::getNormalizedPosition( const SbVec2s& screenPt ) const
{
    const SbVec2s& pixSize = mViewport.getViewportSizePixels();
	const SbVec2s& origin = mViewport.getViewportOriginPixels();
    SbVec2s pos = screenPt - origin;

	SbVec2f normalizedScreenPt;
	if ( pixSize[0] == 0 )
		normalizedScreenPt[0] = 0.;
    else
		normalizedScreenPt[0] = (float) pos[0] / (float) pixSize[0];

	if ( pixSize[1] == 0 )
		normalizedScreenPt[1] = 0.;
    else
		normalizedScreenPt[1] = (float) pos[1] / (float) pixSize[1];

    return normalizedScreenPt;
}

SbBool
SoXipShape::getPoint( SoNode* node, const SbVec2s& screenPt, SbVec3f& worldPt )
{
	if( mOverlaySettings.getLocation() == SoXipOverlayElement::FOCAL_PLANE ||
		mOverlaySettings.getLocation() == SoXipOverlayElement::NEAR_PLANE )
	{
		worldPt = mPlaneProj->project( getNormalizedPosition( screenPt ) );
		return TRUE;
	}
	else if( mOverlaySettings.getLocation() == SoXipOverlayElement::PICKING )
	{
		SoRayPickAction pa( mViewport );
		pa.setPoint( screenPt );
		pa.setRadius( 1 );
		pa.enableCulling( FALSE );
		pa.apply( node );

		if( pa.getPickedPoint() )
		{
			worldPt = pa.getPickedPoint()->getPoint();
			return TRUE;
		}
	}
	else
	{
		SoError::post( "SoXipOverlayElement: Unknown location" );
	}

	return FALSE;
}

SbBool
SoXipShape::getPoint( SoHandleEventAction* action, SbVec3f& point )
{
	const SoEvent* event = action->getEvent();
	if( !event )
		return FALSE;
	
	return getPoint( action->getNodeAppliedTo(), 
		action->getEvent()->getPosition(), point );	
}

void
SoXipShape::handleEvent( SoHandleEventAction* action )
{
	if( !on.getValue() )
		return ;

	SoXipKit::handleEvent( action );

	// Once you set the grabber, the scene is not going to be traversed
	// for the next events. Need to save any view information prior.
	//	
	if( !action->getGrabber() )
		saveViewInformation( action );
}

SbVec3f
SoXipShape::projectScreenOffsetToWorld( const SbVec2s& pixelOffset ) const
{
	SbVec2f normOffset = SbVec2f(
		pixelOffset[0] / (float) mViewport.getViewportSizePixels()[0],
		pixelOffset[1] / (float) mViewport.getViewportSizePixels()[1] );

	return mPlaneProj->project( normOffset ) - mPlaneProj->project( SbVec2f( 0, 0 ) );
}


