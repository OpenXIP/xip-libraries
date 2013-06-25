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
*	@file    SoXipShape.h
*	@brief   Base class for all the shapes
*	@author  Julien Gein
**/

#ifndef SOXIPSHAPE_H
#define SOXIPSHAPE_H

#include <xip/inventor/core/SoXipSubKit.h>
#include <xip/inventor/overlay/xipivoverlay.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFString.h>
#include "SoXipEditText2.h"
#include <xip/inventor/overlay/SoXipOverlayElement.h>

/**
*	@class	SoXipShape
*	@brief	Base class for all the shapes
*
**/
class XIPIVOVERLAY_API SoXipShape : public SoXipKit
{
	SO_NODE_ABSTRACT_HEADER( SoXipShape );

public:
	/// Status of the shape
	enum StatusType
	{
		NONE,		//< the shape is either created or empty
		CREATE,		//< the shape is being created
		EDIT,		//< the shape is being edited
		CLEAR,		//< the shape is being deleted
	};

	/// Constructor
	SoXipShape();

	/// Shape status
	SoSFBool		on;
	/// Shape status
	SoSFEnum		status;
	/// Shape order (back to front)
	SoSFInt32		order;
	/// Shape rank (enumeration)
	SoSFInt32		rank;
	/// Shape label (name)
	SoMFString		label;
	/// Shape caption (annotation)
	SoSFString		caption;

	/// Open Inventor class initialization
	static void initClass();

public:

	// Set the label
	virtual void setLabel( const SoMFString& label );

	// Set the rank
	virtual void setRank( int rank );

	// Set the caption of the overlay
	virtual void setCaption( const SbString& caption );

	// Select/Unselect the shape
	virtual void select( SbBool state = TRUE );	

	// Is the shape being edited?
	virtual SbBool isEditing() const;

	// Is the shape being created?
	virtual SbBool isCreating() const;

	// Is the shape selected?
	virtual SbBool isSelected() const;

	// Is the shape deleted?
	virtual SbBool isDeleted() const;

    /**
    *   @brief  Callback function called before the shape editing
    *
    **/
	virtual void startEditing() {}

    /**
    *   @brief  Callback function called after the shape editing
    *
    **/
	virtual void finishEditing() {}

    /**
    *   @brief  Callback function called before the shape creation
    *
    **/
	virtual void beforeCreation() {}

	/**
    *   @brief  Callback function called after the shape creation
    *
    **/
	virtual void afterCreation() {}

	virtual void invalidateGeometries() = 0;
	virtual void updateGeometries() = 0;

protected:
	/// Destructor
	~SoXipShape();

	const SbVec2f getNormalizedPosition( const SbVec2s& screenPt ) const;
	virtual SbBool getPoint( SoHandleEventAction* action, SbVec3f& point );
	virtual SbBool getPoint( SoNode* node, const SbVec2s& screenPt, SbVec3f& worldPt );

	SbVec3f projectScreenOffsetToWorld( const SbVec2s& pixelOffset ) const;

	virtual void handleEvent( SoHandleEventAction* action );
	virtual void saveViewInformation( SoAction* action );	

	class SbPlaneProjector*		mPlaneProj;
	SbViewVolume				mViewVolume;
	SbViewportRegion			mViewport;
								
	SbXipOverlaySettings		mOverlaySettings;
	SbBool						mIsSelected;

private:
	static void fieldSensorCallback( void* userData, SoSensor* );

	SoFieldSensor*				mFieldSensors[5];

};

#endif // SOXIPSHAPE_H
