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
*	@file	SoXipPlot2Extent.cpp
*	@brief	Implementation of the SoXipPlot2Extent class
*	@author	Julien Gein
**/

#include <Inventor/SbBox.h>
#include "SoXipPlot2Extent.h"

SO_NODE_SOURCE( SoXipPlot2Extent );

SoXipPlot2Extent::SoXipPlot2Extent()
{
	SO_NODE_CONSTRUCTOR( SoXipPlot2Extent );

	SO_NODE_ADD_FIELD( xRange, (0, 0) );
	SO_NODE_ADD_FIELD( yRange, (0, 0) );
}

SoXipPlot2Extent::~SoXipPlot2Extent()
{

}

void
SoXipPlot2Extent::initClass()
{
	SO_NODE_INIT_CLASS( SoXipPlot2Extent, SoShape, "Shape" );
}

void
SoXipPlot2Extent::generatePrimitives( SoAction* )
{

}

void
SoXipPlot2Extent::computeBBox( SoAction* action, SbBox3f& box, SbVec3f& center )
{
	SbVec2f xr = xRange.getValue();
	SbVec2f yr = yRange.getValue();

	if( xr[1] > xr[0] && yr[1] > yr[0] )
	{
		box.extendBy( SbVec3f(xr[0], yr[0], 0) );
		box.extendBy( SbVec3f(xr[1], yr[1], 0) );
	}
}
