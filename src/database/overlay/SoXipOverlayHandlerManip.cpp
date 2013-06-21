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
#include <xip/inventor/core/SoXipCursor.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <xip/inventor/overlay/SoXipHandlerShape.h>
#include "SoXipOverlayHandlerManip.h"
#include <xip/inventor/overlay/SoXipOverlayManipulatedElement.h>
#include <xip/inventor/overlay/XipOverlayUtils.h>

SO_NODE_SOURCE( SoXipOverlayHandlerManip );

SoXipOverlayHandlerManip::SoXipOverlayHandlerManip()
{
	SO_NODE_CONSTRUCTOR( SoXipOverlayHandlerManip );

	SO_NODE_DEFINE_ENUM_VALUE( ModeType, NONE );
	SO_NODE_DEFINE_ENUM_VALUE( ModeType, MOVE );

	SO_NODE_SET_SF_ENUM_TYPE( mode, ModeType );

	SO_NODE_ADD_FIELD( mode, (NONE) );

	mControlPointsSeparator = 0;

	create();

	mControlPointId = -1;
}

SoXipOverlayHandlerManip::~SoXipOverlayHandlerManip()
{
	if( mControlPointsSeparator )
		mControlPointsSeparator->unref();
	mControlPointsSeparator = 0;
}

void
SoXipOverlayHandlerManip::initClass()
{
	SO_NODE_INIT_CLASS( SoXipOverlayHandlerManip, 
		SoXipOverlayManipBase, "SoXipOverlayManipBase" );
}

void
SoXipOverlayHandlerManip::create()
{
	mControlPointsCoords = new SoCoordinate3;

	mControlPointsStyle = new SoDrawStyle;
	mControlPointsStyle->pointSize.setValue(5);
	mControlPointsStyle->lineWidth.setValue(1);

	SoBaseColor* pColor = new SoBaseColor;
	pColor->rgb.setValue( 1, 1, 1 );	

	SoBaseColor* secondColor = new SoBaseColor;
	secondColor->rgb.setValue( 0.5, 0.5, 0.5 );

	SoDrawStyle* secondStyle = new SoDrawStyle;
	secondStyle->pointSize.setValue(3);

	mTransform = new SoMatrixTransform;
	mTransform->matrix.setValue( SbMatrix::identity() );

	if( mControlPointsSeparator )
		mControlPointsSeparator->unref();

	mControlPointsSeparator = new SoSeparator;
	mControlPointsSeparator->addChild( mTransform );
	mControlPointsSeparator->addChild( mControlPointsCoords );
	mControlPointsSeparator->addChild( mControlPointsStyle );
	mControlPointsSeparator->addChild( pColor );
	mControlPointsSeparator->addChild( new SoPointSet );
	mControlPointsSeparator->addChild( mControlPointsCoords );
	mControlPointsSeparator->addChild( secondStyle );
	mControlPointsSeparator->addChild( secondColor );
	mControlPointsSeparator->addChild( new SoPointSet );

	mControlPointsSeparator->ref();
}

void
SoXipOverlayHandlerManip::handleEvent( SoHandleEventAction* action )
{
	if ( !on.getValue() )
		return;
	
	SoXipOverlayManipBase::handleEvent( action );
	if( action->isHandled() )
		return ;

	if( SO_MOUSE_RELEASE_EVENT( action->getEvent(), BUTTON1 ) ) 
	{
		if( action->getGrabber() == this )
		{
			mode.setValue( NONE );

			SoNodeList shapes = XipOverlayUtils::getManipulableShapes( mActionNode, TRUE );
			for( int i = 0; i < shapes.getLength(); ++ i )
			{
				SoXipHandlerShape* shape = (SoXipHandlerShape *) shapes[i];
				if( shape->isOfType( SoXipHandlerShape::getClassTypeId() ) )
					shape->invalidateGeometries();
			}

			action->setHandled();
			action->releaseGrabber();
		}
	}
	else if( action->getEvent()->isOfType( SoLocation2Event::getClassTypeId() ) )
	{
		if( action->getGrabber() == this )
		{
			SbVec3f pos;
			if( getPoint( action, pos ) )
			{
				SoNodeList shapes = XipOverlayUtils::getManipulableShapes( mActionNode, TRUE );

				for( int i = 0; i < shapes.getLength(); ++ i )
				{
					SoXipHandlerShape* shape = (SoXipHandlerShape *) shapes[i];
					if( shape->isOfType( SoXipHandlerShape::getClassTypeId() ) )
					{
						shape->moveHandlerPoint( mControlPointId, pos );
						shape->invalidateGeometries();
					}
				}
				action->setHandled();
			}
		}
		else
		{
			const SoFullPath* path = (SoFullPath *) action->getCurPath();
			mActionNode = path->getNodeFromTail( numNodesUpToContainer.getValue() );

			if( pickControlPoint( action ) != -1 )
			{
				SoXipCursor::setCursor( "MOVE" );
				action->setHandled();
			}
		}	
	}
	else if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) )
	{
		const SoFullPath* path = (SoFullPath *) action->getCurPath();
		mActionNode = path->getNodeFromTail( numNodesUpToContainer.getValue() );

		if( getPoint( action, mTransformationOrigin ) )
		{
			mControlPointId = pickControlPoint( action );
			if( mControlPointId != -1 )
			{
				mode.setValue( MOVE );

				action->setHandled();
				action->setGrabber( this );
			}
		}
	}
}

void
SoXipOverlayHandlerManip::GLRender( SoGLRenderAction* action )
{
	if (!on.getValue())
		return;
	
	
	SoState *state = action->getState();
	if( state )
	{
		if( SoXipActiveViewportElement::get( state ) == false ||
			SoXipOverlayManipulatedElement::get( state ) )
		{
			return ;
		}

		const SoFullPath* path = (SoFullPath *) action->getCurPath();
		SoNode* searchRoot = path->getNodeFromTail( numNodesUpToContainer.getValue() );

		SoNodeList shapes = XipOverlayUtils::getManipulableShapes( searchRoot, TRUE );

		// If there is only one shape selected, then we can apply the handler manipulator.
		// Otherwise, the transform box manipulator will show the bounding box of the
		// selected shapes, and manipulate them all.
		//
		if( shapes.getLength() == 1 )
		{
			SoXipHandlerShape* shape = (SoXipHandlerShape *) shapes[0];

			if( shape->isOfType( SoXipHandlerShape::getClassTypeId() ) )
			{
				mTransform->matrix.setValue( shape->getTransform() );

				shape->getHandlerPoints( mControlPointsCoords->point );

				glPushAttrib( GL_ENABLE_BIT );
				glDisable( GL_DEPTH_TEST );

				SoXipOverlayManipulatedElement::set( state, this, TRUE );

				mControlPointsSeparator->GLRender( action );

				glPopAttrib();
			}
		}
	}
}

int
SoXipOverlayHandlerManip::pickControlPoint( SoHandleEventAction* action )
{
	SbVec2f mousePt = action->getEvent()->getNormalizedPosition( action->getViewportRegion() );
	SbVec3f screenPt;

	// Get const pointer to the shape points
	const SbVec3f* coordPtr = mControlPointsCoords->point.getValues(0);

	int numPoints = mControlPointsCoords->point.getNum();
	for( int i = 0; i < numPoints; ++ i )
	{
		mViewVolume.projectToScreen( coordPtr[i], screenPt );

		SbVec2f d = SbVec2f( screenPt[0], screenPt[1] ) - mousePt;
		if( d.length() < 0.01 )
			return i;
	}
	return -1;
}
