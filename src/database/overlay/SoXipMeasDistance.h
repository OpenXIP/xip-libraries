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
*	@file	SoXipMeasDistance.h
*	@brief	Declaration of the SoXipMeasDistance class
*	@author	Thomas Moeller
**/

#ifndef SOXIPMEASDISTANCE_H
#define SOXIPMEASDISTANCE_H

#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/SbViewportRegion.h> 
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>  
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/nodes/SoBaseColor.h>  
#include <Inventor/nodes/SoTranslation.h>  

class SbPlaneProjector;

/**
*	@class SoXipMeasPixelLens
*
* Draw a line in the current view and display the actual distance
* This coordinate node will also push an empty coordinate vector in
* the traversal state. Typically needed for seed points etc.
*
**/
class SoXipMeasDistance : public SoBaseKit
{
	SO_KIT_HEADER( SoXipMeasDistance );

	// Geometries
	SO_KIT_CATALOG_ENTRY_HEADER( separator );
	SO_KIT_CATALOG_ENTRY_HEADER( coordinate );
	SO_KIT_CATALOG_ENTRY_HEADER( lineset );
	SO_KIT_CATALOG_ENTRY_HEADER( pointset );
	SO_KIT_CATALOG_ENTRY_HEADER( translation );
	SO_KIT_CATALOG_ENTRY_HEADER( text );

public:
	/// Location (where to get the points)
	enum locationType 
	{
		NEAR_PLANE,		//< on the near plane
		FOCAL_PLANE,	//< on the focal plane
		PICKING			//< through a pick action
	};

	/// Constructor
	SoXipMeasDistance();

	/// turn on/off the measure distance tool
	SoSFBool		on;
	/// location
	SoSFEnum		location;
	/// line points
	SoMFVec3f		point;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	virtual ~SoXipMeasDistance();

	virtual void GLRender( SoGLRenderAction* action );
	virtual void handleEvent( SoHandleEventAction* action );
	virtual void getBoundingBox( SoGetBoundingBoxAction* action );

	// View information
	SbPlaneProjector*	mPlaneProj;
	SbViewVolume		mViewVolume;
	SbViewportRegion	mViewport;
	float				mPixelSpacing;

	int					mPointToBeModified;
	SbVec3f				mLastMousePos;

	// Shadow information (see SoXipDropShadowElement)
	SoBaseColor*		mShadowColor;
	SoTranslation*		mShadowTranslation;
};


#endif // SOXIPMEASDISTANCE_H
