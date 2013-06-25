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
*	@file    SoXipOverlaySelectionFrame.h
*	@brief   Declaration of the SoXipOverlaySelectionFrame class
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYSELECTIONFRAME_H
#define SOXIPOVERLAYSELECTIONFRAME_H

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFShort.h>
#include <xip/inventor/overlay/SoXipOverlayManipBase.h>

/**
*	@class SoXipOverlaySelectionFrame
*
* Multiple selection tool. User can draws a semi-transparent box to select
* multiple shapes at once.
*
**/
class SoXipOverlaySelectionFrame : public SoXipOverlayManipBase
{
	SO_NODE_HEADER( SoXipOverlaySelectionFrame );

public:
	/// Constructor
	SoXipOverlaySelectionFrame();

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipOverlaySelectionFrame();

	/// Create the manipulator geometries (semi-transparent box)
	virtual void create();

	class SoSeparator*		mTopSeparator;
	class SoCoordinate3*	mLinesCoords;

	/// Retrieve the selected shapes and update their selection status
	virtual void updateSelection();

	virtual void GLRender( SoGLRenderAction* action );
	virtual void handleEvent( SoHandleEventAction* action );

	/// Is the user dragging ?
	SbBool					mIsDragging;
	
};

#endif // SOXIPOVERLAYSELECTIONFRAME_H
