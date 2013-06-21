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
*	@file	SoXipPlot2Grid.cpp
*	@brief	Implementation of the SoXipPlot2Grid class
*	@author	Julien Gein
**/

#include <xip/inventor/overlay/SoXipPlot2AreaElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoLineSet.h>
#include "SoXipPlot2Grid.h"

SO_NODE_SOURCE( SoXipPlot2Grid );

SoXipPlot2Grid::SoXipPlot2Grid()
{
	SO_NODE_CONSTRUCTOR( SoXipPlot2Grid );

	mCoord = new SoCoordinate3;
	mLineSet = new SoLineSet;
}

SoXipPlot2Grid::~SoXipPlot2Grid()
{

}

void
SoXipPlot2Grid::initClass()
{
	SO_NODE_INIT_CLASS( SoXipPlot2Grid, SoNode, "Node" );
}

void
SoXipPlot2Grid::GLRender( SoGLRenderAction* action )
{	
	int i, j;
	SbBox3f plotArea = SoXipPlot2AreaElement::getBBox( action->getState() );

	float minX, maxX, minY, maxY;
	minX = plotArea.getMin()[0];
	maxX = plotArea.getMax()[0];
	minY = plotArea.getMin()[1];
	maxY = plotArea.getMax()[1];

	int xNumTicks;
	float xStartTick, xTickSpacing;
	SoXipPlot2AreaElement::getXTick( action->getState(), xStartTick, xTickSpacing, xNumTicks );

	int yNumTicks;
	float yStartTick, yTickSpacing;
	SoXipPlot2AreaElement::getYTick( action->getState(), yStartTick, yTickSpacing, yNumTicks );

	// Set the number of vertices for each line
	mLineSet->numVertices.setNum( xNumTicks + yNumTicks );
	for( j = 0; j < xNumTicks + yNumTicks; ++ j )
	{
		mLineSet->numVertices.set1Value( j, 2 );
	}

	mCoord->point.setNum( 2 * ( xNumTicks + yNumTicks) );	

	SbVec3f* coordPtr = mCoord->point.startEditing();
	
	float currentTick;

	// Push vertical lines vertices
	currentTick = xStartTick;	
	for( i = 0; i < xNumTicks; ++ i )
	{
		*coordPtr ++ = SbVec3f( currentTick, minY, 0 );
		*coordPtr ++ = SbVec3f( currentTick, maxY, 0 );

		currentTick += xTickSpacing;
	}

	// Push horizontal lines vertices
	currentTick = yStartTick;
	for( i = 0; i < yNumTicks; ++ i )	
	{
		*coordPtr ++ = SbVec3f( minX, currentTick, 0 );
		*coordPtr ++ = SbVec3f( maxX, currentTick, 0 );

		currentTick += yTickSpacing;
	}

	mCoord->point.finishEditing();


	// Render the grid
	action->getState()->push();

	action->traverse( mCoord );
	action->traverse( mLineSet );

	action->getState()->pop();
}
