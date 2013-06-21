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

#include <Inventor/SbLinear.h>
#include <xip/inventor/core/SbXipCoordinateTransform.h>


XipWorldToImageConvert::XipWorldToImageConvert( const SbMatrix& imageModelMatrix,
											    const SbXipImageDimensions& dimensions )
	: mDimensions( dimensions )
{
	mInvMatrix = imageModelMatrix.inverse();
}

SbBool
XipWorldToImageConvert::getIndexTest( const SbVec3f& worldPt, SbVec3s& index ) const
{
	SbVec3f index3f = getNormalizedPos( worldPt );

	index[0] = (int) ( .5 + index3f[0] * mDimensions[0] );
	index[1] = (int) ( .5 + index3f[1] * mDimensions[1] );
	index[2] = (int) ( .5 + index3f[2] * mDimensions[2] );

	return ( (index[0] >= 0) && (index[1] >= 0) && (index[2] >= 0) && 
		(index[0] < mDimensions[0]) && (index[1] < mDimensions[1]) && (index[2] < mDimensions[2]) );
}

SbVec3s
XipWorldToImageConvert::getIndex( const SbVec3f& worldPt ) const
{
	SbVec3f index3f = getNormalizedPos( worldPt );

	SbVec3s index;
	index[0] = (int) ( .5 + index3f[0] * mDimensions[0] );
	index[1] = (int) ( .5 + index3f[1] * mDimensions[1] );
	index[2] = (int) ( .5 + index3f[2] * mDimensions[2] );

	return index;
}

SbVec3f
XipWorldToImageConvert::getNormalizedPos( const SbVec3f& worldPt ) const
{
	SbVec3f index3f;
	mInvMatrix.multVecMatrix( worldPt, index3f );

	return index3f;
}

/////////////////////////////////////////////////////////////////////
XipImageToWorldConvert::XipImageToWorldConvert( const SbMatrix& imageModelMatrix,
											    const SbXipImageDimensions& dimensions )
	: mModelMatrix( imageModelMatrix ),
	  mDimensions( dimensions )
{
}

SbVec3f
XipImageToWorldConvert::get3DPoint( const SbVec3f& index ) const
{
	SbVec3f index3f; 
	index3f[0] = (float) ( (index[0] - .5) / mDimensions[0]);
	index3f[1] = (float) ( (index[1] - .5) / mDimensions[1]);
	index3f[2] = (float) ( (index[2] - .5) / mDimensions[2]);

	SbVec3f world3f;
	mModelMatrix.multVecMatrix(index3f, world3f);

	return world3f;
}
