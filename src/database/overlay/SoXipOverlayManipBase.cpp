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
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/events/SoEvent.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/SoPickedPoint.h>
#include <xip/inventor/overlay/SoXipOverlayManipBase.h>
#include  <xip/inventor/overlay/SoXipManipulableShape.h>
#include <xip/inventor/overlay/XipOverlayUtils.h>

SO_NODE_ABSTRACT_SOURCE( SoXipOverlayManipBase );

XIPIVOVERLAY_API  SoXipOverlayManipBase::SoXipOverlayManipBase()
{
	SO_NODE_CONSTRUCTOR( SoXipOverlayManipBase );

	SO_NODE_ADD_FIELD(                    on, (TRUE) );
	SO_NODE_ADD_FIELD( numNodesUpToContainer,    (1) );

	mPlaneProj = new SbPlaneProjector;
	mPlaneProj->setPlane( SbPlane( SbVec3f(0, 0, 1), 0 ) );

	mTransformationMatrix = SbMatrix::identity();
	mTransformationOrigin = SbVec3f( 0, 0, 0 );

	mPickedShape = 0;
	mActionNode = 0;
}

SoXipOverlayManipBase::~SoXipOverlayManipBase()
{
	if( mPlaneProj )
		delete mPlaneProj;
	mPlaneProj = 0;
}

void
SoXipOverlayManipBase::initClass()
{
	SO_NODE_INIT_ABSTRACT_CLASS( SoXipOverlayManipBase, SoNode, "Node" );
}

void
SoXipOverlayManipBase::saveViewInformation( SoAction* action )
{
	SoState* state = action->getState();

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

SbBool
SoXipOverlayManipBase::getPoint( SoHandleEventAction* action, SbVec3f& point )
{
	SoState* state = action->getState();
	if( !state )
		return FALSE;

	const SoEvent* event = action->getEvent();
	if( !event )
		return FALSE;

	if( mOverlaySettings.getLocation() == SoXipOverlayElement::FOCAL_PLANE ||
		mOverlaySettings.getLocation() == SoXipOverlayElement::NEAR_PLANE )
	{
		point = mPlaneProj->project( event->getNormalizedPosition( mViewport ) );
		return TRUE;
	}
	else if( mOverlaySettings.getLocation() == SoXipOverlayElement::PICKING )
	{
		SoRayPickAction pa( action->getViewportRegion() );
		pa.setPoint( event->getPosition() );
		pa.setRadius( 1 );
		pa.enableCulling( FALSE );
		pa.apply( action->getNodeAppliedTo() );

		if( pa.getPickedPoint() )
		{
			point = pa.getPickedPoint()->getPoint();
			return TRUE;
		}
	}
	else
	{
		SoError::post( "SoXipOverlayElement: Unknown location" );
	}

	return FALSE;
}

void
SoXipOverlayManipBase::handleEvent( SoHandleEventAction* action )
{
	if( action->isHandled() )
	{
		return ;
	}

	// Once you set the grabber, the scene is not going to be traversed
	// for the next events. Need to save any view information prior.
	//	
	if( !action->getGrabber() )
	{
		saveViewInformation( action );
	}

	if( action->getEvent()->isOfType( SoLocation2Event::getClassTypeId() ) )
	{
		if( !action->getGrabber() )
		{
			const SoFullPath* path = (SoFullPath *) action->getCurPath();
			mActionNode = path->getNodeFromTail( numNodesUpToContainer.getValue() );
		}	
	}
	else if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) )
	{
		const SoFullPath* path = (SoFullPath *) action->getCurPath();

		mActionNode = path->getNodeFromTail( numNodesUpToContainer.getValue() );

 		mPickedShape = isShapePicked( action );
	}
}

void
SoXipOverlayManipBase::transform( SoNode* root )
{
	// Get the list of selected manipulable shapes (groups of shapes are not considered
	// as manipulable shapes)
	//
	SoNodeList shapes = XipOverlayUtils::getManipulableShapes( root, TRUE );
	for( int i = 0; i < shapes.getLength(); ++ i )
	{
		((SoXipManipulableShape *) shapes[i])->setViewTransform( mTransformationMatrix );
	}

	if( shapes.getLength() == 0 && mPickedShape )
	{
		mPickedShape->setViewTransform( mTransformationMatrix );
	}
}

void
SoXipOverlayManipBase::applyTransform( SoNode* root )
{
	// Get the list of selected manipulable shapes (groups of shapes are not considered
	// as manipulable shapes)
	//
	SoNodeList shapes = XipOverlayUtils::getManipulableShapes( root, TRUE );
	for( int i = 0; i < shapes.getLength(); ++ i )
	{
		((SoXipManipulableShape *) shapes[i])->applyViewTransform( mTransformationMatrix );
	}

	if( shapes.getLength() == 0 && mPickedShape )
	{
		mPickedShape->applyViewTransform( mTransformationMatrix );
	}
}

SoXipManipulableShape*
SoXipOverlayManipBase::isShapePicked( SoHandleEventAction* action )
{
	SoRayPickAction pa( action->getViewportRegion() );
	pa.setPoint( action->getEvent()->getPosition() );
	pa.setRadius( 3 );
	pa.setPickAll( TRUE );
	pa.enableCulling( FALSE );
	pa.apply( action->getNodeAppliedTo() );

	SoPickedPointList pickedPoints = pa.getPickedPointList();
	for( int i = 0; i < pickedPoints.getLength(); ++ i )
	{
		SoFullPath* path = (SoFullPath *) pickedPoints[i]->getPath();
		if( !path->containsNode( mActionNode ) )
			continue ;

		for( int j = 0; j < path->getLength(); ++ j )
		{
			if( path->getNodeFromTail(j)->isOfType( SoXipManipulableShape::getClassTypeId() ) )
				return (SoXipManipulableShape *) path->getNodeFromTail(j);
		}
	}
	return 0;
}

SbVec3f 
SoXipOverlayManipBase::projectScreenOffsetToWorld( const SbVec2s& pixelOffset ) const
{
	SbVec2f normOffset = SbVec2f(
		pixelOffset[0] / (float) mViewport.getViewportSizePixels()[0],
		pixelOffset[1] / (float) mViewport.getViewportSizePixels()[1] );

	return mPlaneProj->project( normOffset ) - mPlaneProj->project( SbVec2f( 0, 0 ) );
}
