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
#include "SoXipOverlaySearch.h"
#include <xip/inventor/overlay/SoXipShape.h>
#include "SoXipShapeList.h"
#include <xip/inventor/overlay/XipOverlayUtils.h>

SO_NODE_SOURCE( SoXipOverlaySearch );

SoXipOverlaySearch::SoXipOverlaySearch()
{
	SO_NODE_CONSTRUCTOR( SoXipOverlaySearch );

	SO_NODE_ADD_FIELD( numNodesUpToContainer,     (1) );
	SO_NODE_ADD_FIELD(                 label,    ("") );
	SO_NODE_ADD_FIELD(                  type,    ("") );
	SO_NODE_ADD_FIELD(              selected, (FALSE) );
	SO_NODE_ADD_FIELD(             searchAll, (FALSE) );
	SO_NODE_ADD_FIELD(                search,      () );
	SO_NODE_ADD_FIELD(              overlays,     (0) );
	SO_NODE_ADD_FIELD(           numOverlays,     (0) );
	label.setNum(0);
	overlays.setNum(0);

	m_doSearch = FALSE;

	mSearchSensor = new SoFieldSensor( searchSensorCB, this );
	mSearchSensor->attach( &search );
}

SoXipOverlaySearch::~SoXipOverlaySearch()
{
	if( mSearchSensor )
	{
		delete mSearchSensor;
		mSearchSensor = 0;
	}
}

void
SoXipOverlaySearch::initClass()
{
	SO_NODE_INIT_CLASS( SoXipOverlaySearch, SoNode, "Node" );
}

void
SoXipOverlaySearch::searchSensorCB( void* userData, SoSensor* sensor )
{
  if(userData)
	{
	  ((SoXipOverlaySearch *) userData)->m_doSearch = TRUE;
	}
}

void
SoXipOverlaySearch::GLRender( SoGLRenderAction* action )
{
  doAction( action );
}

void
SoXipOverlaySearch::handleEvent( SoHandleEventAction* action )
{

	doAction( action );
}

SoNodeList
SoXipOverlaySearch::selectMatches( const SoNodeList& shapes )
{
	SoNodeList nodes = shapes;

	SbString classTypeName = type.getValue();
	if( classTypeName.getLength() )
	{
		SoType classType = SoType::fromName( classTypeName );
		if( classType.isBad() || !classType.isDerivedFrom(
														SoXipShape::getClassTypeId() ) )
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

SoNodeList
SoXipOverlaySearch::selectMatches( SoXipShapeList* shapeList )
{
	SoNodeList nodes;

	int numShapes = shapeList->getNumChildren();
	for( int i = 0; i < numShapes; ++ i )
		nodes.append( shapeList->getChild(i) );

	return selectMatches( nodes );
}

void
SoXipOverlaySearch::doAction( SoAction* action )
{
	if( !m_doSearch )
		return ;
	
	m_doSearch = FALSE;

	SoMFNode accum;

	const SoFullPath* path = (SoFullPath *) action->getCurPath();

	if( !path ) return;

	SoNodeList nodes = XipOverlayUtils::loadOverlaysFromNode( 
		path->getNodeFromTail( numNodesUpToContainer.getValue() ),
		searchAll.getValue() );

	int count = 0;

	for( int i = 0; i < nodes.getLength(); ++ i )
	{
		SoNodeList matches = selectMatches( (SoXipShapeList *) nodes[i] );
		if( matches.getLength() )
		{
			SoXipShapeList* newShapeList = new SoXipShapeList;
			newShapeList->ref();
			newShapeList->label.setValue( ((SoXipShapeList *)
															nodes[i])->label.getValue() );

			for( int j = 0; j < matches.getLength(); ++ j )			
				newShapeList->addChild( matches[j] );

			count += matches.getLength();
			
			accum.set1Value( accum.getNum(), newShapeList );
			newShapeList->unref();
		}
	}

	numOverlays.setValue( count );
	overlays.copyFrom( accum );
}


