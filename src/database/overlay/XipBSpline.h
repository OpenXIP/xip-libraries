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
 *  @file	XipBSpline.h
 *  @brief	Contains the declaration of the BSpline utility class.
 *  @author	Julien Gein
 *
 */
 
#ifndef XIPBSPLINE_H
#define XIPBSPLINE_H

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoMFVec3f.h>

/** 
*	@class XipBSpline
*
* This class can be used to interpolate a contour given a list of 
* control points, using a B-spline interpolation.
* Use of this class can be curve fitting (interpolated contour points 
* will not pass by the control points), contour representation, etc.
*
**/ 
class XipBSpline
{
public:
    /// Constructor
	XipBSpline( const SoMFVec3f& controlPoints, int order, SbBool closed );

    /// Destructor
	~XipBSpline();

	 /** 
     *	@brief Interpolate a contour given a list of control points.
     *
     *  @param numPointsPerSegment	number of points per interpolated segment
     *  @param output				output contour
     **/
	void interpolateContour( int numPointsPerSegment, SoMFVec3f& output );
	
protected:
    /// Compute the knot vector
	void computeKnots();

    /// Compute the blend factor
	double blend( int k, int order, double v );

    /// Compute curve point at the given location
	SbVec3f interpolate( double value );

    /// spline control points
	SoMFVec3f		mControlPoints;

    /// Order of the spline
	int				mOrder;

    /// Is the generated output contour closed ?
	SbBool			mClosed;

    /// Knot vector
	int*			mKnots;

};

#endif // XIPBSPLINE_H
