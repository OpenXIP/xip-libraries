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
#include <Inventor/SbBox.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/elements/SoCacheElement.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include "SoXipOverlaySelectionFrame.h"
#include  <xip/inventor/overlay/SoXipManipulableShape.h>
#include <xip/inventor/overlay/XipOverlayUtils.h>
#include "geomutils.h"

SO_NODE_SOURCE( SoXipOverlaySelectionFrame );

SoXipOverlaySelectionFrame::SoXipOverlaySelectionFrame()
{
	SO_NODE_CONSTRUCTOR( SoXipOverlaySelectionFrame );

	mTopSeparator	= 0;
	mIsDragging		= FALSE;

	create();
}

SoXipOverlaySelectionFrame::~SoXipOverlaySelectionFrame()
{
	if( mTopSeparator )
		mTopSeparator->unref();
	mTopSeparator = 0;	
}

void
SoXipOverlaySelectionFrame::initClass()
{
	SO_NODE_INIT_CLASS( SoXipOverlaySelectionFrame,
		SoXipOverlayManipBase, "SoXipOverlayManipBase" );
}

void
SoXipOverlaySelectionFrame::create()
{
	SoDrawStyle* lineStyle = new SoDrawStyle;
	lineStyle->lineWidth.setValue(1);
	lineStyle->linePattern.setValue( 0xf0f0 );

	SoBaseColor* lineColor = new SoBaseColor;
	lineColor->rgb.setValue( 1, 1, 1 );

	int indices[6] = {0, 1, 2, 3, 0, -1};

	SoIndexedLineSet* lineIndices = new SoIndexedLineSet;
	lineIndices->coordIndex.setValues( 0, 6, indices );

	SoSeparator* lineSeparator = new SoSeparator;
	lineSeparator->addChild( lineStyle );
	lineSeparator->addChild( lineColor );
	lineSeparator->addChild( lineIndices );

 	mLinesCoords = new SoCoordinate3;	
	mLinesCoords->point.setNum(4);

	// Top Separator
	//
	mTopSeparator = new SoSeparator;
	mTopSeparator->addChild( mLinesCoords );
	mTopSeparator->addChild( lineSeparator );
	mTopSeparator->ref();
}

void
SoXipOverlaySelectionFrame::handleEvent( SoHandleEventAction* action )
{
	if( !on.getValue() )
		return ;

	SoXipOverlayManipBase::handleEvent( action );
	if( action->isHandled() )
		return ;

	
	if( SO_MOUSE_RELEASE_EVENT( action->getEvent(), BUTTON1 ) ) 
	{
		if( action->getGrabber() == this )
		{
			mIsDragging = FALSE;

			startNotify();

			action->releaseGrabber();
			action->setHandled();

			updateSelection();
		}
	}
	else if( action->getEvent()->isOfType( SoLocation2Event::getClassTypeId() ) )
	{
		SbVec3f newPoint;
		if( action->getGrabber() == this && getPoint( action, newPoint ) )
		{
			SbVec3f u = projectScreenOffsetToWorld( SbVec2s(1, 0) );
			SbVec3f v = projectScreenOffsetToWorld( SbVec2s(0, 1) );
	
			SbVec3f* points = mLinesCoords->point.startEditing();	

			SbVec3f pos[2];
			pos[0] = SbLine( newPoint, newPoint + u ).getClosestPoint( points[0] );
			pos[1] = SbLine( newPoint, newPoint + v ).getClosestPoint( points[0] );

			points[1] = pos[0];
			points[2] = newPoint;
			points[3] = pos[1];
			mLinesCoords->point.finishEditing();

			mIsDragging = TRUE;

			startNotify();

			action->setHandled();
		}		
	}
	else if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) )
	{
		SbVec3f newPoint;
		if( getPoint( action, newPoint ) )
		{
			mLinesCoords->point.set1Value( 0, newPoint );
			mLinesCoords->point.set1Value( 1, newPoint );
			mLinesCoords->point.set1Value( 2, newPoint );
			mLinesCoords->point.set1Value( 3, newPoint );
	
			action->setGrabber( this );
			action->setHandled();
		}		
	}
}

void
SoXipOverlaySelectionFrame::GLRender( SoGLRenderAction* action )
{
	if( !on.getValue() || mIsDragging == FALSE )
		return ;

	glPushAttrib( GL_ENABLE_BIT );
	glDisable( GL_DEPTH_TEST );

	mTopSeparator->GLRender( action );

	glPopAttrib();
}

void
SoXipOverlaySelectionFrame::updateSelection()
{
	if( mLinesCoords->point.getNum() != 4 )
	{
		SoDebugError::post( __FILE__, "Invalid number of points" );
		return ;
	}

	SoNodeList shapes = XipOverlayUtils::getManipulableShapes( mActionNode, FALSE );
	for( int i = 0; i < shapes.getLength(); ++ i )
	{
		SoXipManipulableShape* shape = (SoXipManipulableShape *) shapes[i];

		SbXfBox3f shapeXBox;
		shape->computeXBoundingBox( shapeXBox );

		SbXfBox3f selectionXBox;
		selectionXBox.setTransform( shapeXBox.getTransform() );
		selectionXBox.extendBy( mLinesCoords->point[0] );
		selectionXBox.extendBy( mLinesCoords->point[1] );
		selectionXBox.extendBy( mLinesCoords->point[2] );
		selectionXBox.extendBy( mLinesCoords->point[3] );

		SbVec3f selectionXMin, selectionXMax;
		selectionXBox.getBounds( selectionXMin, selectionXMax );

		SbVec3f shapeXMin, shapeXMax;
		shapeXBox.getBounds( shapeXMin, shapeXMax );

		SbBox2f selection2DBox ( 
			selectionXMin[0], selectionXMin[1], 
			selectionXMax[0], selectionXMax[1] );
		SbVec2f shapeMin( shapeXMin[0], shapeXMin[1] );
		SbVec2f shapeMax( shapeXMax[0], shapeXMax[1] );

		shape->select( selection2DBox.intersect( shapeMin ) && selection2DBox.intersect( shapeMax ) );
	}
}
