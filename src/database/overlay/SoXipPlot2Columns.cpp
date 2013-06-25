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
*	@file	SoXipPlot2Columns.cpp
*	@brief	Implementation of the SoXipPlot2Columns class
*	@author	Julien Gein
**/

#include <xip/inventor/overlay/SoXipPlot2Element.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include "SoXipPlot2Columns.h"

SO_KIT_SOURCE( SoXipPlot2Columns );

SoXipPlot2Columns::SoXipPlot2Columns()
{
	SO_KIT_CONSTRUCTOR( SoXipPlot2Columns );

	SO_KIT_ADD_CATALOG_ENTRY( mMainSeparator, SoSeparator, FALSE, this, \x0, TRUE );

	SO_KIT_ADD_CATALOG_ENTRY( mVertices, SoCoordinate3, FALSE, mMainSeparator, \x0, FALSE );

	SO_KIT_ADD_CATALOG_ENTRY( mFaceSeparator, SoSeparator, FALSE, mMainSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mFaceMaterial, SoMaterial, FALSE, mFaceSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mFaces, SoFaceSet,  FALSE, mFaceSeparator, \x0, FALSE );

	SO_KIT_ADD_CATALOG_ENTRY( mBorderSeparator, SoSeparator,  FALSE, mMainSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mBorderColor, SoBaseColor,  FALSE, mBorderSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mBorderStyle, SoDrawStyle,  FALSE, mBorderSeparator, \x0, FALSE );
	SO_KIT_ADD_CATALOG_ENTRY( mBorderLines, SoLineSet,  FALSE, mBorderSeparator, \x0, FALSE );

	SO_NODE_ADD_FIELD( label, ("Columns") );
	SO_NODE_ADD_FIELD( data, (0) );
	data.setNum(0);
	SO_NODE_ADD_FIELD( faceColor, (0.2, 0.2, 0.2) );
	SO_NODE_ADD_FIELD( faceTransparency, (0) );
	SO_NODE_ADD_FIELD( borderColor, (0, 0, 0) );
	SO_NODE_ADD_FIELD( borderWidth, (1) );

	SO_KIT_INIT_INSTANCE();
	
	setVertices();

	mDataSensor = new SoFieldSensor( dataSensorCB, this );
	mDataSensor->attach( &data );

	setUpConnections( TRUE, TRUE );
}

void 
SoXipPlot2Columns::initClass()
{
	SO_KIT_INIT_CLASS( SoXipPlot2Columns, SoBaseKit, "BaseKit" );
}

SoXipPlot2Columns::~SoXipPlot2Columns()
{
	if( mDataSensor )
	{
		delete mDataSensor;
		mDataSensor = 0;
	}
}

void
SoXipPlot2Columns::dataSensorCB( void* userData, SoSensor* )
{
	((SoXipPlot2Columns *) userData)->setVertices();
}

SbBool
SoXipPlot2Columns::setUpConnections( SbBool onOff, SbBool doItAlways )
{
    if( !doItAlways && connectionsSetUp == onOff )
		return onOff;

	try
	{
		if ( onOff )
		{
			// We connect AFTER base class.
			SoBaseKit::setUpConnections( onOff, FALSE );

			SoMaterial* faceMaterial = SO_GET_ANY_PART( this, "mFaceMaterial", SoMaterial );
			if( faceMaterial )
			{
				faceMaterial->diffuseColor.connectFrom( &faceColor );
				faceMaterial->transparency.connectFrom( &faceTransparency );
			}

			SoBaseColor* borderBaseColor = SO_GET_ANY_PART( this, "mBorderColor", SoBaseColor );
			if( borderBaseColor )
			{
				borderBaseColor->rgb.connectFrom( &borderColor );
			}

			SoDrawStyle* borderStyle = SO_GET_ANY_PART( this, "mBorderStyle", SoDrawStyle );
			if( borderStyle )
			{
				borderStyle->lineWidth.connectFrom( &borderWidth );
			}
		}
		else
		{
			SoMaterial* faceMaterial = SO_GET_ANY_PART( this, "mFaceMaterial", SoMaterial );
			if( faceMaterial )
			{
				faceMaterial->diffuseColor.disconnect();
				faceMaterial->transparency.disconnect();
			}

			SoBaseColor* borderBaseColor = SO_GET_ANY_PART( this, "mBorderColor", SoBaseColor );
			if( borderBaseColor )
			{
				borderBaseColor->rgb.disconnect();
			}

			SoDrawStyle* borderStyle = SO_GET_ANY_PART( this, "mBorderStyle", SoDrawStyle );
			if( borderStyle )
			{
				borderStyle->lineWidth.disconnect();
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
SoXipPlot2Columns::setVertices()
{
	SoCoordinate3* vertices = SO_GET_ANY_PART( this, "mVertices", SoCoordinate3 );
	SoFaceSet* faces = SO_GET_ANY_PART( this, "mFaces", SoFaceSet );
	SoLineSet* lines = SO_GET_ANY_PART( this, "mBorderLines", SoLineSet );

	if( vertices && faces && lines )
	{
		int numData = data.getNum();

		vertices->point.setNum( 4 * numData );	
		faces->numVertices.setNum( numData );
		lines->numVertices.setNum( numData );

		SbVec3f* verticesPtr = vertices->point.startEditing();
		for( int i = 0; i < numData; ++ i )
		{
			verticesPtr[4*i    ] = SbVec3f( i + .9,       0, 0 );			
			verticesPtr[4*i + 1] = SbVec3f( i + .9, data[i], 0 );
			verticesPtr[4*i + 2] = SbVec3f( i + .1, data[i], 0 );
			verticesPtr[4*i + 3] = SbVec3f( i + .1,       0, 0 );			

			faces->numVertices.set1Value( i, 4 );
			lines->numVertices.set1Value( i, 4 );
		}
		vertices->point.finishEditing();	
	}
}

void
SoXipPlot2Columns::GLRender( SoGLRenderAction* action )
{
	SoXipPlot2Element::add(
		action->getState(),
		this,
		label.getValue(),
		borderColor.getValue(),
		faceColor.getValue() );

	SoState* state = action->getState();
	
	state->push();

	// Make sure the DrawStyle is set to FILLED
	SoDrawStyleElement::set( state, SoDrawStyleElement::FILLED ); 

	SoBaseKit::GLRender( action );

	state->pop();
}
