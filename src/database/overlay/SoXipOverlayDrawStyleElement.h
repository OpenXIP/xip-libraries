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
*	@file    SoXipOverlayDrawStyleElement.h
*	@brief   Declaration of the SoXipOverlayDrawStyleElement class
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYDRAWSTYLEELEMENT_H
#define SOXIPOVERLAYDRAWSTYLEELEMENT_H

#include <Inventor/elements/SoAccumulatedElement.h>
#include <Inventor/fields/SoMFString.h>
#include "SbXipSearchTree.h"

struct StyleInfo
{
	StyleInfo()
		: pointSize(0)
		, lineWidth(0)
		, linePattern( 0xffff )
	{}
	
	StyleInfo( float pointSize, float lineWidth, unsigned short linePattern )
		: pointSize( pointSize )
		, lineWidth( lineWidth )
		, linePattern( linePattern )
	{}

	float pointSize;
	float lineWidth;
	unsigned short linePattern;
};

/**
*	@class SoXipOverlayDrawStyleElement
*
* This element is used to associate an overlay label with a draw style.
* This comes really handy when you need to set the line style of an overlay
* nested in an overlay manager
*
**/
class SoXipOverlayDrawStyleElement : public SoAccumulatedElement
{
	SO_ELEMENT_HEADER( SoXipOverlayDrawStyleElement );

public:
	// Init class
	static void initClass();

    // Initializes element.
    virtual void init( SoState* state );

    // Add to the current overlay colormap
    static void add( SoState* state, const SoMFString& label, float pointSize, 
		float lineWidth, unsigned short linePattern );

    // Overrides push() method to copy values from next instance in the stack
    virtual void push( SoState* state);

    // Overrides pop() method to delete values from previous instance in the stack
    virtual void pop( SoState*, const SoElement* prevTopElement );

    // Returns the color and alpha for the given label
    static void get( SoState* state, const SoMFString& label, float& pointSize, 
		float& lineWidth, unsigned short& linePattern );

protected:
	/// Destructor
	virtual ~SoXipOverlayDrawStyleElement();

	// Multi-label search tree
	SbXipSearchTree< StyleInfo >	mSearchTree;

};

#endif // SOXIPOVERLAYDRAWSTYLEELEMENT_H
