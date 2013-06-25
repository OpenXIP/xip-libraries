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
#include <xip/inventor/overlay/SoXipImageTextColorElement.h>
#include <Inventor/errors/SoDebugError.h>

SO_ELEMENT_SOURCE( SoXipImageTextColorElement );

void 
SoXipImageTextColorElement::initClass()
{
	SO_ELEMENT_INIT_CLASS( SoXipImageTextColorElement, SoAccumulatedElement );
}

SoXipImageTextColorElement::~SoXipImageTextColorElement()
{

}

void 
SoXipImageTextColorElement::init( SoState* )
{
	mColorInfo.setNum(0);
}

void 
SoXipImageTextColorElement::add( SoState* state, SoXipImageTextElement::TextElementPosition position, const SbColor& color )
{
	SoXipImageTextColorElement* elt = (SoXipImageTextColorElement *) getElement( state, classStackIndex );

	if( elt )
	{
		int pos = position - SoXipImageTextElement::TP_UPPER_LEFT;

		for( int i = elt->mColorInfo.getNum(); i < pos; ++ i )
			elt->mColorInfo.set1Value( i, SbVec3f(0.8, 0.8, 0.8) );

		elt->mColorInfo.set1Value( pos, color );
	}
}

void 
SoXipImageTextColorElement::push( SoState* state )
{
	const SoXipImageTextColorElement *elt = (const SoXipImageTextColorElement *) getNextInStack();

	mColorInfo = elt->mColorInfo;
}

SoXipImageTextColorElement* 
SoXipImageTextColorElement::getInstance( SoState* state )
{
	return (SoXipImageTextColorElement *) getConstElement(state, classStackIndex);
}

SbColor
SoXipImageTextColorElement::get( SoXipImageTextElement::TextElementPosition position ) const
{
	if( position - SoXipImageTextElement::TP_UPPER_LEFT >= mColorInfo.getNum() )
		return SbColor(0.8, 0.8, 0.8);

	return mColorInfo[ position - SoXipImageTextElement::TP_UPPER_LEFT ];
}
