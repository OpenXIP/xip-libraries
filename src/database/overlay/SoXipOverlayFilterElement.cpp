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
// Disable the warning raised because of the std::map<>
#pragma warning ( disable : 4786 )

#include <Inventor/errors/SoDebugError.h>
#include "SoXipOverlayFilterElement.h"

SO_ELEMENT_SOURCE( SoXipOverlayFilterElement );

void 
SoXipOverlayFilterElement::initClass()
{
	SO_ELEMENT_INIT_CLASS( SoXipOverlayFilterElement, SoAccumulatedElement );
}

SoXipOverlayFilterElement::~SoXipOverlayFilterElement()
{

}

void 
SoXipOverlayFilterElement::init( SoState* )
{
	mSearchTree.clear();
}

void 
SoXipOverlayFilterElement::add( SoState* state, const SoMFString& label )
{
	SoXipOverlayFilterElement* element = (SoXipOverlayFilterElement *) getElement(
		state, classStackIndex );

	if( element ) 
		element->mSearchTree.set( label, TRUE );
}

void 
SoXipOverlayFilterElement::push( SoState* state )
{
	const SoXipOverlayFilterElement* elt = (const SoXipOverlayFilterElement *) getNextInStack();

	mSearchTree = elt->mSearchTree;

	nodeIds	= elt->nodeIds;
}

void
SoXipOverlayFilterElement::pop( SoState*, const SoElement* prevTopElement )
{
	const SoXipOverlayFilterElement* prevElt = (const SoXipOverlayFilterElement *) prevTopElement;

	SoXipOverlayFilterElement* element = const_cast< SoXipOverlayFilterElement* >( prevElt );
	element->mSearchTree.clear();
}

SbBool
SoXipOverlayFilterElement::isOn( SoState* state, const SoMFString& label )
{
	SoXipOverlayFilterElement* element = (SoXipOverlayFilterElement *)
		getElement( state, classStackIndex );

	SbBool isDefined = FALSE;
	element->mSearchTree.get( label, isDefined );

	return !isDefined;
}
