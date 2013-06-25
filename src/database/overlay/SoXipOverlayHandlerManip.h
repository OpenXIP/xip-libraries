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
*	@file    SoXipOverlayHandlerManip.h
*	@brief   Declaration of the SoXipOverlayHandlerManip class
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYHANDLERMANIP_H
#define SOXIPOVERLAYHANDLERMANIP_H

#include <xip/inventor/overlay/SoXipOverlayManipBase.h>

// Forward declarations
class SoDrawStyle;

/**
*	@class SoXipOverlayHandlerManip
*
* Manipulator that can manipulate one (and only one) instance of
* SoXipHandlerShape derived shape.
* This manipulator creates an handler point for each point returned
* by SoXipHandlerShape::getHandlerPoints().
* Those handlers can be dragged to set a new position
*
*	@see SoXipHandlerShape
*
**/
class SoXipOverlayHandlerManip : public SoXipOverlayManipBase
{
	SO_NODE_HEADER( SoXipOverlayHandlerManip );

public:
	/// Mode type
	enum ModeType
	{
		NONE,
		MOVE
	};
	
	/// Constructor
	SoXipOverlayHandlerManip();

	/// mode
	SoSFEnum			mode;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipOverlayHandlerManip();

	/// Create the manipulator geometries
	virtual void create();

	SoMatrixTransform*	mTransform;
	SoSeparator*		mControlPointsSeparator;
	SoCoordinate3*		mControlPointsCoords;
	SoDrawStyle*		mControlPointsStyle;

	virtual void GLRender( SoGLRenderAction* action );
	virtual void handleEvent( SoHandleEventAction* action );

	/// Return the id of the picked handler point, -1 if none
	virtual int pickControlPoint( SoHandleEventAction* action );

	/// id of the picked handler point
	int					mControlPointId;

};

#endif // SOXIPOVERLAYHANDLERMANIP_H
