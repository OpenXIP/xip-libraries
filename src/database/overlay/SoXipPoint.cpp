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
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/nodes/SoSeparator.h>
#include "SoXipPoint.h"
#include <xip/inventor/overlay/SoXipEditText2.h>

SO_NODE_SOURCE( SoXipPoint );

SoXipPoint::SoXipPoint()
{
	SO_NODE_CONSTRUCTOR( SoXipPoint );

	SO_XIP_KIT_ADD_ENTRY( mPointSeparator, SoSeparator, this );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mPointCoords, SoCoordinate3, mPointSeparator );
	SO_XIP_KIT_ADD_ENTRY( mPointStyle, SoDrawStyle, mPointSeparator );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mPointIndices, SoIndexedLineSet, mPointSeparator );

	// Also attach the geometries to the shadow separator
	((SoSeparator *) mShadowSeparator)->addChild( mPointSeparator );

	SO_XIP_SHAPE_ADD_FIELD( point, (0, 0, 0) );
	point.setNum(0);

	mPointCoords->point.setNum(0);
	mPointIndices->coordIndex.setNum(0);
}

SoXipPoint::~SoXipPoint()
{

}

void
SoXipPoint::initClass()
{
	SO_NODE_INIT_CLASS( SoXipPoint, SoXipHandlerShape, "SoXipHandlerShape" );
}

void
SoXipPoint::beforeCreation()
{
	SoXipHandlerShape::beforeCreation();

	point.setNum(0);
}

void
SoXipPoint::mouseDown( const SbVec3f& newPos )
{
	point.setNum(1);
	point.set1Value( 0, newPos );

	status.setValue( NONE );
}

void 
SoXipPoint::extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed )
{
	// Point are not considered closed
	closed = FALSE;

	// Set the points
	point.copyFrom( this->point );

	// No line segments
	coordIndex.setNum(0);
}

void 
SoXipPoint::GLRender( SoGLRenderAction* action )
{
	if( mIsViewInitialized && point.getNum() )
	{
		SbVec3f dx = projectScreenOffsetToWorld( SbVec2s(3, 0) );
		SbVec3f dy = projectScreenOffsetToWorld( SbVec2s(0, 3) );

		mPointCoords->point.setNum(4);
		mPointCoords->point.set1Value( 0, point[0] - dx );
		mPointCoords->point.set1Value( 1, point[0] - dy );
		mPointCoords->point.set1Value( 2, point[0] + dx );
		mPointCoords->point.set1Value( 3, point[0] + dy );

		const static int s_pointIndices[6] = { 0, 1, 2, 3, 0, -1 };
		mPointIndices->coordIndex.setNum(6);
		mPointIndices->coordIndex.setValues( 0, 6, s_pointIndices );
	}

	SoXipManipulableShape::GLRender( action );
}

void 
SoXipPoint::transform( const SbMatrix& matrix )
{
	if( point.getNum() )
	{
		SbVec3f pt = point[0];
		matrix.multVecMatrix( pt, pt );

		point.set1Value( 0, pt );
	}
}

void 
SoXipPoint::moveHandlerPoint( int id, const SbVec3f& newPos )
{
	if( id != 0 )
	{
		SoDebugError::post( __FILE__, "Invalid point Id" );
		return ;
	}

	point.set1Value( id, newPos );
}

void
SoXipPoint::updateAnnotationPosition( SoSFVec3f& position )
{
	if( mIsViewInitialized && point.getNum() )
	{
		mAnnotation->justification.setValue( SoXipText2::LEFT );
		position.setValue( point[0] + projectScreenOffsetToWorld( SbVec2s( 5, 5 ) ) );
		mAnnotation->vAlignment.setValue( SoXipText2::BOTTOM );
	}
}

void 
SoXipPoint::updateEnumerationPosition( SoSFVec3f& position )
{
	if( mIsViewInitialized && point.getNum() )
	{
		mEnumerationText->justification.setValue( SoXipText2::RIGHT );
		position.setValue( point[0] - projectScreenOffsetToWorld( SbVec2s( 5, 5 ) ) );
		mEnumerationText->vAlignment.setValue( SoXipText2::TOP );
	}
}
