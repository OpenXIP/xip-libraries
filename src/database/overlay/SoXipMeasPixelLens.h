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
*	@file	SoXipMeasPixelLens.h
*	@brief	Declaration of the SoXipMeasPixelLens class
*	@author	Thomas Moeller
**/

#ifndef SOXIPMEASPIXELLENS_H
#define SOXIPMEASPIXELLENS_H

#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/SbViewportRegion.h> 
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include <Inventor/nodes/SoBaseColor.h>  
#include <Inventor/nodes/SoTranslation.h>  

class SbPlaneProjector;

/**
*	@class SoXipMeasPixelLens
*
* Read the voxel intensity at the location pointed at by the mouse.
* This coordinate node will also push an empty coordinate vector in
* the traversal state. Typically needed for seed points etc.
*
**/
class SoXipMeasPixelLens : public SoBaseKit
{
	SO_KIT_HEADER( SoXipMeasPixelLens );

	// Geometries
	SO_KIT_CATALOG_ENTRY_HEADER( separator );
	SO_KIT_CATALOG_ENTRY_HEADER( pickStyle );
	SO_KIT_CATALOG_ENTRY_HEADER( coordinate );
	SO_KIT_CATALOG_ENTRY_HEADER( pointset );
	SO_KIT_CATALOG_ENTRY_HEADER( translation );
	SO_KIT_CATALOG_ENTRY_HEADER( text );

public:
	/// Constructor
	SoXipMeasPixelLens();

	/// turn on/off the pixel lens
	SoSFBool			on;
	/// image where to read the intensities from
	SoXipSFDataImage	image;
	/// apply an offset to the read intensity ?
	SoSFInt32			offset;
	/// Current position analyzed by the pixel lens
	SoSFVec3f			position;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	virtual ~SoXipMeasPixelLens();

	virtual void GLRender( SoGLRenderAction* action );
	virtual void handleEvent( SoHandleEventAction* action );
	virtual void getBoundingBox( SoGetBoundingBoxAction* action );

	/// Return the voxel value at the given position
	virtual SbBool getVoxelValue( const SbVec3f& position, float& value );

	// Picked point information
	SbBool				mHasPickedPoint;
	SbBool				mHasPickedPointChanged;
	SbVec3f				mPickedPoint;

	// Shadow information (see SoXipDropShadowElement)
	SoBaseColor*		mShadowColor;
	SoTranslation*		mShadowTranslation;
};

#endif // SOXIPMEASPIXELLENS_H
