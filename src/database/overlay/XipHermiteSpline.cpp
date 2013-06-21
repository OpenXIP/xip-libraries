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
#include "XipHermiteSpline.h"

XipHermiteSpline::XipHermiteSpline( const SoMFVec3f& controlPoints, SbBool closed )
	: mClosed( closed )
{
	mControlPoints.copyFrom( controlPoints );
}

XipHermiteSpline::~XipHermiteSpline()
{

}

void
XipHermiteSpline::interpolateSegment( const SbVec3f& p0, const SbVec3f& p1,
									  const SbVec3f& m0, const SbVec3f& m1,
									  SbVec3f* curvePointPtr, int numPoints )
{
	float dt = 1.0f / (float) (numPoints - 1);
	float  t = 0;

	for( int i = 0; i < numPoints; ++ i, t += dt )
	{
		float t2 = t * t;
		float t3 = t * t2;

		float h00 =  2*t3 - 3*t2 + 1;
		float h10 =    t3 - 2*t2 + t;
		float h01 = -2*t3 + 3*t2;
		float h11 =    t3 - t2;

		*curvePointPtr ++ = h00 * p0 + h10 * m0 + h01 * p1 + h11 * m1;
	}
}

void
XipHermiteSpline::interpolateContour( int numPointsPerSegment, SoMFVec3f& output )
{
	int numControlPoints = mControlPoints.getNum();
	if( numControlPoints <= 2 )
	{
		output.setNum( numControlPoints );
		output.setValues( 0, numControlPoints, mControlPoints.getValues(0) );
		return ;
	}
	
	int numSegments = numControlPoints - 1;
	if( mClosed )
		++ numSegments;
	
	output.setNum( numSegments * numPointsPerSegment );

	SbVec3f* outputPtr = output.startEditing();
	for( int i = 0; i < numSegments; ++ i )
	{
		const SbVec3f* P[4];
		P[0] = &mControlPoints[ ( i + numControlPoints - 1 ) % numControlPoints ];
		P[1] = &mControlPoints[ i ];
		P[2] = &mControlPoints[ ( i + 1 ) % numControlPoints ];
		P[3] = &mControlPoints[ ( i + 2 ) % numControlPoints ];

		float d = (*P[2] - *P[1]).length();

		// When points are very close, the traditionnal tangent computation leads to
		// bad results. A looping artefact results from the fact that the tangent of
		// the first point is much longer than the segments we want to interpolate.
		// Therefore, the tangent length is set according to this segment distance.
		// The shorter the segment is, the shorter the tangent is.
		// That's why we need to remove points which are very close from each other,
		// to avoid division by zero (which would lead to huge tangents).
		//
		// default tangents equation:
		// T[i] = ½[P(i) - P(i-1)] + ½[P(i+1) - P(i)]
		//
		SbVec3f T[2] = {
			.5 * ( *P[2] - *P[1] ) + .5 * ( *P[1] - *P[0] ) * d / (*P[1] - *P[0]).length(),
			.5 * ( *P[2] - *P[1] ) + .5 * ( *P[3] - *P[2] ) * d / (*P[3] - *P[2]).length()
		};

		if( !mClosed && i == 0 )
		{
			T[0] = .5 * ( *P[2] - *P[1] );
		}
		else if( !mClosed && i == numControlPoints - 2 )
		{
			T[1] = .5 * ( *P[2] - *P[1] );
		}

		interpolateSegment( *P[1], *P[2], T[0], T[1], outputPtr, numPointsPerSegment );

		outputPtr += numPointsPerSegment;
	}
	output.finishEditing();
}
