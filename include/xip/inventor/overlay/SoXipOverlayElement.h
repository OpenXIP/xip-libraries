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
*	@file    SoXipOverlayElement.h
*	@brief   Declaration of the SoXipOverlayElement and SbXipOverlaySettings
*            classes
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYELEMENT_H
#define SOXIPOVERLAYELEMENT_H

#include <Inventor/elements/SoReplacedElement.h>
#include <xip/inventor/overlay/xipivoverlay.h>

/**
*	@class SbXipOverlaySettings
*
* Container for overlay settings
* 
**/
class XIPIVOVERLAY_API SbXipOverlaySettings
{
public:
	SbXipOverlaySettings();
	SbXipOverlaySettings( int location, SbBool showAnnotation, SbBool showEnumeration );

	SbXipOverlaySettings( const SbXipOverlaySettings& other);

	SbBool	operator == ( const SbXipOverlaySettings& other) const;

	int		getLocation() const;

	SbBool	shouldDisplayAnnotation() const;
	SbBool	shouldDisplayEnumeration() const;

protected:
	int			mLocation;
	SbBool		mShowAnnotation;
	SbBool		mShowEnumeration;

};

/**
*	@class SoXipOverlayElement
*
* This element contains some overlay properties that apply to
* all the overlays in the scene graph where the element is set.
*
**/
class XIPIVOVERLAY_API SoXipOverlayElement : public SoReplacedElement
{
	SO_ELEMENT_HEADER( SoXipOverlayElement );

public:
	/// Location (where to get the overlay points)
	enum LocationType
	{
		PICKING,		//< throught a pick action
		FOCAL_PLANE,	//< on the focal plane
        NEAR_PLANE		//< on the near plane
	};

	/// Open Inventor class initialization
	static void initClass();

	/// Elements init method
	virtual void init( SoState* state );

	/// Set the overlay settings
	static void set( SoState* state, SoNode* node, SbXipOverlaySettings settings );

	virtual SoElement* copyMatchInfo() const;

	virtual SbBool matches( const SoElement* elt ) const;

	static SbXipOverlaySettings get( SoState* state );

protected:
	/// Destructor
	virtual ~SoXipOverlayElement();

	/// Overlay settings
	SbXipOverlaySettings	mSettings;
};

#endif // SOXIPOVERLAYELEMENT_H
