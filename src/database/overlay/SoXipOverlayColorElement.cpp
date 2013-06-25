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
#include "SoXipOverlayColorElement.h"

SO_ELEMENT_SOURCE( SoXipOverlayColorElement );

void 
SoXipOverlayColorElement::initClass()
{
	SO_ELEMENT_INIT_CLASS( SoXipOverlayColorElement, SoAccumulatedElement );
}

SoXipOverlayColorElement::~SoXipOverlayColorElement()
{

}

void 
SoXipOverlayColorElement::init( SoState* )
{
	mSearchTree.clear();
}

void 
SoXipOverlayColorElement::add( SoState* state, const SoMFString& label,
		const SbColor& color, float alpha )
{
	SoXipOverlayColorElement* element = (SoXipOverlayColorElement *) getElement(
		state, classStackIndex );

	if( element ) 
		element->mSearchTree.set( label, ColorInfo(color, alpha) );
}

void 
SoXipOverlayColorElement::push( SoState* state )
{
	const SoXipOverlayColorElement* elt = (const SoXipOverlayColorElement *) getNextInStack();

	mSearchTree = elt->mSearchTree;

	nodeIds	= elt->nodeIds;
}

void
SoXipOverlayColorElement::pop( SoState*, const SoElement* prevTopElement )
{
	const SoXipOverlayColorElement* prevElt = (const SoXipOverlayColorElement *) prevTopElement;

	SoXipOverlayColorElement* element = const_cast< SoXipOverlayColorElement* >( prevElt );
	element->mSearchTree.clear();
}

void
SoXipOverlayColorElement::get( SoState* state, const SoMFString& label,
							   SbColor& color, float& alpha )
{
	SoXipOverlayColorElement* element = (SoXipOverlayColorElement *)
		getElement( state, classStackIndex );

	color = SbColor(1.f, 1.f, 1.f);
	alpha = 0.f;

	ColorInfo info;
	if( element->mSearchTree.get( label, info ) )
	{
		color = info.color;
		alpha = info.alpha;
	}
}
