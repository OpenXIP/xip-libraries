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
*	@file    SoXipOverlaySearchContour.h
*	@brief   Declaration of the SoXipOverlaySearchContour class
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYSEARCHCONTOUR_H
#define SOXIPOVERLAYSEARCHCONTOUR_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFInt32.h>

/**
*	@class SoXipOverlaySearchContour
*
* Contour search engine. Retrieve a list of point and indices
* from the specified scene graph and given some search criteria.
* This is equivalent to SoXipOverlaySearchContour followed by
* SoXipOverlayExtractContour.
*
*	@see SoXipOverlaySearchContour
*	@see SoXipOverlayExtractContour
**/
class SoXipOverlaySearchContour : public SoNode
{
	SO_NODE_HEADER( SoXipOverlaySearchContour );

public:
	/// Constructor
	SoXipOverlaySearchContour();

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

	/// list of point extracted from matching shapes
	SoMFVec3f		point;
	/// list of point indices, defining multiple contours, extracted from
	/// matching shapes
	SoMFInt32		coordIndex;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipOverlaySearchContour();

	virtual void GLRender( SoGLRenderAction* action );
	virtual void handleEvent( SoHandleEventAction* action );
	virtual void doAction( SoAction* action );

	/// Select the matching shapes from a list of nodes
	virtual SoNodeList selectMatches( const SoNodeList& shapes );

	/// Append the geometries of a shape to a point and index accumulation
	/// buffers
	virtual void appendContour( class SoXipManipulableShape* shape,
		SoMFVec3f& accumulatePoint, SoMFInt32& accumulateCoordIndex );

	/// Should the search be performed ?
	SbBool			m_doSearch;

private:
	static void searchSensorCB( void* userData, SoSensor* sensor );

	SoFieldSensor*	mSearchSensor;
};

#endif // SOXIPOVERLAYSEARCHCONTOUR_H
