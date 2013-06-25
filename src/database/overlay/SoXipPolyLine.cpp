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
#include "geomutils.h"
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/nodes/SoTranslation.h>
#include "SoXipPolyLine.h"
#include <xip/inventor/overlay/SoXipEditText2.h>
#include  <xip/inventor/overlay/XipOverlayUtils.h>
SO_NODE_SOURCE( SoXipPolyLine );

SoXipPolyLine::SoXipPolyLine()
{
	SO_NODE_CONSTRUCTOR( SoXipPolyLine );

	SO_XIP_SHAPE_ADD_FIELD( point, (0, 0, 0) );
	point.setNum(0);
}

SoXipPolyLine::~SoXipPolyLine()
{

}

void
SoXipPolyLine::initClass()
{
	SO_NODE_INIT_CLASS( SoXipPolyLine, SoXipHandlerShape, "SoXipHandlerShape" );
}

void
SoXipPolyLine::beforeCreation()
{
	SoXipHandlerShape::beforeCreation();

	point.setNum(0);
}

void
SoXipPolyLine::translate( const SbVec3f& offset )
{
	SbVec3f* pointPtr = point.startEditing();
	for( int i = 0; i < point.getNum(); ++ i )
		(*pointPtr ++) += offset;
	point.finishEditing();
}

void
SoXipPolyLine::mouseDouble( const SbVec3f& newPos )
{
	if( point.getNum() >= 2 )
	{
		// Remove the last point resulting from the mouse down event
		point.setNum( point.getNum() - 1 );

		// Creation is done
		status.setValue( NONE );
	}
}

void
SoXipPolyLine::mouseUp( const SbVec3f& newPos )
{
	// This is to prevent artefact points due a fast mouse move
	if( (mMouseUpTime - mMouseDownTime) > mClickTime )
		point.set1Value( point.getNum(), newPos );
}

void
SoXipPolyLine::mouseMove( const SbVec3f& newPos )
{
    if (point.getNum() > 0)
        point.set1Value( point.getNum() - 1, newPos );
}

void
SoXipPolyLine::mouseDown( const SbVec3f& newPos )
{
	if( point.getNum() == 0 )
		point.set1Value( point.getNum(), newPos );
	point.set1Value( point.getNum(), newPos );
}

void 
SoXipPolyLine::extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed )
{
	// Polylines are always closed
	closed = FALSE;

	// Set the point
	point.copyFrom( this->point );

	// Set the coordinate indices
	XipOverlayUtils::fillCoordIndex( point, closed, coordIndex );
}

void 
SoXipPolyLine::transform( const SbMatrix& matrix )
{
	SbVec3f* pointPtr = point.startEditing();
	int numPoints = point.getNum();
	for( int i = 0; i < numPoints; ++ i, ++ pointPtr )
	{
		matrix.multVecMatrix( *pointPtr, *pointPtr );
	}
	point.finishEditing();
}

void 
SoXipPolyLine::moveHandlerPoint( int id, const SbVec3f& newPos )
{
	point.set1Value( id, newPos );
}

void
SoXipPolyLine::updateAnnotationPosition( SoSFVec3f& position )
{
	if( mIsViewInitialized && point.getNum() >= 2 )
	{
		const SbVec3f& p0 = point[0];
		const SbVec3f& p1 = point[1];
		
		SbVec3f u = SbVec3f( 1, 0, 0 );
		SbVec3f v = p1 - p0;
		SbVec3f normal = mViewVolume.getPlane(0).getNormal();

		double a = angleBetweenVectors( u, v, normal );
		bool pos_cos = cos(a) > 0;
		bool pos_sin = sin(a) > 0;

		mAnnotation->justification.setValue( pos_cos ? SoXipText2::LEFT : SoXipText2::RIGHT );
		mAnnotation->vAlignment.setValue( pos_sin ? SoXipText2::TOP : SoXipText2::BOTTOM );

		SbVec3f offset = projectScreenOffsetToWorld( SbVec2s( 5, 5 ) );
		SbVec3f middle;
		middle[0] = (  pos_cos ? offset[0] : -offset[0] ) + ( p0[0] + p1[0] ) / 2.;
		middle[1] = ( !pos_sin ? offset[1] : -offset[1] ) + ( p0[1] + p1[1] ) / 2.;
		middle[2] = ( p0[2] + p1[2] ) / 2.;

		position.setValue( middle );
	}
}

void 
SoXipPolyLine::updateEnumerationPosition( SoSFVec3f& position )
{
	if( mIsViewInitialized && point.getNum() >= 2 )
	{
		SbVec3f screenPt[2];
		mViewVolume.projectToScreen( point[0], screenPt[0] );
		mViewVolume.projectToScreen( point[1], screenPt[1] );

		if( screenPt[0][0] < screenPt[1][0] )
		{
			mEnumerationText->justification.setValue( SoXipText2::RIGHT );
			position.setValue( point[0] - projectScreenOffsetToWorld( SbVec2s( 5, 0 ) ) );
		}
		else
		{
			mEnumerationText->justification.setValue( SoXipText2::LEFT );
			position.setValue( point[0] + projectScreenOffsetToWorld( SbVec2s( 5, 0 ) ) );
		}

		if( screenPt[0][1] < screenPt[1][1] )
			mEnumerationText->vAlignment.setValue( SoXipText2::TOP );
		else
			mEnumerationText->vAlignment.setValue( SoXipText2::BOTTOM );
	}
}
