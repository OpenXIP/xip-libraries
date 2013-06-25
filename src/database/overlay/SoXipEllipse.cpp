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
#include <Inventor/events/SoEvent.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/fields/SoMFInt32.h>
#include <xip/inventor/overlay/SoXipEllipse.h>
#include <xip/inventor/overlay/SoXipText2.h>
#include <xip/inventor/overlay/XipOverlayUtils.h>

SO_NODE_SOURCE( SoXipEllipse );

SoXipEllipse::SoXipEllipse()
{
	SO_NODE_CONSTRUCTOR( SoXipEllipse );

	SO_XIP_SHAPE_ADD_FIELD( center, (0, 0, 0) );
	SO_XIP_SHAPE_ADD_FIELD( a, (0, 0, 0) );
	SO_XIP_SHAPE_ADD_FIELD( b, (0, 0, 0) );
	SO_XIP_SHAPE_ADD_FIELD( precision, (8) );

	mHasFirstPoint = false;
}

SoXipEllipse::~SoXipEllipse()
{

}

void
SoXipEllipse::initClass()
{
	SO_NODE_INIT_CLASS( SoXipEllipse, SoXipManipulableShape, "SoXipManipulableShape" );
}

SbBool
SoXipEllipse::isClosed() const
{
	return TRUE;
}

void
SoXipEllipse::beforeCreation()
{
	SoXipManipulableShape::beforeCreation();

	mHasFirstPoint = false;

	center.setValue( 0, 0, 0 );
	a.setValue( 0, 0, 0 );
	b.setValue( 0, 0, 0 );
}

void
SoXipEllipse::translate( const SbVec3f& offset )
{
	mFirstPoint += offset;
	center = center.getValue() + offset;
}

void
SoXipEllipse::mouseUp( const SbVec3f& newPos )
{
	if( (newPos - mFirstPoint).length() > 5 * projectScreenOffsetToWorld( SbVec2s(1, 1) ).length() )
	{
		status.setValue( NONE );
	}
}

void
SoXipEllipse::mouseMove( const SbVec3f& newPos )
{
	SbVec3f u = projectScreenOffsetToWorld( SbVec2s(1, 0) );
	SbVec3f v = projectScreenOffsetToWorld( SbVec2s(0, 1) );
	
	SbVec3f pos[2];
	pos[0] = SbLine( newPos, newPos + u ).getClosestPoint( mFirstPoint );
	pos[1] = SbLine( newPos, newPos + v ).getClosestPoint( mFirstPoint );

	SbVec3f aTmp = ( newPos - pos[1] ) / 2.f;
	SbVec3f bTmp = ( newPos - pos[0] ) / 2.f;

	// If shift is down, make the ellipse a circle: use the smallest radius
	// in both directions
	if( mHandleEventAction->getEvent()->wasShiftDown() )
	{
		float hRadius = bTmp.length();
		float vRadius = aTmp.length();

		if( hRadius < vRadius )
			aTmp *= ( hRadius / vRadius );
		else
			bTmp *= ( vRadius / hRadius );
	}

	// If Ctrl is down, center the ellipse on first point
	if( mHandleEventAction->getEvent()->wasCtrlDown() )
	{
		a		= 2 * aTmp;
		b		= 2 * bTmp;
		center	= mFirstPoint;
	}
	else
	{
		a		= aTmp;
		b		= bTmp;
		center	= mFirstPoint + aTmp + bTmp;
	}
}

void
SoXipEllipse::mouseDown( const SbVec3f& newPos )
{
	if( mHasFirstPoint )
	{
		status.setValue( NONE );
		return ;		
	}

	mFirstPoint = newPos;
	mHasFirstPoint = true;
}

void 
SoXipEllipse::extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed )
{
	// Set the points
	int numPoints = 4 * precision.getValue();
	point.setNum( numPoints );	

	SbVec3f* pointPtr = point.startEditing();
	{
		// Ellipse center, horizontal and vertical radiuses
		const SbVec3f& c = center.getValue();
		const SbVec3f& hRadius = a.getValue();
		const SbVec3f& vRadius = b.getValue();

		float angle;
		float angleIncrement = 0.5f * M_PI / (float) precision.getValue();

		for( int i = 0; i < numPoints; ++ i )
		{
			angle = i * angleIncrement;
			pointPtr[i] = c + hRadius * cos( angle ) + vRadius * sin( angle );
		}
	}	
	point.finishEditing();

	// Set the coordinate indices
	XipOverlayUtils::fillCoordIndex( point, TRUE, coordIndex );

	// Ellipses are always closed
	closed = TRUE;
}

void 
SoXipEllipse::transform( const SbMatrix& matrix )
{
	SbVec3f scale;
	SbVec3f translate;
	SbRotation rot;
	SbRotation rottemp;
	matrix.getTransform( translate, rot, scale, rottemp );

	SbVec3f newA;	
	matrix.multVecMatrix( a.getValue(), newA );
	a.setValue( newA - translate );

	SbVec3f newB;
	matrix.multVecMatrix( b.getValue(), newB );
	b.setValue( newB - translate );
	
	SbVec3f	newCenter;
	matrix.multVecMatrix( center.getValue(), newCenter );
	center.setValue( newCenter );
}
