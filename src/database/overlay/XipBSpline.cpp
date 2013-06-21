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
#include "XipBSpline.h"

XipBSpline::XipBSpline( const SoMFVec3f& controlPoints, int order, SbBool closed )
	: mOrder( order )
	, mClosed( closed )
	, mKnots( 0 )
{
	mControlPoints.copyFrom( controlPoints );
}

XipBSpline::~XipBSpline()
{
	if( mKnots )
	{
		delete mKnots;
		mKnots = 0;
	}
}

void
XipBSpline::computeKnots()
{
	if( mKnots )
		delete mKnots;	

	int numSegments = mControlPoints.getNum() - 1;

	mKnots = new int[ numSegments + mOrder + 1];

	for( int i = 0; i <= numSegments + mOrder; ++ i )
	{
		if( i < mOrder )
			mKnots[i] = 0;
		else if( mOrder <= i && i <= numSegments )
			mKnots[i] = i - mOrder + 1;
		else if( i > numSegments )
			mKnots[i] = numSegments - mOrder + 2;	
	}
}

double
XipBSpline::blend( int k, int order, double v )
{
	if( order == 1 )
	{
		if( mKnots[k] <= v && v < mKnots[k+1] )
			return 1;
		else
			return 0;
	}

	if( mKnots[k+order-1] == mKnots[k] && mKnots[k+order] == mKnots[k+1] )
		return 0;

	if( mKnots[k+order-1] == mKnots[k] )
		return (mKnots[k+order] - v) / (mKnots[k+order] - mKnots[k+1]) * blend( k+1, order-1, v );

	if( mKnots[k+order] == mKnots[k+1] )
		return (v - mKnots[k]) / (mKnots[k+order-1] - mKnots[k]) * blend( k, order-1, v );
	
	return (v - mKnots[k]) / (mKnots[k+order-1] - mKnots[k]) * blend( k, order-1, v ) + 
		(mKnots[k+order] - v) / (mKnots[k+order] - mKnots[k+1]) * blend( k+1, order-1, v );
}

SbVec3f
XipBSpline::interpolate( double value )
{
	int numSegments = mControlPoints.getNum() - 1;

	SbVec3f output(0, 0, 0);

	for( int k = 0; k <= numSegments; ++ k )
	{
		output += mControlPoints[k % mControlPoints.getNum() ] * blend( k, mOrder, value );
	}

	return output;
}

void
XipBSpline::interpolateContour( int numPointsPerSegment, SoMFVec3f& output )
{
	int numCP = mControlPoints.getNum();
	if( numCP <= 2 )
	{
		output.setNum( numCP );
		output.setValues( 0, numCP, mControlPoints.getValues(0) );
		return ;
	}

	computeKnots();
	
	int numSegments = numCP - 1;
	int numOutputs = numSegments * numPointsPerSegment;
	
	output.setNum( numOutputs );

	double increment = (double) (numSegments - mOrder + 2) / (numOutputs - 1);
	double u = 0;

	SbVec3f* outPtr = output.startEditing();

	for( int outputId = 0; outputId < numOutputs - 1; ++ outputId )
	{
		*outPtr ++ = interpolate(u);

		u += increment;
	}

	*outPtr = mControlPoints[ numSegments ];

	output.finishEditing();
}
