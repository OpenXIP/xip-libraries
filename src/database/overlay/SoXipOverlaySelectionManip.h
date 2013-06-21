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
*	@file    SoXipOverlaySelectionManip.h
*	@brief   Declaration of the SoXipOverlaySelectionManip class
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYSELECTIONMANIP_H
#define SOXIPOVERLAYSELECTIONMANIP_H

#include <xip/inventor/overlay/SoXipOverlayManipBase.h>

/**
*	@class SoXipOverlaySelectionManip
*
* This class takes care of the shape selection. The Ctrl key
* can be pressed to add/ remove shape from the selection. As
* a shape needs to be selected to be translated, the selection
* manip cannot handle the action (trick).
*
**/
class SoXipOverlaySelectionManip : public SoXipOverlayManipBase
{
	SO_NODE_HEADER( SoXipOverlaySelectionManip );

public:
	/// Constructor
	SoXipOverlaySelectionManip();

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipOverlaySelectionManip();

	/// Event handler method
	virtual void handleEvent( SoHandleEventAction* action );

	/// Update the selection state of all the shapes found in the
	/// scene graph (up to numNodesUpToContainer).
	virtual void updateShapesStatus( SoHandleEventAction* action,
		SbBool unselect = TRUE, SbBool finishEditing = TRUE );

};

#endif // SOXIPOVERLAYSELECTIONMANIP_H
