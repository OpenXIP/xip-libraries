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
*	@file    SoXipOverlayColorElement.h
*	@brief   Declaration of the SoXipOverlayColorElement class
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYCOLORELEMENT_H
#define SOXIPOVERLAYCOLORELEMENT_H

#include <Inventor/elements/SoAccumulatedElement.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/SbColor.h>
#include "SbXipSearchTree.h"

struct ColorInfo
{
	ColorInfo()
		: color( 1, 1, 1 )
		, alpha(0)
	{}

	ColorInfo( const SbColor& color_, float alpha_ )
		: color( color_ )
		, alpha( alpha_ )
	{}

	SbColor		color;
	float		alpha;
};

/**
*	@class SoXipOverlayElement
*
* This element is used to associate an overlay label with a color/ alpha.
* This comes really handy when you need to set the color of an overlay
* nested in an overlay manager
*
**/
class SoXipOverlayColorElement : public SoAccumulatedElement
{
	SO_ELEMENT_HEADER( SoXipOverlayColorElement );

public:
	// Init class
	static void initClass();

    // Initializes element.
    virtual void init( SoState* state );

    // Add to the current overlay colormap
    static void add( SoState* state, const SoMFString& label,
		const SbColor& color, float alpha );

    // Overrides push() method to copy values from next instance in the stack
    virtual void push( SoState* state);

	// Overrides pop() method to delete values from previous instance in the stack
	virtual void pop( SoState*, const SoElement* prevTopElement );

    // Returns the color and alpha for the given label
    static void get( SoState* state, const SoMFString& label, SbColor& color, float& alpha );

protected:
	/// Destructor
	virtual ~SoXipOverlayColorElement();

	/// Multi-label search tree
	SbXipSearchTree< ColorInfo >		mSearchTree;

};

#endif // SOXIPOVERLAYCOLORELEMENT_H
