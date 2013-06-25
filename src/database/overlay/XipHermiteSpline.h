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
*	@file	XipHermiteSpline.h
*	@brief	Contains the declaration of the HermiteSpline utility class.
*	@author	Julien Gein
*/
 
#ifndef XIPHERMITESPLINE_H
#define XIPHERMITESPLINE_H

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoMFVec3f.h>

/** 
*	@class XipHermiteSpline
*
* This class can be used to interpolate points given a segment and two
* tangents, or interpolate a contour given a set of control points
* (the tangents are in this case generated)
*
**/ 
class XipHermiteSpline
{
public:
    /// Constructor
	XipHermiteSpline( const SoMFVec3f& controlPoints, SbBool closed );

    /// Destructor
	~XipHermiteSpline();

    /** 
	*
    *	@brief Interpolate points along a given segment, represented by two control points.
    *
	* Interpolation is made so that the generated curve has in its two extremities, tangents
    * that match the tangents specified by the user.
    *
    *	@param p0           first control point
    *	@param p1           second control point
    *	@param m0           tangent associated to the first control point
    *	@param m1           tangent associated to the second control point
    *	@param pointsPtr    output point buffer
    *	@param numPoints    number of points to interpolate between p0 and p1 (both included)
    **/
	static void interpolateSegment( 
		const SbVec3f& p0, const SbVec3f& p1,
		const SbVec3f& m0, const SbVec3f& m1,
		SbVec3f* pointsPtr, int numPoints );

	 /** 
     *	@brief Interpolate a contour given a list of control points.
     *
     *  @param numPointsPerSegment	number of points per interpolated segment
     *  @param output				output contour
     */
	void interpolateContour( int numPointsPerSegment, SoMFVec3f& output );

protected:
    /// Spline control points
	SoMFVec3f		mControlPoints;

    /// Is the generated output contour closed ?
	SbBool			mClosed;

};

#endif // XIPHERMITESPLINE_H
