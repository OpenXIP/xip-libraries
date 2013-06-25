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
*	@file SoXipMenuStyleElement.h
*	@brief Declaration of the SbXipMenuStyle structure and SoXipMenuStyleElement class
*	@author Julien Gein
**/

#ifndef SOXIPMENUSTYLEELEMENT_H
#define SOXIPMENUSTYLEELEMENT_H

#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/SbColor.h>

struct SbXipMenuStyle
{
	SbXipMenuStyle()
		: textColor( SbColor(0, 0, 0) )
		, focusedTextColor( SbColor(0, 0, 0) )
		, disabledTextColor( SbColor(0.2, 0.2, 0.2) )
	{		
		color.setValue( 0xffff00ff );
		focusedColor.setValue( 0xffff00ff );
		disabledColor.setValue( 0xffff00ff );
	}

	SbXipMenuStyle(
		const SoMFUInt32& color_,
		const SoMFUInt32& focusedColor_,
		const SoMFUInt32& disabledColor_,
		const SbColor& textColor_,
		const SbColor& focusedTextColor_,
		const SbColor& disabledTextColor_ )

		: textColor( textColor_ )
		, focusedTextColor( focusedTextColor_ )
		, disabledTextColor( disabledTextColor_ )
	{
		color.setNum( color_.getNum() );
		color.setValues( 0, color_.getNum(), color_.getValues(0) );
		focusedColor.setNum( focusedColor_.getNum() );
		focusedColor.setValues( 0, focusedColor_.getNum(), focusedColor_.getValues(0) );
		disabledColor.setNum( disabledColor_.getNum() );
		disabledColor.setValues( 0, disabledColor_.getNum(), disabledColor_.getValues(0) );
	}

	SbXipMenuStyle( const SbXipMenuStyle& other )
	{
		this->operator =( other );
	}

	SbBool operator == ( const SbXipMenuStyle& other ) const
	{
		return
			color				== other.color				&&
			focusedColor		== other.focusedColor		&&
			disabledColor		== other.disabledColor		&&

			textColor			== other.textColor			&&
			focusedTextColor	== other.focusedTextColor	&&
			disabledTextColor	== other.disabledTextColor;
	}

	SbXipMenuStyle& operator = ( const SbXipMenuStyle& other )
	{
		color.setNum( other.color.getNum() );
		color.setValues( 0, other.color.getNum(), other.color.getValues(0) );
		focusedColor.setNum( other.focusedColor.getNum() );
		focusedColor.setValues( 0, other.focusedColor.getNum(), other.focusedColor.getValues(0) );
		disabledColor.setNum( other.disabledColor.getNum() );
		disabledColor.setValues( 0, other.disabledColor.getNum(), other.disabledColor.getValues(0) );

		textColor			= other.textColor;
		focusedTextColor	= other.focusedTextColor;
		disabledTextColor	= other.disabledTextColor;

		return *this;
	}

	SoMFUInt32		color;
	SoMFUInt32		focusedColor;
	SoMFUInt32		disabledColor;

	SbColor			textColor;
	SbColor			focusedTextColor;
	SbColor			disabledTextColor;
};

class SoXipMenuStyleElement : public SoReplacedElement
{
	SO_ELEMENT_HEADER( SoXipMenuStyleElement );

public:
	static void initClass();

	// Initializes element
	virtual void init( SoState* state );

	// Sets the current active slice index 
	static void set( SoState* state, SoNode* node, const SbXipMenuStyle& menuStyle );

	virtual SoElement* copyMatchInfo() const;

	virtual SbBool matches( const SoElement* elt ) const;

	static SbXipMenuStyle get( SoState* state );

protected:
	virtual ~SoXipMenuStyleElement();

	SbXipMenuStyle	mMenuStyle;

};

#endif // SOXIPMENUSTYLEELEMENT_H
