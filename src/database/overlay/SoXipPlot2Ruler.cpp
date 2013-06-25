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
/**
*	@file	SoXipPlot2Ruler.cpp
*	@brief	Implementation of the SoXipPlot2Ruler class
*	@author	Julien Gein
**/

#include <xip/inventor/core/SoXipCursor.h>
#include <xip/inventor/overlay/SoXipPlot2AreaElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoLineSet.h>
#include "SoXipPlot2Ruler.h"

SO_NODE_SOURCE( SoXipPlot2Ruler );

SoXipPlot2Ruler::SoXipPlot2Ruler()
{
	SO_NODE_CONSTRUCTOR( SoXipPlot2Ruler );

	SO_NODE_DEFINE_ENUM_VALUE( RulerType,  HORIZONTAL );
	SO_NODE_DEFINE_ENUM_VALUE( RulerType,  VERTICAL );
	SO_NODE_SET_SF_ENUM_TYPE( type, RulerType );

	SO_NODE_ADD_FIELD( type, (VERTICAL) );
	SO_NODE_ADD_FIELD( value, (0) );
	value.setNum(0);

	mCoord = new SoCoordinate3;
	mCoord->point.setNum(0);
	mCoord->ref();

	mLineSet = new SoLineSet;
	mLineSet->numVertices.setValue(0);
	mLineSet->ref();

	mSelectedValue = -1;
}

SoXipPlot2Ruler::~SoXipPlot2Ruler()
{
	mCoord->unref();
	mLineSet->unref();
}

void
SoXipPlot2Ruler::initClass()
{
	SO_NODE_INIT_CLASS( SoXipPlot2Ruler, SoNode, "Node" );
}

void
SoXipPlot2Ruler::GLRender( SoGLRenderAction* action )
{
	SoState* state = action->getState();
	if( !state )
		return ;

	state->push();

	mBBox = SoXipPlot2AreaElement::getBBox( state );

	int numValues = value.getNum();
	mCoord->point.setNum( 2 * numValues );
	mLineSet->numVertices.setNum( numValues );

	if( type.getValue() == HORIZONTAL )
	{
		for( int i = 0; i < numValues; ++ i )
		{
			mCoord->point.set1Value(     2*i, SbVec3f( mBBox.getMin()[0], value[i], 0 ) );
			mCoord->point.set1Value( 1 + 2*i, SbVec3f( mBBox.getMax()[0], value[i], 0 ) );
			mLineSet->numVertices.set1Value( i, 2 );
		}
	}
	else
	{
		for( int i = 0; i < numValues; ++ i )
		{
			mCoord->point.set1Value(     2*i, SbVec3f( value[i], mBBox.getMin()[1], 0 ) );
			mCoord->point.set1Value( 1 + 2*i, SbVec3f( value[i], mBBox.getMax()[1], 0 ) );
			mLineSet->numVertices.set1Value( i, 2 );
		}
	}
	
	action->traverse( mCoord );
	action->traverse( mLineSet );

	state->pop();
}

void
SoXipPlot2Ruler::saveViewInformation( SoHandleEventAction* action )
{
	mViewportRegion = SoViewportRegionElement::get( action->getState() );

	mViewVolume = SoViewVolumeElement::get( action->getState() );	

	mPlaneProj.setViewVolume( mViewVolume );
	mPlaneProj.setPlane( mViewVolume.getPlane( mViewVolume.getNearDist() + 0.001 ) );
}

SbVec3f
SoXipPlot2Ruler::projectScreenOffsetToWorld( const SbVec2s& pixelOffset )
{
	SbVec2f normOffset = SbVec2f(
		pixelOffset[0] / (float) mViewportRegion.getViewportSizePixels()[0],
		pixelOffset[1] / (float) mViewportRegion.getViewportSizePixels()[1] );

	return mPlaneProj.project( normOffset ) - mPlaneProj.project( SbVec2f( 0, 0 ) );
}

void
SoXipPlot2Ruler::handleEvent( SoHandleEventAction* action )
{
	const SoEvent* event = action->getEvent();

	if( action->getGrabber() == this )
	{
		if( SO_MOUSE_RELEASE_EVENT( event, BUTTON1 ) )
		{
			action->releaseGrabber();
			action->setHandled();
		}
		else if( event->isOfType( SoLocation2Event::getClassTypeId() ) )
		{
			SbVec3f proj = mPlaneProj.project( event->getNormalizedPosition( mViewportRegion ) );

			if( type.getValue() == HORIZONTAL )
			{
				SoXipCursor::setCursor( "UPDOWN" );

				float val = proj[1];
				if( val < mBBox.getMin()[1] )
					val = mBBox.getMin()[1];
				else if( val > mBBox.getMax()[1] )
					val = mBBox.getMax()[1];

				value.set1Value( mSelectedValue, val );
			}
			else
			{
				SoXipCursor::setCursor( "LEFTRIGHT" );
				
				float val = proj[0];
				if( val < mBBox.getMin()[0] )
					val = mBBox.getMin()[0];
				else if( val > mBBox.getMax()[0] )
					val = mBBox.getMax()[0];

				value.set1Value( mSelectedValue, val );
			}

			action->setHandled();
		}
	}
	else if( !action->getGrabber() )
	{		
		saveViewInformation( action );

		if( SO_MOUSE_PRESS_EVENT( event, BUTTON1 ) )
		{
			SbVec3f proj = mPlaneProj.project( event->getNormalizedPosition( mViewportRegion ) );
			
			if( type.getValue() == HORIZONTAL )
			{
				float minDist = projectScreenOffsetToWorld( SbVec2s(0, 3) ).length();
				int numValues = value.getNum();
				for( int i = 0; i < numValues; ++ i )
				{
					if( fabs( proj[1] - value[i] ) < minDist )
					{
						action->setHandled();
						action->setGrabber( this );
						break ;
					}
				}
			}
			else if( type.getValue() == VERTICAL )
			{
				float minDist = projectScreenOffsetToWorld( SbVec2s(3, 0) ).length();
				int numValues = value.getNum();
				for( int i = 0; i < numValues; ++ i )
				{
					if( fabs( proj[0] - value[i] ) < minDist )
					{
						action->setHandled();
						action->setGrabber( this );
					}
				}
			}
		}
		else if( event->isOfType( SoLocation2Event::getClassTypeId() ) )
		{
			SbVec3f proj = mPlaneProj.project( event->getNormalizedPosition( mViewportRegion ) );
			
			if( type.getValue() == HORIZONTAL )
			{
				float minDist = projectScreenOffsetToWorld( SbVec2s(0, 3) ).length();
				int numValues = value.getNum();
				for( int i = 0; i < numValues; ++ i )
				{
					if( fabs( proj[1] - value[i] ) < minDist )
					{
						mSelectedValue = i;
						SoXipCursor::setCursor( "UPDOWN" );
						action->setHandled();
						break ;
					}
				}
			}
			else if( type.getValue() == VERTICAL )
			{
				float minDist = projectScreenOffsetToWorld( SbVec2s(3, 0) ).length();
				int numValues = value.getNum();
				for( int i = 0; i < numValues; ++ i )
				{
					if( fabs( proj[0] - value[i] ) < minDist )
					{
						mSelectedValue = i;
						SoXipCursor::setCursor( "LEFTRIGHT" );
						action->setHandled();
						break ;
					}
				}
			}
		}
	}
}
