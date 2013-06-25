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
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include "SoXipOverlaySearchContour.h"
#include  <xip/inventor/overlay/SoXipManipulableShape.h>
#include "SoXipShapeList.h"
#include <xip/inventor/overlay/XipOverlayUtils.h>

SO_NODE_SOURCE( SoXipOverlaySearchContour );

SoXipOverlaySearchContour::SoXipOverlaySearchContour()
{
	SO_NODE_CONSTRUCTOR( SoXipOverlaySearchContour );

	// Inputs
	SO_NODE_ADD_FIELD( numNodesUpToContainer,       (1) );
	SO_NODE_ADD_FIELD(                 label,      ("") );
	SO_NODE_ADD_FIELD(                  type,      ("") );
	SO_NODE_ADD_FIELD(                closed,   (FALSE) );
	SO_NODE_ADD_FIELD(              selected,   (FALSE) );
	SO_NODE_ADD_FIELD(             searchAll,   (FALSE) );
	SO_NODE_ADD_FIELD(                search,        () );
	label.setNum(0);

	// Outputs
	SO_NODE_ADD_FIELD(                 point, (0, 0, 0) );
	SO_NODE_ADD_FIELD(            coordIndex,       (0) );
	point.setNum(0);
	coordIndex.setNum(0);

	m_doSearch = FALSE;

	mSearchSensor = new SoFieldSensor( searchSensorCB, this );
	mSearchSensor->attach( &search );
}

SoXipOverlaySearchContour::~SoXipOverlaySearchContour()
{
	if( mSearchSensor )
	{
		delete mSearchSensor;
		mSearchSensor = 0;
	}
}

void
SoXipOverlaySearchContour::initClass()
{
	SO_NODE_INIT_CLASS( SoXipOverlaySearchContour, SoNode, "Node" );
}

void
SoXipOverlaySearchContour::searchSensorCB( void* userData, SoSensor* sensor )
{
	((SoXipOverlaySearchContour *) userData)->m_doSearch = TRUE;
}

void
SoXipOverlaySearchContour::GLRender( SoGLRenderAction* action )
{
	doAction( action );
}

void
SoXipOverlaySearchContour::handleEvent( SoHandleEventAction* action )
{
	doAction( action );
}

SoNodeList
SoXipOverlaySearchContour::selectMatches( const SoNodeList& shapes )
{
	SoNodeList nodes = shapes;

	SbString classTypeName = type.getValue();
	if( classTypeName.getLength() )
	{
		SoType classType = SoType::fromName( classTypeName );
		if( classType.isBad() || !classType.isDerivedFrom( SoXipShape::getClassTypeId() ) )
		{
			SoDebugError::post( __FILE__, "Invalid Type" );
			return SoNodeList();
		}

		for( int i = 0; i < nodes.getLength(); ++ i )
		{
			if( ! nodes[i]->isOfType( classType ) )
				nodes.remove( i -- );				
		}
	}
	
	for( int labelIndex = 0; labelIndex < label.getNum(); ++ labelIndex )
	{
		const SbString& labelSearch = label[labelIndex];
		if( labelSearch.getLength() )
		{
			for( int i = 0; i < nodes.getLength(); ++ i )
			{
				SoXipShape* shape = (SoXipShape *) nodes[i];
				if( shape->label.find( labelSearch ) == -1 )
					nodes.remove( i -- );
			}
		}
	}

	if( selected.getValue() )
	{
		for( int i = 0; i < nodes.getLength(); ++ i )
		{
			SoXipShape* shape = (SoXipShape *) nodes[i];
			if( !shape->isSelected() )
				nodes.remove( i -- );
		}
	}

	return nodes;
}

void
SoXipOverlaySearchContour::doAction( SoAction* action )
{
	if( !m_doSearch )
		return ;
	
	m_doSearch = FALSE;

	const SoFullPath* path = (SoFullPath *) action->getCurPath();

	SoNodeList nodes = XipOverlayUtils::loadOverlaysFromNode( 
		path->getNodeFromTail( numNodesUpToContainer.getValue() ), 
		SoXipManipulableShape::getClassTypeId(),
		searchAll.getValue() );

	SoMFVec3f pointTmp;
	SoMFInt32 coordIndexTmp;

	SoNodeList matches = selectMatches( nodes );

	for( int i = 0; i < matches.getLength(); ++ i )
	{
		SoXipManipulableShape* shape = (SoXipManipulableShape *) matches[i];
		appendContour( shape, pointTmp, coordIndexTmp );
	}

	int numPoints  = pointTmp.getNum();
	int numIndices = coordIndexTmp.getNum();

	point.setNum( numPoints );
	coordIndex.setNum( numIndices );

	if( numPoints )
		point.setValues( 0, numPoints, pointTmp.getValues(0) );

	if( numIndices )
		coordIndex.setValues( 0, numIndices, coordIndexTmp.getValues(0) );
}

void 
SoXipOverlaySearchContour::appendContour( SoXipManipulableShape*
  shape, SoMFVec3f& accumulatePoint, SoMFInt32& accumulateCoordIndex )
{
	if( closed.getValue() && !shape->isClosed() )
		return ;

	int oldNumPoints = accumulatePoint.getNum();
	int oldNumIndices = accumulateCoordIndex.getNum();
	
	SoMFVec3f linePoints;
	SoMFInt32 lineIndices;
	SbBool closed;
	shape->extractGeometries( linePoints, lineIndices, closed );

	accumulatePoint.setValues( oldNumPoints, linePoints.getNum(),
								 	linePoints.getValues(0) );
	accumulateCoordIndex.setValues( oldNumIndices,
									lineIndices.getNum(), lineIndices.getValues(0) );

	int* indPtr = accumulateCoordIndex.startEditing();

  if( !indPtr )
	{
	  return;
	}

	indPtr += oldNumIndices;

  for( int i = 0; i < lineIndices.getNum(); ++ i, ++ indPtr )
	{
	  if( *indPtr != -1 )
		{
		  *indPtr += oldNumPoints;		
	  }
	}

	accumulateCoordIndex.finishEditing();
}


