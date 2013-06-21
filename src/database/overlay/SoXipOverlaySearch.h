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
*	@file    SoXipOverlaySearch.h
*	@brief   Declaration of the SoXipOverlaySearch class
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYSEARCH_H
#define SOXIPOVERLAYSEARCH_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFTrigger.h>

/**
*	@class SoXipOverlaySearch
*
* Overlay search engine. Retrieve a list of overlays
* from the specified scene graph and given some search criteria.
*
**/
class SoXipOverlaySearch : public SoNode
{
	SO_NODE_HEADER( SoXipOverlaySearch );

public:
	/// Constructor
	SoXipOverlaySearch();

	/// number of nodes upward where to start the search action
	SoSFShort		numNodesUpToContainer;
	/// shapes should match given label, if not "" 
	SoMFString		label;
	/// shapes class name should match given type, if not "" 
	SoSFString		type;
	/// shoudl the shapes be closed ? 
	SoSFBool		closed;
	/// should the shapes be selected ? 
	SoSFBool		selected;
	/// should the search action goes trough kits and groups ?
	SoSFBool		searchAll;
	/// perform the search action
	SoSFTrigger		search;

	/// list of found overlays
	SoMFNode		overlays;
	/// Number of overlay found
	SoSFInt32		numOverlays;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipOverlaySearch();

	virtual void GLRender( SoGLRenderAction* action );
	virtual void handleEvent( SoHandleEventAction* action );
	virtual void doAction( SoAction* action );

	/// Select the matching shapes from a list of nodes
	virtual SoNodeList selectMatches( const SoNodeList& shapes );
	/// Select the matching shapes from a list of shapes
	virtual SoNodeList selectMatches( class SoXipShapeList* shapeList );

	/// Should the search be performed ?
	SbBool			m_doSearch;

private:
	static void searchSensorCB( void* userData, SoSensor* sensor );

	SoFieldSensor*	mSearchSensor;
};

#endif // SOXIPOVERLAYSEARCH_H
