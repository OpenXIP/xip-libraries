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
*	@file	SoXipFontTypeElement.cpp
*	@brief	Implementation of the SoXipFontTypeElement class
*	@author	Julien Gein
**/

#include <xip/inventor/overlay/SoXipFontTypeElement.h>

SO_ELEMENT_SOURCE( SoXipFontTypeElement );

SoXipFontTypeElement::~SoXipFontTypeElement()
{

}

void
SoXipFontTypeElement::initClass()
{
	SO_ELEMENT_INIT_CLASS( SoXipFontTypeElement, SoReplacedElement );
}

void
SoXipFontTypeElement::init( SoState* )
{
	mFontType = BITMAP;
}

void
SoXipFontTypeElement::set( SoState* state, SoNode* node, FontType type )
{
    SoXipFontTypeElement* elt = (SoXipFontTypeElement *)
		getElement( state, classStackIndex, node );

    if( elt )
		elt->mFontType = type;
}

SbBool
SoXipFontTypeElement::matches( const SoElement* elt ) const
{
	const SoXipFontTypeElement* other = (const SoXipFontTypeElement *) elt;

	return other->mFontType == mFontType;
}

SoElement*
SoXipFontTypeElement::copyMatchInfo() const
{
    SoXipFontTypeElement* result = (SoXipFontTypeElement *) getTypeId().createInstance();

	if( result )
		result->mFontType = mFontType;

	return result;
}

SoXipFontTypeElement::FontType
SoXipFontTypeElement::get( SoState* state )
{
	const SoXipFontTypeElement* elt = (const SoXipFontTypeElement*)
		getConstElement( state, classStackIndex );

	return elt ? elt->mFontType: BITMAP;
}
