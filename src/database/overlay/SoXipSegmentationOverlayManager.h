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
*  @file	SoXipSegmentationOverlayManager.h
*  @brief	Declaration of the SoXipSegmentationOverlayManager node
*  @author	Julien Gein
*
*  Copyright (C) Siemens Corporate Research, Inc. 2003-2005 All Rights Reserved
**/

#ifndef SoXipSegmentationOverlayManager_H
#define SoXipSegmentationOverlayManager_H

#include <map>
#include "SoXipOverlayManager.h"
#include <Inventor/fields/SoMFString.h>

/**
*  \class SoXipSegmentationOverlayManager
*
*  This class supports overlay creation and management for dicom images.
*  A SoXipImageExaminer must be provided prior to the manager, to grant 
*  the manager access to the image element.
*
*  \see SoXipImageExaminer
*
**/
class SoXipSegmentationOverlayManager : public SoXipOverlayManager
{
	SO_NODE_HEADER( SoXipSegmentationOverlayManager );

	SoMFString		OverlayOption ;
	
	SoSFInt32		OverlayAction ;

	SoSFBool		OverlayEnable ;

public:
    /// Constructor
	SoXipSegmentationOverlayManager();

    /// Class initialization
	static void initClass();

protected:
    /// Destructor
	~SoXipSegmentationOverlayManager();

	virtual void handleEvent( SoHandleEventAction* action );
	virtual void GLRender( SoGLRenderAction* action );
	virtual void pick( SoPickAction* action );	
	virtual void callback( SoCallbackAction* action );	
	
private:

	int SetupOverlayOption ( SoXipShape *pshape, SoMFString& OO ) ;
	int SetupOverlayAction ( SoHandleEventAction* action, SoXipShape *pshape ) ;

	SbTime				mMouseDownTime ;
	SbTime				mMouseUpTime ;
	SbVec2s				mMouseDownPos ;
};

#endif // SoXipSegmentationOverlayManager_H
