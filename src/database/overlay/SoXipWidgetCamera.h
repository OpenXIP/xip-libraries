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
*	@file    SoXipWidgetCamera.h
*	@brief   Simple camera for 2D objects (preserve scale)
*	@author  Julien Gein
**/

#ifndef SOXIPWIDGETCAMERA_H
#define SOXIPWIDGETCAMERA_H

#include <xip/inventor/core/SoXipSubKit.h>
#include <Inventor/SbViewportRegion.h> 
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/projectors/SbPlaneProjector.h>

/**
*	@class SoXipWidgetCamera
*
* Simple camera for 2D objects (preserve scale)
*
**/
class SoXipWidgetCamera : public SoXipKit
{
	SO_NODE_HEADER( SoXipWidgetCamera );

	SO_XIP_KIT_TYPE_ENTRY_HEADER( mCamera, SoOrthographicCamera );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mScale, SoScale );

public:
	/// Constructor
	SoXipWidgetCamera();

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	virtual ~SoXipWidgetCamera();

	/**
	*	@brief	Compute the scale factor used to keep the menu size constant, independently
	* of the viewport size and aspect ratio
	*
	**/
	virtual void updateScale();

	virtual void GLRender( SoGLRenderAction* action );
	virtual void handleEvent( SoHandleEventAction* action );	
	
	/**
	*	@brief	Save the view information
	*
	**/
	virtual void saveViewInformation( SoAction* action );

	// View information
	SbPlaneProjector*		mPlaneProj;
	SbViewVolume			mViewVolume;
	SbViewportRegion		mViewport;
	SbVec2s					mViewportSize;

};

#endif // SOXIPWIDGETCAMERA_H
