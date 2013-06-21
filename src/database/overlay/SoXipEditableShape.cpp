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
#include <xip/inventor/core/SoXipCursor.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoPointSet.h>
#include <xip/inventor/overlay/SoXipEditableShape.h>
#include <xip/inventor/overlay/XipOverlayUtils.h>
#include "geomutils.h"

SO_NODE_ABSTRACT_SOURCE( SoXipEditableShape );


SoXipEditableShape::SoXipEditableShape()
{
	SO_NODE_CONSTRUCTOR( SoXipEditableShape );

	SO_XIP_KIT_ADD_ENTRY( mControlPointsSwitch, SoSwitch, mTopSeparator );
	SO_XIP_KIT_ADD_ENTRY( mControlPointsSeparator, SoSeparator, mControlPointsSwitch );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mControlPointsCoords, SoCoordinate3, mControlPointsSeparator );
	SO_XIP_KIT_ADD_ENTRY( mControlPointsStyle, SoDrawStyle, mControlPointsSeparator );
	SO_XIP_KIT_ADD_ENTRY( mControlPointsSet, SoPointSet, mControlPointsSeparator );

	SO_XIP_SHAPE_ADD_FIELD( point, (0, 0, 0) );
	point.setNum(0);
	SO_XIP_SHAPE_ADD_FIELD( closed, (FALSE) );

	SO_NODE_ADD_FIELD( closeOnDblClick,  (TRUE) );

	mControlPointsCoords->point.setNum(0);
	mControlPointsStyle->set( "pointSize 3" );

	mControlPointId				= -1;
}

SoXipEditableShape::~SoXipEditableShape()
{

}

void
SoXipEditableShape::initClass()
{
	SO_NODE_INIT_ABSTRACT_CLASS( SoXipEditableShape, SoXipManipulableShape, "SoXipManipulableShape" );
}

SbBool
SoXipEditableShape::isClosed() const
{
	return closed.getValue();
}

void
SoXipEditableShape::beforeCreation()
{
	SoXipManipulableShape::beforeCreation();
		
	point.setNum(0);
	closed.setValue( FALSE );
}

void
SoXipEditableShape::extractControlPoints( SoMFVec3f& points )
{
	points.setNum( point.getNum() );
	if (point.getNum() > 0)
		points.setValues( 0, point.getNum(), point.getValues(0) );
}

void 
SoXipEditableShape::transform( const SbMatrix& matrix )
{
	int numPoints = point.getNum();
	SbVec3f* pts = point.startEditing();
	for( int i = 0;i < numPoints; ++ i )
		matrix.multVecMatrix( pts[i], pts[i] );
	point.finishEditing();
}

int
SoXipEditableShape::pickControlPoint( SoHandleEventAction* action )
{	
	SbVec3f worldPt;
	if( getPoint( action, worldPt ) )
	{
		float maxDist = 2 * projectScreenOffsetToWorld( SbVec2s( 1, 1 ) ).length();

		// Get a const pointer to the shape points
		const SbVec3f* coordPtr = mControlPointsCoords->point.getValues(0);

		int numPoints = mControlPointsCoords->point.getNum();		
		for( int i = 0; i < numPoints; ++ i )
		{
			if( (coordPtr[i] - worldPt).length() < maxDist )
				return i;
		}
	}
	return -1;	
}

void
SoXipEditableShape::addPoint( SoNode* node, const SbVec2s& screenPt )
{
	int id;
	SbVec3f worldPt;
	if( getPoint( node, screenPt, worldPt ) && belongsToContour( worldPt, id ) )
	{
		// Add one point
		point.insertSpace( id + 1, 1 );
		point.set1Value( id + 1, worldPt );
	}
}

void
SoXipEditableShape::deletePoint( int id )
{
	point.setValues( id, point.getNum() - id - 1, point.getValues( id + 1 ) );	
	point.setNum( point.getNum() - 1 );	
}

void
SoXipEditableShape::handleEvent( SoHandleEventAction* action )
{
	if( !on.getValue() )
		return ;

	if( !isEditing() )
	{
		SoXipManipulableShape::handleEvent( action );		
		return ;
	}

	const SoEvent* event = action->getEvent();
	if( !event )
		return ;

	SbVec3f worldPt;
	if( SO_MOUSE_RELEASE_EVENT( action->getEvent(), BUTTON1 ) && action->getGrabber() )
	{
		action->releaseGrabber();
		action->setHandled();
	}
	else if( event->isOfType( SoLocation2Event::getClassTypeId() ) )
	{
		if( action->getGrabber() == this)
		{
			if( getPoint( action, worldPt ) )
				mouseMove( worldPt );
		}

		if( ! action->getGrabber() )
		{
			int cIndex = pickControlPoint( action );
			if( cIndex != -1 )
			{
				SoXipCursor::setCursor( "MOVEPOINT" );
				action->setHandled();
			}		
			else 
			{
				int id;				
				if( getPoint( action, worldPt ) && belongsToContour( worldPt, id ) )
				{
					SoXipCursor::setCursor( "ADDPOINT" );
					action->setHandled();
				}
			}
		}
	}
	else if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) )
	{
		if( getPoint( action, worldPt ) )
		{
			mControlPointId = -1;
			if( ( mControlPointId = pickControlPoint( action ) ) != -1 )
			{
				action->setHandled();
				action->setGrabber( this );

				mIsButtonPressed = true;
				mouseDown( worldPt );
			}
			else
			{
				int id;
				if( belongsToContour( worldPt, id ) )
				{
					// Add one point
					point.insertSpace( id + 1, 1 );
					point.set1Value( id + 1, worldPt );

					// Set this point as the one being modified
					mControlPointId = id + 1;

					action->setHandled();
					action->setGrabber( this );

					mIsButtonPressed = true;

					SoXipCursor::setCursor( "MOVEPOINT" );
				}
				else
				{
					action->releaseGrabber();
					status.setValue( NONE );
				}			
			}
		}
	}

	if( action->getGrabber() == this )
	{
		updateGeometries();
	}
}

void
SoXipEditableShape::updateGeometries()
{
	if (mControlPointsCoords && mControlPointsSet)
	{
		extractControlPoints( mControlPointsCoords->point );

		((SoPointSet *) mControlPointsSet)->numPoints.setValue( 
			mControlPointsCoords->point.getNum() );
	}
	
	SoXipManipulableShape::updateGeometries();
}

void 
SoXipEditableShape::extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed )
{
	// Read information from shape
	closed = this->closed.getValue();

	// Set the points
	point.copyFrom( this->point );

	// Set the coordinate indices
	XipOverlayUtils::fillCoordIndex( point, closed, coordIndex );
}

void
SoXipEditableShape::startEditing()
{
	toggleEnumerationOnOff( FALSE );
	toggleAnnotationOnOff( FALSE );

	((SoSwitch *) mControlPointsSwitch)->whichChild.setValue(0);
}

void
SoXipEditableShape::finishEditing()
{
	((SoSwitch *) mControlPointsSwitch)->whichChild.setValue(-1);

	toggleEnumerationOnOff( TRUE );
	toggleAnnotationOnOff( TRUE );
}

bool
SoXipEditableShape::belongsToContour( const SbVec3f& worldPt, int &id )
{
	if( !mLinesCoords )
		return false;

	float maxDist = 2 * projectScreenOffsetToWorld( SbVec2s( 1, 1 ) ).length();

	// Get a const pointer to the shape points
	const SbVec3f* coordPtr = mLinesCoords->point.getValues(0);
	
	int numPoints = mLinesCoords->point.getNum();	
	for( int i = 0; i < numPoints; ++ i )
	{
		const SbVec3f& origin = coordPtr[i];
		const SbVec3f& dest = coordPtr[ (i + 1) % numPoints];

		SbLine line( origin, dest );
	
		SbVec3f proj = line.getClosestPoint( worldPt );
		if( (proj - worldPt).length() > maxDist )
			continue ;

		float dist = (origin - dest).length();
		if( (proj - origin).length() > dist || (proj - dest).length() > dist )
			continue ;

		id = getPreviousControlPoint( i );
		return true;
	}
	return false;
}

int
SoXipEditableShape::getPreviousControlPoint( int id ) const
{
	return id;
}

void 
SoXipEditableShape::updateAnnotationPosition( SoSFVec3f& position )
{
	if( mIsViewInitialized && point.getNum() )
	{
		mAnnotation->justification.setValue( SoXipText2::RIGHT );
		mAnnotation->vAlignment.setValue( SoXipText2::TOP );
		
		SbXfBox3f bbox;
		computeXBoundingBox( bbox );

		SbVec3f bboxMin, bboxMax, refPt;
		bbox.getBounds( bboxMin, bboxMax );
		bbox.getTransform().multVecMatrix( bboxMin, refPt );

		int id = closestPoint( point, refPt );

		SbVec3f offset = projectScreenOffsetToWorld( SbVec2s( 5, 5 ) );
		offset[2] = 0;
		
		position.setValue( point[id] - offset );
	}
}

void 
SoXipEditableShape::updateEnumerationPosition( SoSFVec3f& position )
{
	if( mIsViewInitialized && point.getNum() )
	{
		mEnumerationText->justification.setValue( SoXipText2::LEFT );
		mEnumerationText->vAlignment.setValue( SoXipText2::BOTTOM );
		
		SbXfBox3f bbox;
		computeXBoundingBox( bbox );

		SbVec3f bboxMin, bboxMax, refPt;
		bbox.getBounds( bboxMin, bboxMax );
		bbox.getTransform().multVecMatrix( bboxMax, refPt );

		int id = closestPoint( point, refPt );

		SbVec3f offset = projectScreenOffsetToWorld( SbVec2s( 5, 5 ) );
		offset[2] = 0;
		
		position.setValue( point[id] + offset );
	}
}
