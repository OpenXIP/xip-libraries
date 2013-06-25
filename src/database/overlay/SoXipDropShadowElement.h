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
*  @file SoXipDropShadowElement.h
*  @brief Declaration of the SoXipDropShadowElement element
*  @author Julien Gein
**/

#ifndef SOXIPDROPSHADOWELEMENT_H
#define SOXIPDROPSHADOWELEMENT_H

#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/SbColor.h>

/**
*	@class SoXipDropShadowElement
*
* This element defines the drop shadows properties for 2D
* annotations (e.g. SoXipEllipse, SoXipPolygon, etc.) as well
* as text annotations.
*
*	@see SoXipDropShadowStyle
*	@see SoXipManipulableShape
*	@see SoXipText2
*
**/
class SoXipDropShadowElement : public SoReplacedElement
{
	SO_ELEMENT_HEADER( SoXipDropShadowElement );

public:
    /// Open Inventor class initialization
	static void initClass();

	/// Initializes element (no constructor for elements)
	virtual void init( SoState* state );

	/// Sets the drop shadows properties (offset, color, transparency)
	static void set( SoState*	state,
		SoNode*					node,
		SbBool					on,
		const SbColor&			color,
		float					transparency, 
		const SbVec2s&			pixelOffset );

    /// Copy element information into a new element
	virtual SoElement* copyMatchInfo() const;

    /// Returns wheter the element matches the given argument
	virtual SbBool matches( const SoElement* elt ) const;

    /// Are the drop shadows activated ?
	static SbBool isOn( SoState* state );
    
    /// Get the drop shadows color
	static SbColor getColor( SoState* state );
    
    /// Get the drop shadows transparency    
	static float getTransparency( SoState* state );
    
    /**
	*	@brief	get the offset (in screen coordinates), where the drop
	* shadows should be rendered.
	*
	* The user can project this offset on the current plane using a
	* SbPlaneProjector to get the offset in world coordinates.
    *  
    *	@param	state     state of the action
	*
    *	@return	a 2D point
    **/
	static SbVec2s getPixelOffset( SoState* state );

protected:
    /// Destructor
	virtual ~SoXipDropShadowElement();

    /// Activation flag
	SbBool		    mOn;
    /// Drop shadows color
	SbColor		    mColor;
    /// Drop shadows transparency
	float		    mTransparency;
    /// Drop shadows offset in screen coordinates
	SbVec2s		    mPixelOffset;

};

#endif // SOXIPDROPSHADOWELEMENT_H
