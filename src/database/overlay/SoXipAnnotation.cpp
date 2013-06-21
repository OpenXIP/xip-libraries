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
#include <xip/system/standard.h>
#include "geomutils.h"
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include "SoXipAnnotation.h"

SO_NODE_SOURCE( SoXipAnnotation );

SoXipAnnotation::SoXipAnnotation()
{
	SO_NODE_CONSTRUCTOR( SoXipAnnotation );

	SO_XIP_KIT_ADD_ENTRY( mArrowSeparator, SoSeparator, this );
	SO_XIP_KIT_ADD_ENTRY( mArrowTransform, SoMatrixTransform, mArrowSeparator );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mArrowCoords, SoCoordinate3, mArrowSeparator );
	SO_XIP_KIT_ADD_ENTRY( mLinesStyle, SoDrawStyle, mArrowSeparator );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mArrowIndices, SoIndexedLineSet, mArrowSeparator );	

	// Also attach the geometries to the shadow separator
	((SoSeparator *) mShadowSeparator)->addChild( mArrowSeparator );

	SO_XIP_SHAPE_ADD_FIELD(  angle, (15) );
	SO_XIP_SHAPE_ADD_FIELD( length, (10) );

	mArrowCoords->point.setNum(0);
	mArrowIndices->coordIndex.setNum(0);

	mFinishTextEditingSensor = new SoFieldSensor( finishTextEditingCB, this );
}

SoXipAnnotation::~SoXipAnnotation()
{
	if( mFinishTextEditingSensor )
	{
		delete mFinishTextEditingSensor;
		mFinishTextEditingSensor = 0;
	}
}

void
SoXipAnnotation::initClass()
{
	SO_NODE_INIT_CLASS( SoXipAnnotation, SoXipLine, "SoXipLine" );
}

void
SoXipAnnotation::beforeCreation()
{
	SoXipLine::beforeCreation();

	mArrowCoords->point.setNum(0);
	mArrowIndices->coordIndex.setNum(0);
}

void
SoXipAnnotation::finishTextEditingCB( void* userData, SoSensor* )
{
	SoXipAnnotation* annot = (SoXipAnnotation *) userData;

	if( annot->mAnnotation->isEditing.getValue() == FALSE )
	{
		annot->caption.setValue( annot->mAnnotation->string.getValue() );
		annot->mFinishTextEditingSensor->detach();
	}
}

void
SoXipAnnotation::mouseUp( const SbVec3f& pos )
{
	SoXipLine::mouseUp( pos );

	// Edit the text
	editText();

	mFinishTextEditingSensor->attach( &mAnnotation->isEditing );
}

void 
SoXipAnnotation::GLRender( SoGLRenderAction* action )
{
	if( mIsViewInitialized && point.getNum() == 2 && point[0] != point[1] )
	{
		float angleValue = angle.getValue() * M_PI / 180.;

		SbVec3f screenPt[2];
		mViewVolume.projectToScreen( point[0], screenPt[0] );
		mViewVolume.projectToScreen( point[1], screenPt[1] );

		float lineAngle = angleBetweenVectors( SbVec3f(1, 0, 0), (screenPt[1] - screenPt[0]) );
		if( screenPt[0][1] > screenPt[1][1] )
			lineAngle = 2 * M_PI - lineAngle;

		float arrowLengthPix = length.getValue();

		SbVec3f offsetUp = projectScreenOffsetToWorld( SbVec2s( 
			arrowLengthPix * cos( lineAngle - angleValue ),
			arrowLengthPix * sin( lineAngle - angleValue ) ) );

		SbVec3f offsetDown = projectScreenOffsetToWorld( SbVec2s( 
			arrowLengthPix * cos( lineAngle + angleValue ),
			arrowLengthPix * sin( lineAngle + angleValue ) ) );

		mArrowCoords->point.setNum(3);
		mArrowCoords->point.set1Value( 0, point[0] );
		mArrowCoords->point.set1Value( 1, point[0] + offsetUp );
		mArrowCoords->point.set1Value( 2, point[0] + offsetDown );
		
		int indices[6] = {0, 1, -1, 0, 2, -1};
		mArrowIndices->coordIndex.setNum(6);
		mArrowIndices->coordIndex.setValues( 0, 6, indices );
	}

	SoXipManipulableShape::GLRender( action );
}

void 
SoXipAnnotation::setViewTransform( const SbMatrix& matrix )
{	
	SoXipLine::setViewTransform( matrix );

	// FIXME : needs to find the good transformation for the
	//         arrow
	if( !isTextPicked() )
		((SoMatrixTransform *) mArrowTransform)->matrix.setValue( matrix );
}

void 
SoXipAnnotation::transform( const SbMatrix& matrix )
{
	SoXipLine::transform( matrix );

	((SoMatrixTransform *) mArrowTransform)->matrix.setValue( SbMatrix::identity() );
}

void
SoXipAnnotation::updateEnumerationPosition( SoSFVec3f& position )
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

		mEnumerationText->justification.setValue( pos_cos ? SoXipText2::LEFT : SoXipText2::RIGHT );
		mEnumerationText->vAlignment.setValue( pos_sin ? SoXipText2::TOP : SoXipText2::BOTTOM );

		SbVec3f offset = projectScreenOffsetToWorld( SbVec2s( 5, 5 ) );
		SbVec3f middle;
		middle[0] = (  pos_cos ? offset[0] : -offset[0] ) + ( p0[0] + p1[0] ) / 2.;
		middle[1] = ( !pos_sin ? offset[1] : -offset[1] ) + ( p0[1] + p1[1] ) / 2.;
		middle[2] = ( p0[2] + p1[2] ) / 2.;

		position.setValue( middle );
	}
}

void
SoXipAnnotation::updateAnnotationPosition( SoSFVec3f& position )
{
	if( mIsViewInitialized && point.getNum() == 2 )
	{
		SbVec3f screenPt[2];
		mViewVolume.projectToScreen( point[0], screenPt[0] );
		mViewVolume.projectToScreen( point[1], screenPt[1] );

		if( screenPt[0][0] < screenPt[1][0] )
		{
			mAnnotation->justification.setValue( SoXipText2::LEFT );
			position.setValue( point[1] + projectScreenOffsetToWorld( SbVec2s( 5, 0 ) ) );
		}
		else
		{
			mAnnotation->justification.setValue( SoXipText2::RIGHT );
			position.setValue( point[1] - projectScreenOffsetToWorld( SbVec2s( 5, 0 ) ) );
		}

		mAnnotation->vAlignment.setValue( SoXipText2::TOP );
	}
}
