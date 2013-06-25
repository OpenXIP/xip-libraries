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
// Disable the warning raised because of the std::map<>
#pragma warning ( disable : 4786 )

#include <xip/system/standard.h>
#include "geomutils.h"
#include <xip/inventor/core/SoXipActiveViewportElement.h>
#include <xip/inventor/core/SoXipCursor.h>

// Inventor actions
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoHandleEventAction.h>

// Inventor events
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoKeyboardEvent.h>

// Inventor nodes
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoDrawStyle.h>

// Inventor misc
#include <Inventor/SoPickedPoint.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/SbTime.h>

#include "SoXipOverlayFilterElement.h"
#include "SoXipOverlayColorElement.h"
#include "SoXipOverlayDrawStyleElement.h"
#include <xip/inventor/overlay/SoXipOverlayManipulatedElement.h>
#include "SoXipDropShadowElement.h"
#include  <xip/inventor/overlay/SoXipManipulableShape.h>

SO_NODE_ABSTRACT_SOURCE( SoXipManipulableShape );

// Maximal distance between two consecutive mouse down positions
// allowed to generate a double-click.
int SoXipManipulableShape::mDoubleClickMaxJump = 2;

// Maximal time between two mouse clicks to be considered as a
// double-click.
SbTime SoXipManipulableShape::mDoubleClickTime = SbTime(0.5);

// Time corresponding to a click
SbTime SoXipManipulableShape::mClickTime = SbTime(0.1);


SoXipManipulableShape::SoXipManipulableShape()
{
	SO_NODE_CONSTRUCTOR( SoXipManipulableShape );

	// Color
	SO_XIP_KIT_ADD_TYPE_ENTRY( mColor, SoMaterial, this );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mDrawStyle, SoDrawStyle, this );

	// Enumeration
	SO_XIP_KIT_ADD_ENTRY( mEnumerationSwitch, SoSwitch, this );	
	SO_XIP_KIT_ADD_ENTRY( mEnumerationSeparator, SoSeparator, mEnumerationSwitch );
	SO_XIP_KIT_ADD_ENTRY( mEnumerationPickStyle, SoPickStyle, mEnumerationSeparator );
	SO_XIP_KIT_ADD_ENTRY( mEnumerationOffset, SoTranslation, mEnumerationSeparator );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mEnumerationText, SoXipText2, mEnumerationSeparator );

	// Text annotation
	SO_XIP_KIT_ADD_ENTRY( mAnnotationSwitch, SoSwitch, this );
	SO_XIP_KIT_ADD_ENTRY( mAnnotationSeparator, SoSeparator, mAnnotationSwitch );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mAnnotationTransform, SoMatrixTransform, mAnnotationSeparator );
	SO_XIP_KIT_ADD_ENTRY( mAnnotationOffset, SoTranslation, mAnnotationSeparator );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mAnnotation, SoXipEditText2, mAnnotationSeparator );

	// Shadows
	SO_XIP_KIT_ADD_ENTRY( mShadowSwitch, SoSwitch, this );
	SO_XIP_KIT_ADD_ENTRY( mShadowSeparator, SoSeparator, mShadowSwitch );
	SO_XIP_KIT_ADD_ENTRY( mShadowMaterial, SoMaterial, mShadowSeparator );
	SO_XIP_KIT_ADD_ENTRY( mShadowOffset, SoTranslation, mShadowSeparator );

	// Top Separator	
	SO_XIP_KIT_ADD_ENTRY( mTopSeparator, SoSeparator, this );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mTransform, SoMatrixTransform, mTopSeparator );

	// Geometries
	SO_XIP_KIT_ADD_ENTRY( mLinesSeparator, SoSeparator, mTopSeparator );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mLinesCoords, SoCoordinate3, mLinesSeparator );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mLinesIndices, SoIndexedLineSet, mLinesSeparator );

	// Also attach the geometries to the shadow separator
	((SoSeparator *) mShadowSeparator)->addChild( mTopSeparator );

	SO_NODE_ADD_FIELD( textAnchored, (TRUE) );
	SO_NODE_ADD_FIELD( textPosition, (0, 0, 0) );	


	mEnumerationText->string.connectFrom( &rank );
	mEnumerationPickStyle->set( "style UNPICKABLE" );

	mAnnotation->string.connectFrom( &caption );
	((SoTranslation *) mAnnotationOffset)->translation.connectFrom( &textPosition );


	mLinesCoords->point.setNum(0);
	mLinesIndices->coordIndex.setNum(0);

	mShowAnnotation			= status.getValue() == NONE;
	mShowEnumeration		= status.getValue() == NONE;
	mIsButtonPressed		= FALSE;	
	mIsViewInitialized		= FALSE;
	mIsTextPicked			= FALSE;
	mIsEnumPicked			= FALSE;
	mIsManipulated			= FALSE;
    mIsSpacePressed         = FALSE;

	mMouseDownTime			= SbTime::zero();
	mMouseDownPos			= SbVec2s(-1, -1);

	mHandleEventAction		= 0;

	invalidateGeometries();
}

SoXipManipulableShape::~SoXipManipulableShape()
{

}

void
SoXipManipulableShape::initClass()
{
	SO_NODE_INIT_ABSTRACT_CLASS( SoXipManipulableShape, SoXipShape, "SoXipShape" );

	SO_ENABLE(    SoGLRenderAction, SoXipOverlayElement);
	SO_ENABLE( SoHandleEventAction, SoXipOverlayElement);

	SO_ENABLE(    SoGLRenderAction, SoXipOverlayManipulatedElement);
	SO_ENABLE( SoHandleEventAction, SoXipOverlayManipulatedElement);
}

SbBool
SoXipManipulableShape::isButtonPressed() const
{
	return mIsButtonPressed;
}

SbBool
SoXipManipulableShape::isClosed() const
{
	return FALSE;
}

SbBool 
SoXipManipulableShape::readInstance( SoInput* in, unsigned short flags )
{
	SbBool readOK = SoNode::readInstance( in , flags );

	invalidateGeometries();

	if( status.getValue() == NONE )
	{
		toggleEnumerationOnOff( TRUE );
		toggleAnnotationOnOff( TRUE );
	}

	return readOK;
}

SbBool
SoXipManipulableShape::isTextPicked() const
{
	return mIsTextPicked;
}

SbBool
SoXipManipulableShape::isTextAnchored() const
{
	return textAnchored.getValue();
}

void
SoXipManipulableShape::GLRender( SoGLRenderAction* action )
{
	SbBool isOn = SoXipOverlayFilterElement::isOn( action->getState(), label );

	if( !isOn || !on.getValue() )
		return ;

	SoState* state = action->getState();
	if( !state )
		return ;	

	saveViewInformation( action );

	if( mIsViewInitialized == FALSE )
	{
		if( SoXipActiveViewportElement::get(state) )
		{
			mIsViewInitialized = TRUE;
			updateViewDependentGeometries();
		}
	}

	if( mUpdateGeometries )
	{
		this->enableNotify( FALSE );

		mUpdateGeometries = FALSE;
		updateGeometries();

		this->enableNotify( TRUE );
	}

	if( mShadowSwitch )
	{
		SoSwitch* shadowSwitch = (SoSwitch *) mShadowSwitch;

		if( !mIsManipulated && SoXipDropShadowElement::isOn( state ) )
		{
			const SbVec2s& shadowPixelOffset = SoXipDropShadowElement::getPixelOffset( state );
			
			SbVec3f p0, p1;
			if( getPoint( action->getNodeAppliedTo(), SbVec2s( 0, 0 ), p0 ) && 
				getPoint( action->getNodeAppliedTo(), shadowPixelOffset, p1 ) )
			{
				((SoTranslation *) mShadowOffset)->translation.setValue( 
					p1[0] - p0[0], p1[1] - p0[1], 0 );

				((SoMaterial *) mShadowMaterial)->diffuseColor.setValue( 
					SoXipDropShadowElement::getColor( state ) );
				((SoMaterial *) mShadowMaterial)->transparency.setValue( 
					SoXipDropShadowElement::getTransparency( state ) );

				if( shadowSwitch->whichChild.getValue() != 0 )
					shadowSwitch->whichChild.setValue (0);			
			}
		}
		else
		{
			if( shadowSwitch->whichChild.getValue() != -1 )
				shadowSwitch->whichChild.setValue (-1); 
		}
	}

	// Set the color
	{
		SbColor shapeColor;
		float shapeAlpha;
		SoXipOverlayColorElement::get( action->getState(), label,
			shapeColor, shapeAlpha );

		mColor->enableNotify( FALSE );
		mColor->diffuseColor.setValue( shapeColor );
		mColor->transparency.setValue( shapeAlpha );
		mColor->enableNotify( TRUE );
	}

	// Set the draw style
	{
		float pointSize, lineWidth;
		unsigned short linePattern;
		SoXipOverlayDrawStyleElement::get( action->getState(), label,
			pointSize, lineWidth, linePattern );

		mDrawStyle->enableNotify( FALSE );
		mDrawStyle->pointSize.setValue( pointSize );
		mDrawStyle->lineWidth.setValue( lineWidth );
		mDrawStyle->linePattern.setValue( linePattern );
		mDrawStyle->enableNotify( TRUE );
	}	
	
	SbXipOverlaySettings settings = SoXipOverlayElement::get( action->getState() );

	// Disable notification to avoid invalidating the cache and call GLRender again
	mAnnotationSwitch->enableNotify( FALSE );
	mEnumerationSwitch->enableNotify( FALSE );
	
	// By default hide annotation and enumeration
	((SoSwitch *) mAnnotationSwitch)->whichChild.setValue(-1);
	((SoSwitch *) mEnumerationSwitch)->whichChild.setValue(-1);

	// Show/hide annotation and enumeration
	if( mShowAnnotation && settings.shouldDisplayAnnotation() )
		((SoSwitch *) mAnnotationSwitch)->whichChild.setValue(0);

	if( mShowEnumeration && settings.shouldDisplayEnumeration() && rank.getValue() != -1 )
		((SoSwitch *) mEnumerationSwitch)->whichChild.setValue(0);

	// Restore notification
	mAnnotationSwitch->enableNotify( TRUE );
	mEnumerationSwitch->enableNotify( TRUE );

	GLboolean depthTest = glIsEnabled( GL_DEPTH_TEST );
	if( depthTest )
		glDisable( GL_DEPTH_TEST );

	if( mLinesCoords->point.getNum() > 1 )
	{
		SoXipKit::GLRender( action );
	}

	if( depthTest )
		glEnable( GL_DEPTH_TEST );
}

void
SoXipManipulableShape::handleEvent( SoHandleEventAction* action )
{
	if( !on.getValue() )
		return ;

	SoXipShape::handleEvent( action );
	if( action->isHandled() )
		return ;

	SbVec3f pos;

	const SbVec2s& mousePosition = action->getEvent()->getPosition();
	
	if( action->getGrabber() == this )
	{
		mHandleEventAction = action;
	}

	if( action->getEvent()->isOfType( SoKeyboardEvent::getClassTypeId() ) )
	{	
		const SoKeyboardEvent* keyEvent = (const SoKeyboardEvent *) action->getEvent();

		if( keyEvent->getKey() == SoKeyboardEvent::SPACE )
		{
			if( SO_KEY_PRESS_EVENT( action->getEvent(), ANY ) && !mIsSpacePressed )
			{				
				getPoint( action, mSpacePosition );
				mIsSpacePressed = TRUE;
			}
			else if( SO_KEY_RELEASE_EVENT( action->getEvent(), ANY ) )
			{
				mIsSpacePressed = FALSE;
			}			
		}
	}
    else if( SO_MOUSE_RELEASE_EVENT( action->getEvent(), BUTTON1 ) && action->getGrabber() == this ) 
	{
		if( getPoint( action, pos ) )
		{
			mMouseUpTime = action->getEvent()->getTime();
			mouseUp( pos );
		}

		if( status.getValue() == NONE )
		{
			select( TRUE );

			updateGeometries();

			action->releaseGrabber();
		}

		action->setHandled();

		mIsButtonPressed = FALSE;
	}
	else if( action->getEvent()->isOfType( SoLocation2Event::getClassTypeId() ) && action->getGrabber() == this )
	{
		if( mousePosition != mMouseDownPos )
		{
			if( status.getValue() == CREATE && getPoint( action, pos ) )
			{
				if( mIsSpacePressed )
				{
					translate( pos - mSpacePosition );
					mSpacePosition = pos;
				}
				else mouseMove( pos );
			}
		}

		action->setHandled();
	}
	else if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) )
	{
		if( isCreating() )
		{
			action->setHandled();
	
			SbTime time = action->getEvent()->getTime();

			// Compute the distance between the last mouse press event and this one
			SbVec2s v = (mMouseDownPos - mousePosition);
			float mouseJump = sqrtf( v.dot(v) );

			// Do not perform a double-click if the time between two mouse press
			// events is higher than the default time set for double-clicks, or if
			// the mouse jumped further than the tolerance set (without tolerance
			// it is more difficult to get a double-click.
			if( (time - mMouseDownTime) < mDoubleClickTime && mouseJump < mDoubleClickMaxJump )
			{
				if( getPoint( action->getNodeAppliedTo(), mMouseDownPos, pos ) )
					mouseDouble( pos );

				mMouseDownTime = SbTime::zero();
				mMouseDownPos = SbVec2s(-1, -1);
			}
			else
			{
				action->setGrabber( this );

				if( getPoint( action, pos ) )
					mouseDown( pos );
				
				mIsButtonPressed = TRUE;
				mMouseDownTime = time;
				mMouseDownPos = mousePosition;
			}
		}
	}

	if( action->getGrabber() == this )
	{
		updateGeometries();

		if( status.getValue() == NONE )
		{
			// We just finish to create the shape. Make it selected
			select( TRUE );
		}
	}
}

const SbMatrix&
SoXipManipulableShape::getTransform() const
{
	return mTransform->matrix.getValue();
}

void
SoXipManipulableShape::setViewTransform( const SbMatrix& viewMatrix )
{
	// Hide the enumeration
	toggleEnumerationOnOff( FALSE );

	mIsManipulated = TRUE;

	if( isTextPicked() )
	{
		mAnnotationTransform->matrix.setValue( viewMatrix );

		// If the user starts dragging the text annotation, then
		// the text is not anchored to the shape anymore.
		textAnchored.setValue( FALSE );		
	}
	else
	{
		mTransform->matrix.setValue( viewMatrix );

		// If the text is anchored, then its position needs to be
		// recomputed everytime the shape is changing. To avoid this,
		// the text annotation is hidden until the transformation is
		// applied.
		if( isTextAnchored() )
			toggleAnnotationOnOff( FALSE );
	}	
}

void
SoXipManipulableShape::applyViewTransform( const SbMatrix& viewMatrix )
{
	if( !isTextPicked() )
	{
		transform( viewMatrix );

		mTransform->matrix.setValue( SbMatrix::identity() );

		updateGeometries();

		// Show the text
		if( isTextAnchored() )
			toggleAnnotationOnOff( TRUE );
	}
	else
	{
		mAnnotationTransform->matrix.setValue( SbMatrix::identity() );
		
		SbVec3f newTextOffset;
		viewMatrix.multVecMatrix( textPosition.getValue(), newTextOffset );
		textPosition.setValue( newTextOffset );
		
		textAnchored.setValue( FALSE );
	}

	mIsManipulated = FALSE;

	toggleEnumerationOnOff( TRUE );
}

void
SoXipManipulableShape::updateGeometries()
{
	if( mLinesCoords && mLinesIndices )
	{		
		SbBool dummyClosed;
		extractGeometries( mLinesCoords->point, mLinesIndices->coordIndex, dummyClosed );
	}

	updateViewDependentGeometries();
}

void
SoXipManipulableShape::updateViewDependentGeometries()
{
	if( isTextAnchored() )
		updateAnnotationPosition( textPosition );

	updateEnumerationPosition( ((SoTranslation *) mEnumerationOffset)->translation );
}

void 
SoXipManipulableShape::updateEnumerationPosition( SoSFVec3f& position )
{
	if( mIsViewInitialized )
	{
		mEnumerationText->justification.setValue( SoXipText2::LEFT );
		mEnumerationText->vAlignment.setValue( SoXipText2::BOTTOM );

		SbXfBox3f bbox;
		computeXBoundingBox( bbox );

		SbVec3f bboxMin, bboxMax, refPt;
		bbox.getBounds( bboxMin, bboxMax );
		bbox.getTransform().multVecMatrix( bboxMax, refPt );

		int pointIndex  = closestPoint( mLinesCoords->point, refPt );
		if( pointIndex != -1 )
		{
			SbVec3f offset = projectScreenOffsetToWorld( SbVec2s( 5, 0 ) );
	
			// By default (if method not overwritten), enumeration will be
			// positionned in the top right corner, as close as possible from
			// from the shape
			position.setValue( mLinesCoords->point[ pointIndex ] + offset );
		}
	}
}

void 
SoXipManipulableShape::updateAnnotationPosition( SoSFVec3f& position )
{
	if( mIsViewInitialized )
	{
		mAnnotation->justification.setValue( SoXipText2::RIGHT );
		mAnnotation->vAlignment.setValue( SoXipText2::TOP );

		SbXfBox3f bbox;
		computeXBoundingBox( bbox );

		SbVec3f bboxMin, bboxMax, refPt;
		bbox.getBounds( bboxMin, bboxMax );
		bbox.getTransform().multVecMatrix( bboxMin, refPt );

		int pointIndex = closestPoint( mLinesCoords->point, refPt );
		if( pointIndex != -1 )
		{
			SbVec3f offset = projectScreenOffsetToWorld( SbVec2s( 5, 0 ) );

			// By default (if method not overwritten), text will be
			// positionned in the bottom left corner, as close as possible from
			// from the shape
			position.setValue( mLinesCoords->point[ pointIndex ] - offset );
		}
	}
}

void
SoXipManipulableShape::rayPick( SoRayPickAction* action )
{
	if( !on.getValue() )
		return ;

	SoXipShape::pick( action );

	if( action->isPickAll() )
	{
		mIsTextPicked = FALSE;

		SoPickedPointList pickedPoints = action->getPickedPointList();
		for( int i = 0; i < pickedPoints.getLength(); ++ i )
		{
			if( pickedPoints[i]->getPath()->containsNode( this ) )
			{
				mIsTextPicked	= pickedPoints[i]->getPath()->containsNode( mAnnotation );
				break ;
			}
		}
	}
	else
	{
		SoPickedPoint* pickedPoint = action->getPickedPoint();
		if( pickedPoint )
			mIsTextPicked = pickedPoint->getPath()->containsNode( mAnnotation );
	}
}

void
SoXipManipulableShape::beforeCreation()
{
	mLinesCoords->point.setNum(0);
	mLinesIndices->coordIndex.setNum(0);

	// Hide the annotation
	toggleAnnotationOnOff( FALSE );
	toggleEnumerationOnOff( FALSE );
}

void
SoXipManipulableShape::afterCreation()
{
	// Show the annotation
	toggleAnnotationOnOff( TRUE );
	toggleEnumerationOnOff( TRUE );
}

void
SoXipManipulableShape::computeXBoundingBox( SbXfBox3f& bbox )
{
	if( !mLinesCoords || mLinesCoords->point.getNum() <= 0 )
		return ;

	SbMatrix affine, proj;
	mViewVolume.getMatrices( affine, proj );

	bbox.makeEmpty();
	bbox.setTransform( affine.inverse() );

	const SoMFVec3f& point = mLinesCoords->point;
	for( int i = 0; i < point.getNum(); ++ i )
	{
		bbox.extendBy( point[i] );
	}
}

void
SoXipManipulableShape::editText()
{
	mAnnotation->isEditing.setValue( TRUE );
	mAnnotation->startNotify();
}

void
SoXipManipulableShape::editText( SoHandleEventAction* action )
{
	mAnnotation->isEditing.setValue( TRUE );
	mAnnotation->startNotify();
	
	action->setGrabber( mAnnotation );
}

void
SoXipManipulableShape::toggleEnumerationOnOff( SbBool flag )
{
	mShowEnumeration = flag;
}

void
SoXipManipulableShape::toggleAnnotationOnOff( SbBool flag )
{
	mShowAnnotation = flag;
}

void
SoXipManipulableShape::invalidateGeometries()
{
	mUpdateGeometries = TRUE;

	startNotify();
}

void 
SoXipManipulableShape::invalidateGeometriesCB( void* userData, SoSensor* )
{
	((SoXipManipulableShape *) userData)->invalidateGeometries();
}
