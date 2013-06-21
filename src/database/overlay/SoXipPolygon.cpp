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
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include "SoXipPolygon.h"

SO_NODE_SOURCE( SoXipPolygon );

SoXipPolygon::SoXipPolygon()
{
	SO_NODE_CONSTRUCTOR( SoXipPolygon );
}

SoXipPolygon::~SoXipPolygon()
{

}

void
SoXipPolygon::initClass()
{
	SO_NODE_INIT_CLASS( SoXipPolygon, SoXipEditableShape, "SoXipEditableShape" );
}

SbBool
SoXipPolygon::canClose( const SbVec3f& pos ) const
{
	// Do not need to close the shape if already closed
	if( isClosed() )
		return FALSE;

	// The number of points should be at least 4.
	// The 4th point corresponds to the one which is moving.
	if( point.getNum() > 3 )
	{
		// minimum size for contour is given, check if the last point
		// is very close to the start point so we can close the contour
		SbVec3f screenPt[2];
		mViewVolume.projectToScreen( point[0], screenPt[0] );
		mViewVolume.projectToScreen(      pos, screenPt[1] );

		SbVec3f d = screenPt[0] - screenPt[1];
		d[0] *= mViewport.getViewportSizePixels()[0];
		d[1] *= mViewport.getViewportSizePixels()[1];
		d[2] = 0;

		return d.length() < CLOSING_MIN_PIXEL_DISTANCE;
	}

	return FALSE;
}

SbBool
SoXipPolygon::isConsistent() const
{
	// check if the contour size is greater than the minimum size.
	const SbVec3f* pointPtr = point.getValues(0);

	SbBox3f bbox;
	for( int i = 0; i < point.getNum(); ++ i )
		bbox.extendBy( pointPtr[i] );

	SbVec3f bbSize;
	bbox.getSize(bbSize[0], bbSize[1], bbSize[2]);

	float screenScale = mViewVolume.getHeight() / mViewport.getViewportSizePixels()[1];
	float bbLengthPix = bbSize.length() / screenScale;

	return ( bbLengthPix >= (2 * CLOSING_MIN_PIXEL_DISTANCE) );
}

void
SoXipPolygon::translate( const SbVec3f& offset )
{
	SbVec3f* pointPtr = point.startEditing();
	for( int i = 0; i < point.getNum(); ++ i )
		(*pointPtr ++) += offset;
	point.finishEditing();
}

void
SoXipPolygon::mouseUp( const SbVec3f& newPos )
{
	if( isEditing() )
		return ;

	// If the shape can be closed and is consitent (big enough)
	if( canClose( newPos ) && isConsistent() )
	{
		closed.setValue( TRUE );

		// Remove the last point corresponding to the moving point.
		point.setNum( point.getNum() - 1 );

		// Creation is done
		status.setValue( NONE );
	}
	
	// If user keeps the mouse button pressed, then a point should
	// be added when the mouse is released.
	// But to prevent artefact points due to a fast click & move,
	// point are only added if the event is not considered as a
	// click.
	else if( (mMouseUpTime - mMouseDownTime) > mClickTime )
	{
		if (*point.getValues(point.getNum() - 1) != newPos)
			point.set1Value( point.getNum(), newPos );
	}	
}

void
SoXipPolygon::mouseMove( const SbVec3f& newPos )
{
	if( isEditing() )
	{
		if( mControlPointId != -1 )
			point.set1Value( mControlPointId, newPos );
	}
	else
	{
		// Look if the mouse cursor is near the starting point.
		// If so it gets anchored to its position, and the user will be
		// able to close the shape later
		if( canClose( newPos ) )
			point.set1Value( point.getNum() - 1, point[0] );
		else
			point.set1Value( point.getNum() - 1, newPos );
	}
}

void
SoXipPolygon::mouseDown( const SbVec3f& newPos )
{
	if( !isEditing() )
	{
		if( point.getNum() == 0 )
			point.set1Value( point.getNum(), newPos );

		// If the shape can be closed and is consitent (big enough)
		if( canClose( newPos ) && isConsistent() )
		{
			closed.setValue( TRUE );

			// Remove the last point corresponding to the moving point.
			point.setNum( point.getNum() - 1 );

			// Creation is done
			status.setValue( NONE );
		}
		else
		{
			point.set1Value( point.getNum(), newPos );
		}
	}
}

void
SoXipPolygon::mouseDouble( const SbVec3f& newPos )
{
	if( point.getNum() > 3 )
	{
		if( closeOnDblClick.getValue() )
			closed.setValue( TRUE );

		// Remove last point added by the mouseDown event, since events
		// are no more delayed!
		point.setNum( point.getNum() - 1 );

		// Creation is done
		status.setValue( NONE );
		return ;
	}

	point.set1Value( point.getNum(), newPos );
}
