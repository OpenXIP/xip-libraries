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
 *  \file	SbXipCoordinateTransform.h
 *  \brief	Utilities for coordinate manipulation
 *  \author	Thomas Moeller
 *  \author	Julien Gein
 *
 *  copyright (C) Siemens Corporate Research, Inc. 2007 All Rights Reserved
 */

#ifndef SBXIPCOORDINATETRANSFORM_H
#define SBXIPCOORDINATETRANSFORM_H

#include <xip/inventor/core/xipivcore.h>
#include <xip/inventor/core/SbXipImage.h>

/**
 *  \class XipWorldToImageConvert
 *
 *   This class can be used to convert 3D points to image coordinates (indices).
 *   As the translation component of the image model matrix corresponds to the
 *   center of the first voxel (0, 0, 0), a shift by half a voxel back needs to be
 *   done.
 *
 */
class XIPIVCORE_API XipWorldToImageConvert
{
public:
	/// Constructor
	XipWorldToImageConvert( const SbMatrix& imageModelMatrix,
		const SbXipImageDimensions& dimensions );

	/// Extract image coordinates from a point in world coordinates.
	/// Returns wheter the point belongs to the image or not.
	/// 
	SbBool getIndexTest( const SbVec3f& worldPt, SbVec3s& index ) const;

	/// Extract image coordinates from a point in world coordinates.
	/// 
	SbVec3s getIndex( const SbVec3f& worldPt ) const;

	/// Extract normalized image coordinates from a point in world coordinates.
	/// 
	SbVec3f getNormalizedPos( const SbVec3f& worldPt ) const;

protected:
	/// Inverse of the model matrix
	SbMatrix				mInvMatrix;

	/// Image dimensions
	SbXipImageDimensions	mDimensions;

};

/**
 *  \class XipImageToWorldConvert
 *
 *   This class can be used to convert image coordinates (indices) to 3D Points.
 *   As the translation component of the image model matrix corresponds to the
 *   center of the first voxel (0, 0, 0), a shift by half a voxel back needs to be
 *   done.
 *
 */
class XIPIVCORE_API XipImageToWorldConvert
{
public:
	/// Constructor
	XipImageToWorldConvert( const SbMatrix& imageModelMatrix,
		const SbXipImageDimensions& dimensions );

	/// Extract world coordinates from a point in image coordinates.
	/// 
	SbVec3f get3DPoint( const SbVec3f& index ) const;


protected:
	/// model matrix
	SbMatrix				mModelMatrix;

	/// Image dimensions
	SbXipImageDimensions	mDimensions;

};

#endif // SBXIPCOORDINATETRANSFORM_H
