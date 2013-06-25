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
*	@file    SoXipOverlayManipulatedElement.h
*	@brief   Declaration of the SoXipOverlayManipulatedElement class
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYMANIPULATEDELEMENT_H
#define SOXIPOVERLAYMANIPULATEDELEMENT_H

#include <Inventor/elements/SoReplacedElement.h>
#include  <xip/inventor/overlay/xipivoverlay.h>
/**
*	@class SoXipOverlayManipulatedElement
*
* Element that tells wheter the selected overlays have
* already been manipulated or not.
*
**/
class XIPIVOVERLAY_API SoXipOverlayManipulatedElement : public SoReplacedElement
{
	SO_ELEMENT_HEADER( SoXipOverlayManipulatedElement );

public:
	/// Constructor
	static void initClass();

	/// Element initialization method
	virtual void init( SoState* state );

	static void set( SoState* state, SoNode* node, SbBool flag );

	virtual SoElement* copyMatchInfo() const;

	virtual SbBool matches( const SoElement* elt ) const;

	static SbBool get( SoState* state );

protected:
	/// Destructor
	virtual ~SoXipOverlayManipulatedElement();

	/// Have the overlays already been manipulated?
	SbBool		mIsManipulated;
};

#endif // SOXIPOVERLAYMANIPULATEDELEMENT_H
