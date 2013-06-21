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
*  @file	SoXipBox.h
*  @brief	Declaration of the SoXipBox ROI tool
*  @author	Julien Gein
**/

#ifndef SOXIPBOX_H
#define SOXIPBOX_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>

// Forward declarations
class SoGroup;
class SoCoordinate3;
class SbPlaneProjector;

/**
*	@class SoXipBox
*
* Tool used to draw a rectangular ROI. The output volume of interest
* is extracted from this ROI and a user given padding.
*
**/
class SoXipBox : public SoNode
{
	SO_NODE_HEADER( SoXipBox );

public:
	/// Constructor
	SoXipBox();

	/// Is the tool active ?
	SoSFBool			on;
	/// Enable/disable the display of the box center
	SoSFBool			showCenter;
	/// Output the box coordinates
	SoMFVec3f			point;
	/// Padding vector used to create a volume of interest from the ROI
	SoSFVec3f			padding;
	/// Output volume of interest
	SoSFMatrix			volumeOfInterest;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	virtual ~SoXipBox();

	/// Rendering method
	virtual void GLRender( SoGLRenderAction* action );

	/// Event handler method
	virtual void handleEvent( SoHandleEventAction* action );

	/// Box geometries separator
	SoGroup*			mSeparator;
	/// Box coordinates
	SoCoordinate3*		mCoords;
	/// Plane projector uesd to project mouse coordinates to world coordinates
	SbPlaneProjector*	mPlaneProj;
	/// View volume
	SbViewVolume		mViewVolume;
	/// Viewport
	SbViewportRegion	mViewport;
	/// Coordinates of the top-left corner of the box
	SbVec3f				mFirstCoordinates;
	/// Is the box being drawn ?
	SbBool				mDrawing;
};

#endif // SOXIPBOX_H
