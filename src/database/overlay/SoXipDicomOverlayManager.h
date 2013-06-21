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
*  @file	SoXipDicomOverlayManager.h
*  @brief	Declaration of the SoXipDicomOverlayManager node
*  @author	Babu Samuel
*
*  Copyright (C) Siemens Corporate Research, Inc. 2007-2008 All Rights Reserved
**/

#ifndef SOXIPDICOMOVERLAYMANAGER_H
#define SOXIPDICOMOVERLAYMANAGER_H

#include <map>
#include "SoXipOverlayManager.h"

class SoXipDataDicom;

/**
*  \class SoXipDicomOverlayManager
*
*  This class supports overlay creation and management for dicom images.
*  A SoXipImageExaminer must be provided prior to the manager, to grant 
*  the manager access to the image element.
*
*  \see SoXipImageExaminer
*
**/
class SoXipDicomOverlayManager : public SoXipOverlayManager
{
	SO_NODE_HEADER( SoXipDicomOverlayManager );

public:
    /// Constructor
	SoXipDicomOverlayManager();

	SoSFTrigger		store;
	SoSFTrigger		update;

    /// Class initialization
	static void initClass();

    /// For Internal use only. Get access to the shape list corresponding
    /// to the current dicom image slice.
	virtual SoXipShapeList* getCurrentList();

protected:
    /// Destructor
	~SoXipDicomOverlayManager();

    /// Check whether the current dicom image has changed
	virtual SbBool imageChanged( SoAction* action );
    /// Update the internal overlay structure, whenever the dicom image changes
	virtual void updateOverlays( SoAction* action );

	virtual void handleEvent( SoHandleEventAction* action );
	virtual void GLRender( SoGLRenderAction* action );
	virtual void pick( SoPickAction* action );	
	virtual void callback( SoCallbackAction* action );	

    /// Update the look-up table that
	virtual void updateSliceMap();
	virtual void saveOverlays();
	virtual void loadOverlays();
	virtual void clearClipboard();
	
    /// Declares a type that maps a slice index to a shape list
	typedef std::map< int, SoXipShapeList* > SeparatorMapType;

    /// Wrapper of the current dicom image shown
	SoXipDataDicom*			mDataDicom;
    /// Look-up table to give easy access to the overlays of the desired slice
	SeparatorMapType		mSliceMap;
    /// Index of the current dicom image slice shown
	int						mCurrentSlice;

public:
	virtual void addOverlays();
	virtual void removeOverlays();
	virtual void clearOverlays();

private:
	class SoFieldSensor*	mStoreSensor;
	class SoFieldSensor*	mUpdateSensor;
	class SoNodeSensor*		mOverlaysSensor;
	class SoTimerSensor*	mOverlaysTimerSensor;

	static void storeSensorCB( void* userData, SoSensor* );
	static void updateSensorCB( void* userData, SoSensor* );
	static void overlaysSensorCB( void* userData, SoSensor* );
	static void overlaysTimerSensorCB( void* userData, SoSensor* );
};

#endif // SOXIPDICOMOVERLAYMANAGER_H
