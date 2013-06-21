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
#include "SoXipOverlayDrawStyleElement.h"

SO_ELEMENT_SOURCE( SoXipOverlayDrawStyleElement );

void 
SoXipOverlayDrawStyleElement::initClass()
{
	SO_ELEMENT_INIT_CLASS( SoXipOverlayDrawStyleElement, SoAccumulatedElement );
}

SoXipOverlayDrawStyleElement::~SoXipOverlayDrawStyleElement()
{

}

void 
SoXipOverlayDrawStyleElement::init( SoState* )
{
	mSearchTree.clear();
}

void 
SoXipOverlayDrawStyleElement::add( SoState* state, const SoMFString& label,
								   float pointSize, float lineWidth, unsigned short linePattern )
{
	SoXipOverlayDrawStyleElement* element = (SoXipOverlayDrawStyleElement *) getElement(
		state, classStackIndex );

	if( element ) 
		element->mSearchTree.set( label, StyleInfo(pointSize, lineWidth, linePattern) );
}

void 
SoXipOverlayDrawStyleElement::push( SoState* state )
{
	const SoXipOverlayDrawStyleElement* elt = (const SoXipOverlayDrawStyleElement *) getNextInStack();

	mSearchTree = elt->mSearchTree;
	nodeIds	= elt->nodeIds;
}

void 
SoXipOverlayDrawStyleElement::pop( SoState*, const SoElement* prevTopElement )
{
	const SoXipOverlayDrawStyleElement* prevElt = (const SoXipOverlayDrawStyleElement *) prevTopElement;

	SoXipOverlayDrawStyleElement* element = const_cast< SoXipOverlayDrawStyleElement* >( prevElt );
	element->mSearchTree.clear();
}

void
SoXipOverlayDrawStyleElement::get( SoState* state, const SoMFString& label, 
								   float& pointSize, float& lineWidth, unsigned short& linePattern )
{
	SoXipOverlayDrawStyleElement* element = (SoXipOverlayDrawStyleElement *)
		getElement( state, classStackIndex );

	StyleInfo info;
	element->mSearchTree.get( label, info );

	pointSize = info.pointSize;
	lineWidth = info.lineWidth;
	linePattern = info.linePattern;
}
