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
*	@file    SoXipOverlayFilterElement.h
*	@brief   Declaration of the SoXipOverlayFilterElement class
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYFILTERELEMENT_H
#define SOXIPOVERLAYFILTERELEMENT_H

#include <Inventor/elements/SoAccumulatedElement.h>
#include <Inventor/fields/SoMFString.h>
#include "SbXipSearchTree.h"

/**
*	@class SoXipOverlayFilterElement
*
* This element is used to filter the displayed overlays 
*
**/
class SoXipOverlayFilterElement : public SoAccumulatedElement
{
	SO_ELEMENT_HEADER( SoXipOverlayFilterElement );

public:
	// Init class
	static void initClass();

    // Initializes element.
    virtual void init( SoState* state );

    // Add to the current overlay colormap
    static void add( SoState* state, const SoMFString& label );

    // Overrides push() method to copy values from next instance in the stack
    virtual void push( SoState* state);

	// Overrides pop() method to delete values from previous instance in the stack
	virtual void pop( SoState*, const SoElement* prevTopElement );

    // Returns the color and alpha for the given label
    static SbBool isOn( SoState* state, const SoMFString& label );

protected:
	/// Destructor
	virtual ~SoXipOverlayFilterElement();

	/// Multi-label search tree
	SbXipSearchTree< SbBool >		mSearchTree;

};

#endif // SOXIPOVERLAYFILTERELEMENT_H
