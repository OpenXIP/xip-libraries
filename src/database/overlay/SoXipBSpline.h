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
*	@file    SoXipBSpline.h
*	@brief   Interactive B-Spline tool
*	@author  Julien Gein
**/

#ifndef SOXIPBSPLINE_H
#define SOXIPBSPLINE_H

#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFInt32.h>
#include "SoXipPolygon.h"

/**
*  @class SoXipBSpline
*  This node is used to create/ edit a b-spline contour.
*  It is a permanent overlay. User may use multiple instances of this node
*  to perform multiple measures, or use this class as a parameter of the
*  overlay manager (cf. SoXipOverlayManager)
*
*  @see SoXipOverlayManager
*
**/
class SoXipBSpline : public SoXipPolygon
{
	SO_NODE_HEADER( SoXipBSpline );

public:
    /// Constructor
	SoXipBSpline();

	/// Order of the spline
	SoSFShort		degree;
    /// Number of interpolated points between two control points
	SoSFInt32		alpha;

    /// Open Inventor class initialization
	static void initClass();

protected:
    /// Destructor
	~SoXipBSpline();

	/**
    *   @brief  Callback function called before the shape creation
    *
    **/
	virtual void beforeCreation();

	/**
    *   @brief  Extract spline geometries
    *
    * This method is called by the base class to retrieve the points and segments
    * defining the spline. 
    *
    *   @param point		output array of points
    *   @param coordIndex   output array of point indices
	*	@param closed		is the shape closed?
	*
    **/	
	virtual void extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed );

	/**
    *   @brief  Map a displayed line index to its preceding control point.
	*
    * This method is called when the b-spline is edited and a control point
	* needs to be added. The editor only knows about the extracted point, not
	* the control points.
    *
    *   @param id	index 
	*
	*	@return	index of the preceding control point
	**/
	virtual int getPreviousControlPoint( int id ) const;

};

#endif // SOXIPBSPLINE_H
