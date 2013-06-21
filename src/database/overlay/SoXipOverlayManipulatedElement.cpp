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
#include <Inventor/errors/SoDebugError.h>
#include <xip/inventor/overlay/SoXipOverlayManipulatedElement.h>

SO_ELEMENT_SOURCE( SoXipOverlayManipulatedElement );

SoXipOverlayManipulatedElement::~SoXipOverlayManipulatedElement()
{

}

void
SoXipOverlayManipulatedElement::initClass()
{
	SO_ELEMENT_INIT_CLASS( SoXipOverlayManipulatedElement, SoReplacedElement );
}

void
SoXipOverlayManipulatedElement::init( SoState* )
{
	mIsManipulated = FALSE;
}

void
SoXipOverlayManipulatedElement::set( SoState* state, SoNode* node, SbBool flag )
{
    SoXipOverlayManipulatedElement* elt = (SoXipOverlayManipulatedElement *)
		getElement( state, classStackIndex, node );

    if( elt )
		elt->mIsManipulated = flag;
}

SbBool
SoXipOverlayManipulatedElement::matches( const SoElement* elt ) const
{
	return mIsManipulated == ((const SoXipOverlayManipulatedElement *) elt)->mIsManipulated;
}

SoElement*
SoXipOverlayManipulatedElement::copyMatchInfo() const
{
    SoXipOverlayManipulatedElement* result = (SoXipOverlayManipulatedElement *) getTypeId().createInstance();

	if( result )
	{
		result->mIsManipulated = mIsManipulated;
		return result;
	}
	
	return NULL;
}

SbBool
SoXipOverlayManipulatedElement::get( SoState* state )
{
	const SoXipOverlayManipulatedElement* elt = (const SoXipOverlayManipulatedElement*)
		getConstElement( state, classStackIndex );
	
	return elt ? elt->mIsManipulated : FALSE;
}
