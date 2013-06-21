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
*	@file	SoXipPlot2Legend.cpp
*	@brief	Implementation of the SoXipPlot2Legend class
*	@author	Julien Gein
**/

#include <xip/inventor/overlay/SoXipPlot2Element.h>
#include <xip/inventor/overlay/SbXipMarkerShapes.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include "SoXipPlot2Legend.h"

SO_NODE_SOURCE( SoXipPlot2Legend );

SoXipPlot2Legend::SoXipPlot2Legend()
{
	SO_NODE_CONSTRUCTOR( SoXipPlot2Legend );

	SO_NODE_DEFINE_ENUM_MARKER_VALUES( markerType );
	SO_NODE_SET_SF_ENUM_TYPE( marker, markerType );	

	SO_NODE_ADD_FIELD( label, ("") );
	SO_NODE_ADD_FIELD( lineWidth, (0) );
	SO_NODE_ADD_FIELD( linePattern, (0xffff) );
	SO_NODE_ADD_FIELD( lineColor, (SbColor(0.8, 0.8, 0.8)) );
	SO_NODE_ADD_FIELD( marker, (0) );
	SO_NODE_ADD_FIELD( markerSize, (0) );
	SO_NODE_ADD_FIELD( markerColor, (SbColor(0.8, 0.8, 0.8)) );
}

void 
SoXipPlot2Legend::initClass()
{
	SO_NODE_INIT_CLASS( SoXipPlot2Legend, SoNode, "Node" );

	// enable elements goes here
	SO_ENABLE( SoGLRenderAction, SoXipPlot2Element );
}

SoXipPlot2Legend::~SoXipPlot2Legend()
{

}

void 
SoXipPlot2Legend::GLRender( SoGLRenderAction* action )
{
	SoXipPlot2Element::add(action->getState(), this, label.getValue(),
		lineWidth.getValue(), linePattern.getValue(), lineColor.getValue(),
		marker.getValue(), markerSize.getValue(), markerColor.getValue());
}
