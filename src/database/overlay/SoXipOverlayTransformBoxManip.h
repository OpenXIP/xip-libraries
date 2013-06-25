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
*	@file    SoXipOverlayTransformBoxManip.h
*	@brief   Declaration of the SoXipOverlayTransformBoxManip class
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYTRANSFORMBOXMANIP_H
#define SOXIPOVERLAYTRANSFORMBOXMANIP_H

#include <Inventor/SbBox.h>
#include <xip/inventor/overlay/SoXipOverlayManipBase.h>

/**
*	@class SoXipOverlayTransformBoxManip
*
* Compute the in-plane bounding box of the current selection, and
* display handler points in the 8 corners. Those handlers can be used
* to apply a scaling to the selected shapes when no key specifiers are
* pressed. When shift is pressed the 4 corners can be used to apply a 
* rotation around the normal axis.
*
**/
class SoXipOverlayTransformBoxManip : public SoXipOverlayManipBase
{
	SO_NODE_HEADER( SoXipOverlayTransformBoxManip );

public:
	/// Mode of the manipulator
	enum ModeType
	{
		NONE,
		ROTATION,
		SCALE
	};

	/// Constructor
	SoXipOverlayTransformBoxManip();

	/// mode of the manipulator
	SoSFEnum		mode;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipOverlayTransformBoxManip();

	/// Create the manipulator geometries (handlers)
	virtual void create();

	class SoSwitch*				mControlPointsSwitch;
	class SoCoordinate3*		mControlPointsCoords;
	class SoDrawStyle*			mControlPointsStyle;

	class SoMatrixTransform*	mBBoxTransform;

	virtual void handleEvent( SoHandleEventAction* action );

	/// Scale the selected shapes given the last user mouse interactions
	virtual void scale( SoHandleEventAction* action );

	/// Rotate the selected shapes given the last user mouse interactions
	virtual void rotate( SoHandleEventAction* action );

	/// Return the id of the picked handler point, -1 if none were picked
	virtual int pickControlPoint( SoHandleEventAction* action );

	/// Id of the lastly picked handler point
	int							mControlPointId;

	virtual void GLRender( SoGLRenderAction* action );

	/// Compute the in-plane bouding box of the selected shapes
	virtual SbBool computeSelectionXBoundingBox( SoGLRenderAction* action );

	/// In-plane bouding box of the selected shapes
	SbXfBox3f					mXBoundingBox;	

};

#endif // SOXIPOVERLAYTRANSFORMBOXMANIP_H
