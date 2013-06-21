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
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include "SoXipBox.h"

SO_NODE_SOURCE( SoXipBox );

SoXipBox::SoXipBox()
{
	SO_NODE_CONSTRUCTOR( SoXipBox );

	SO_NODE_ADD_FIELD( on, (TRUE) );
	SO_NODE_ADD_FIELD( showCenter, (FALSE));
	SO_NODE_ADD_FIELD( point, (0, 0, 0) );
	SO_NODE_ADD_FIELD( padding, (0, 0, 0) );
	SO_NODE_ADD_FIELD( volumeOfInterest,  (SbMatrix::identity()) );

	mDrawing = false;
	mViewport = SbViewportRegion( 1, 1 );
	mPlaneProj = new SbPlaneProjector( FALSE );

	mCoords = new SoCoordinate3;

	SoIndexedLineSet *lineSet = new SoIndexedLineSet;
	lineSet->set( "coordIndex 0, 1, 2, 3, 0, -1" );

	mSeparator = new SoGroup;
	mSeparator->ref();	
	mSeparator->addChild( mCoords );
	mSeparator->addChild( new SoPointSet );
	mSeparator->addChild( lineSet );	
}

SoXipBox::~SoXipBox()
{
	if( mSeparator )
	{
		mSeparator->unref();
		mSeparator = 0;
	}

	if( mPlaneProj )
	{
		delete mPlaneProj;
		mPlaneProj = 0;
	}
}

void 
SoXipBox::initClass()
{
	SO_NODE_INIT_CLASS( SoXipBox, SoNode, "Node" );
}

void 
SoXipBox::GLRender( SoGLRenderAction* action )
{
	if( on.getValue() && mDrawing )
	{
		mSeparator->GLRender( action );		
	}
}

void SoXipBox::handleEvent( SoHandleEventAction* action )
{
	if( !on.getValue() )
		return ;

	if( !action->getGrabber() )
	{
		SoState* state = action->getState();

		mViewVolume = SoViewVolumeElement::get( state );
		mPlaneProj->setViewVolume( mViewVolume );

		float distance = mViewVolume.getDepth() / 2.f;
		mPlaneProj->setPlane( mViewVolume.getPlane( mViewVolume.getNearDist() + distance ) );
		mViewport = SoViewportRegionElement::get( state );
	}

	const SoEvent* event = action->getEvent();

	SbVec3f pos = mPlaneProj->project( event->getNormalizedPosition(mViewport) );

	if( SO_MOUSE_PRESS_EVENT( event, BUTTON1 ) && !action->getGrabber() )
	{
		mFirstCoordinates = pos;

		point.setNum(0);

		action->setGrabber(this);
		action->setHandled();
	}
	else
	{
		SbVec3f posOffsetX = mPlaneProj->project( event->getNormalizedPosition(mViewport) + SbVec2f(1, 0) );
		SbVec3f posOffsetY = mPlaneProj->project( event->getNormalizedPosition(mViewport) + SbVec2f(0, 1) );
		SbVec3f pos1 = SbLine(pos, posOffsetX).getClosestPoint( mFirstCoordinates );
		SbVec3f pos2 = SbLine(pos, posOffsetY).getClosestPoint( mFirstCoordinates );

		if( action->getGrabber() == this && event->isOfType( SoLocation2Event::getClassTypeId() ) )
		{
			mCoords->point.set1Value( 0, mFirstCoordinates );
			mCoords->point.set1Value( 1, pos1 );
			mCoords->point.set1Value( 2, pos );
			mCoords->point.set1Value( 3, pos2 );

			if( showCenter.getValue() )
				mCoords->point.set1Value( 4, mFirstCoordinates + (pos - mFirstCoordinates) * 0.5 );

			// this node needs to be re-rendered
			startNotify();

			action->setHandled();
			mDrawing = true;
		}
		else if( action->getGrabber() == this && SO_MOUSE_RELEASE_EVENT( event, BUTTON1 ) )
		{
			mCoords->point.setNum( 0 );

			SbVec3f t = mFirstCoordinates;
			SbVec3f x = pos2 - mFirstCoordinates;
			SbVec3f y = pos1 - mFirstCoordinates;
			SbVec3f n = mPlaneProj->getPlane().getNormal();

			// enlarge width of voi
			SbVec3f tmp = x;
			tmp.normalize();
			tmp *= padding.getValue()[0];
			t -= tmp;
			x += 2.f * tmp;

			// enlarge height of voi
			tmp = y;
			tmp.normalize();
			tmp *= padding.getValue()[1];
			t -= tmp;
			y += 2.f * tmp;

			// compute depth of voi 
			// (box is drawn on plane, must ignore prev. depth)
			tmp = n;
			tmp.normalize();
			tmp *= padding.getValue()[2];
			t -= tmp;
			n = 2.f * tmp;

			SbMatrix voi(
				x[0], x[1], x[2], 0,
				y[0], y[1], y[2], 0,
				n[0], n[1], n[2], 0,
				t[0], t[1], t[2], 1 );
			
			SbVec3f s;
			SbRotation rot, so;
			voi.getTransform(t, rot, s, so);

			if (s[0] < 0)
			{
				t += x + y + n;
				x *= -1.f;
				y *= -1.f;
				n *= -1.f;

				voi = SbMatrix(
					x[0], x[1], x[2], 0,
					y[0], y[1], y[2], 0,
					n[0], n[1], n[2], 0,
					t[0], t[1], t[2], 1 );
			}

			volumeOfInterest.setValue(voi);

			// update point field after the VOI has been set, because
			// updates in the network are typically triggered by the point field
			point.setNum(2);
			point.set1Value( 0, mFirstCoordinates );
			point.set1Value( 1, pos );

			action->releaseGrabber();
			action->setHandled();

			mDrawing = false;
		}
	}

	SoNode::handleEvent( action );
}
