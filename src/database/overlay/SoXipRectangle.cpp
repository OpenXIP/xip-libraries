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
#include <Inventor/projectors/SbPlaneProjector.h>
#include "SoXipRectangle.h"
#include  <xip/inventor/overlay/XipOverlayUtils.h>

SO_NODE_SOURCE( SoXipRectangle );

SoXipRectangle::SoXipRectangle()
{
	SO_NODE_CONSTRUCTOR( SoXipRectangle );

	SO_XIP_SHAPE_ADD_FIELD( p0, (0, 0, 0) );
	SO_XIP_SHAPE_ADD_FIELD( p1, (0, 0, 0) );
	SO_XIP_SHAPE_ADD_FIELD( p2, (0, 0, 0) );
	SO_XIP_SHAPE_ADD_FIELD( p3, (0, 0, 0) );

	mHasFirstPoint = false;
}

SoXipRectangle::~SoXipRectangle()
{

}

void
SoXipRectangle::initClass()
{
	SO_NODE_INIT_CLASS( SoXipRectangle, SoXipManipulableShape, "SoXipManipulableShape" );
}

SbBool
SoXipRectangle::isClosed() const
{
	return TRUE;
}

void
SoXipRectangle::beforeCreation()
{
	SoXipManipulableShape::beforeCreation();

	mHasFirstPoint = false;

	p0.setValue( 0, 0, 0 );
	p1.setValue( 0, 0, 0 );
	p2.setValue( 0, 0, 0 );
	p3.setValue( 0, 0, 0 );
}

void
SoXipRectangle::translate( const SbVec3f& offset )
{
	mFirstPoint += offset;
	p0 = p0.getValue() + offset;
	p1 = p1.getValue() + offset;
	p2 = p2.getValue() + offset;
	p3 = p3.getValue() + offset;
}

void
SoXipRectangle::mouseUp( const SbVec3f& newPos )
{	
	if( (newPos - p0.getValue()).length() > 5 * projectScreenOffsetToWorld( SbVec2s(1, 1) ).length() )
	{
		status.setValue( NONE );
	}
}

void
SoXipRectangle::mouseMove( const SbVec3f& newPos )
{
	SbVec3f u = projectScreenOffsetToWorld( SbVec2s(1, 0) );
	SbVec3f v = projectScreenOffsetToWorld( SbVec2s(0, 1) );
	
	SbVec3f widthVec = newPos - SbLine( newPos, newPos + u ).getClosestPoint( mFirstPoint );
	SbVec3f heightVec = newPos - SbLine( newPos, newPos + v ).getClosestPoint( mFirstPoint );

	// If shift is down, make the rectangle a square: use the smallest edge
	// for both width and height
	if( mHandleEventAction->getEvent()->wasShiftDown() )
	{
		float width = widthVec.length();
		float height = heightVec.length();

		if( width < height )
			heightVec *= (width / height);
		else
			widthVec *= (height / width);
	}
	
	// If Ctrl is down, center the rectangle on first point
	if( mHandleEventAction->getEvent()->wasCtrlDown() )
	{
		p0.setValue( mFirstPoint - widthVec/2 - heightVec/2 );
		p1.setValue( mFirstPoint + widthVec/2 - heightVec/2 );
		p2.setValue( mFirstPoint + widthVec/2 + heightVec/2 );
		p3.setValue( mFirstPoint - widthVec/2 + heightVec/2 );
	}
	else
	{
		p0.setValue( mFirstPoint );	
		p1.setValue( p0.getValue() + widthVec );
		p2.setValue( p0.getValue() + widthVec + heightVec );
		p3.setValue( p0.getValue() + heightVec );
	}
}

void
SoXipRectangle::mouseDown( const SbVec3f& newPos )
{
	if( mHasFirstPoint )
	{
		status.setValue( NONE );
		return ;		
	}
    
    mFirstPoint = newPos;

	p0.setValue( newPos );
	p1.setValue( newPos );
	p2.setValue( newPos );
	p3.setValue( newPos );

	mHasFirstPoint = true;
}

void 
SoXipRectangle::extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed )
{
	// Rectangles are always closed
	closed = TRUE;

	// Set 4 rectangle corners
	point.setNum(4);
	point.set1Value( 0, p0.getValue() );
	point.set1Value( 1, p1.getValue() );
	point.set1Value( 2, p2.getValue() );
	point.set1Value( 3, p3.getValue() );
	
	// Set indices
	XipOverlayUtils::fillCoordIndex( point, closed, coordIndex );
}

void 
SoXipRectangle::transform( const SbMatrix& matrix )
{
	SbVec3f pt;
	matrix.multVecMatrix( p0.getValue(), pt );
	p0.setValue( pt );
	matrix.multVecMatrix( p1.getValue(), pt );
	p1.setValue( pt );
	matrix.multVecMatrix( p2.getValue(), pt );
	p2.setValue( pt );
	matrix.multVecMatrix( p3.getValue(), pt );
	p3.setValue( pt );
}
