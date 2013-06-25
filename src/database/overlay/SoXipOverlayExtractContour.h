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
*	@file    SoXipOverlayExtractContour.h
*	@brief   Declaration of the SoXipOverlayExtractContour class
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYEXTRACTCONTOUR_H
#define SOXIPOVERLAYEXTRACTCONTOUR_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSFTrigger.h>

/**
*	@class SoXipOverlayExtractContour
*
* Extract a list of contour, defined by a list of point and a list of point
* index, from a list of overlay. Each contour is separated by -1 in the list
* of index.
*
**/
class SoXipOverlayExtractContour : public SoEngine
{
	SO_ENGINE_HEADER( SoXipOverlayExtractContour );

public:
	/// Constructor
	SoXipOverlayExtractContour();

	/// List of overlays
	SoMFNode		overlays;
	/// Extract the contour information
	SoSFTrigger		extract;

	/// Contour points (SoMFVec3f)
	SoEngineOutput	point;
	/// Contour indices (SoMFInt32)
	SoEngineOutput	coordIndex;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipOverlayExtractContour();

	/// Engines inputChanged method
	virtual void inputChanged( SoField* whichField );
	/// Engines evaluate method
	virtual void evaluate();

	/// Append the contour points and indices of one shape to a point
	/// and index accumulation buffers
	virtual void appendContour( class SoXipManipulableShape* shape,
		SoMFVec3f& accumulatePoint, SoMFInt32& accumulateCoordIndex );

};

#endif // SOXIPOVERLAYEXTRACTCONTOUR_H
