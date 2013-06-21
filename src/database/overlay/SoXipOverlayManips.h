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
*	@file    SoXipOverlayManips.h
*	@brief   Declaration of the SoXipOverlayManips class
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYMANIPS_H
#define SOXIPOVERLAYMANIPS_H

#include <xip/inventor/core/SoXipSubKit.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFBool.h>

/**
*	@class SoXipOverlayManips
*
* Kit that groups all the Xip overlay manipulators. As the
* manipulators all deal with events (mouse interaction), the order
* matters a lot. This kit makes easy to use overlay manipulators.
*
**/
class SoXipOverlayManips : public SoXipKit
{
	SO_NODE_HEADER( SoXipOverlayManips );

	SO_XIP_KIT_ENTRY_HEADER( mTopSeparator );

	// Manipulators
	SO_XIP_KIT_ENTRY_HEADER( mHandlerManip );
	SO_XIP_KIT_ENTRY_HEADER( mTransformBox );
	SO_XIP_KIT_ENTRY_HEADER( mSelectionManip );
	SO_XIP_KIT_ENTRY_HEADER( mTranslationManip );
	SO_XIP_KIT_ENTRY_HEADER( mSelectionFrame );

public:
	/// Constructor
	SoXipOverlayManips();

	/// Number of nodes upward where overlay manipulators can start
	/// searching for overlays.
	SoSFShort	numNodesUpToContainer;
	/// activate / disactivate the selection frame manipulator
	SoSFBool	multipleSelection;

	/// enable / disable selection
	SoSFBool  enableSelection;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipOverlayManips();

};

#endif // SOXIPOVERLAYMANIPS_H
