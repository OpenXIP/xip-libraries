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
*	@file	SoXipPlot2Samples.cpp
*	@brief	Implementation of the SoXipPlot2Samples class
*	@author	Julien Gein
**/

#include <xip/inventor/overlay/SoXipPlot2Element.h>
#include <xip/inventor/overlay/SoXipPlot2AreaElement.h>
#include <xip/inventor/overlay/SbXipMarkerShapes.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/elements/SoPointSizeElement.h>
#include <Inventor/elements/SoLineWidthElement.h>
#include <Inventor/elements/SoLinePatternElement.h>
#include <Inventor/elements/SoDrawStyleElement.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include "SoXipPlot2Samples.h"
#include "XipBSpline.h"
#include "XipHermiteSpline.h"

SO_KIT_SOURCE( SoXipPlot2Samples );

SoXipPlot2Samples::SoXipPlot2Samples()
{
	SO_KIT_CONSTRUCTOR( SoXipPlot2Samples );

	/// Define the kit structure

	SO_KIT_ADD_CATALOG_ENTRY( mMainSeparator, SoSeparator, TRUE, this, \x0, TRUE );

	SO_KIT_ADD_CATALOG_ENTRY( mMarkerSeparator, SoSeparator, FALSE, mMainSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mMarkerMaterial, SoMaterial, FALSE, mMarkerSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mMarkerCoord, SoCoordinate3, FALSE, mMarkerSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mMarkerSet, SoXipMarkerSet, FALSE, mMarkerSeparator, \x0, FALSE );

	/// Define fields

	SO_NODE_DEFINE_ENUM_MARKER_VALUES( markerEnumType );
	SO_NODE_SET_SF_ENUM_TYPE( markerType, markerEnumType );	

	SO_NODE_ADD_FIELD( label, ("Line" ) );
	SO_NODE_ADD_FIELD( data, (0, 0) );	
	SO_NODE_ADD_FIELD( markerType, (0) );
	SO_NODE_ADD_FIELD( markerColor, (0, 0, 0) );
	SO_NODE_ADD_FIELD( markerTransparency, (0) );

	SO_KIT_INIT_INSTANCE();

	mDataSensors[0] = new SoFieldSensor( dataSensorCB, this );
	mDataSensors[0]->attach( &data );

	setUpConnections( TRUE, TRUE );
}

void 
SoXipPlot2Samples::initClass()
{
	SO_KIT_INIT_CLASS( SoXipPlot2Samples, SoBaseKit, "BaseKit" );

	SO_ENABLE( SoGLRenderAction, SoXipPlot2Element );
}

SoXipPlot2Samples::~SoXipPlot2Samples()
{
	if( mDataSensors[0] )
	{
		delete mDataSensors[0];
		mDataSensors[0] = 0;
	}
}

SbBool
SoXipPlot2Samples::setUpConnections( SbBool onOff, SbBool doItAlways )
{
    if( !doItAlways && connectionsSetUp == onOff )
		return onOff;

	try
	{
		if ( onOff )
		{
			// We connect AFTER base class.
			SoBaseKit::setUpConnections( onOff, FALSE );

			SoXipMarkerSet* markers = SO_GET_ANY_PART( this, "mMarkerSet", SoXipMarkerSet );
			if( markers )
			{
				markers->marker.connectFrom( &markerType );
			}

			SoMaterial* markerMaterial = SO_GET_ANY_PART( this, "mMarkerMaterial", SoMaterial );
			if( markerMaterial )
			{
				markerMaterial->diffuseColor.connectFrom( &markerColor );
				markerMaterial->transparency.connectFrom( &markerTransparency );
			}
		}
		else
		{
			SoXipMarkerSet* markers = SO_GET_ANY_PART( this, "mMarkerSet", SoXipMarkerSet );
			if( markers )
			{
				markers->marker.disconnect();
			}

			SoMaterial* markerMaterial = SO_GET_ANY_PART( this, "mMarkerMaterial", SoMaterial );
			if( markerMaterial )
			{
				markerMaterial->diffuseColor.disconnect();
				markerMaterial->transparency.disconnect();
			}

			SoBaseKit::setUpConnections( onOff, FALSE );
		}
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Cannot setup connections" );
		return true;
	}

    return !( connectionsSetUp = onOff );
}

void 
SoXipPlot2Samples::getBoundingBox( SoGetBoundingBoxAction* action )
{
	if( data.getNum() )
	{
		SoBaseKit::getBoundingBox( action );
	}
}

void 
SoXipPlot2Samples::GLRender( SoGLRenderAction* action )
{
	if( data.getNum() )
	{
		//float pointSize = SoPointSizeElement::get( action->getState() );
		//float lineWidth = SoLineWidthElement::get( action->getState() );
		//unsigned short linePattern = SoLinePatternElement::get( action->getState() );

		SoXipPlot2Element::add(
			action->getState(),
			this,
			label.getValue(),
			markerType.getValue(), markerColor.getValue() );

		SoState* state = action->getState();
		
		state->push();

		// Make sure the DrawStyle is set to FILLED
		SoDrawStyleElement::set( state, SoDrawStyleElement::FILLED ); 

		SoBaseKit::GLRender( action );

		state->pop();
	}
}

void
SoXipPlot2Samples::dataSensorCB( void* userData, SoSensor* )
{
	SoXipPlot2Samples* plot = (SoXipPlot2Samples *) userData;

	plot->extractMarkerCoords();
}

void
SoXipPlot2Samples::extractMarkerCoords()
{
	SoCoordinate3* markerCoord = SO_GET_ANY_PART( this, "mMarkerCoord", SoCoordinate3 );
	if( markerCoord )
	{
		int numCoord = data.getNum();
		markerCoord->point.setNum( numCoord );
		
		SbVec3f* verticesPtr = markerCoord->point.startEditing();
		for( int i = 0; i < numCoord; ++ i )
		{
			verticesPtr[i] = SbVec3f( data[i][0], data[i][1], 0 );
		}
		markerCoord->point.finishEditing();
	}
}

