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

#include <xip/inventor/core/SoXipImageTextElement.h>
#include <Inventor/errors/SoDebugError.h>

SO_ELEMENT_SOURCE( SoXipImageTextElement );

void 
SoXipImageTextElement::initClass()
{
	SO_ELEMENT_INIT_CLASS( SoXipImageTextElement, SoAccumulatedElement );
}

SoXipImageTextElement::~SoXipImageTextElement()
{

}

void 
SoXipImageTextElement::init( SoState* )
{
	mTextInfo.clear();
}

void 
SoXipImageTextElement::add( SoState* state, TextElementPosition position, const SbString& text )
{
	SoXipImageTextElement* elt = (SoXipImageTextElement *) getElement( state, classStackIndex );

	if( elt )
	{
		CustomImageText it;
		it.position = position;
		it.text = text;

		elt->mTextInfo.push_back(it);
	}
}

void 
SoXipImageTextElement::push( SoState* state )
{
	const SoXipImageTextElement *elt = (const SoXipImageTextElement *) getNextInStack();

	mTextInfo = elt->mTextInfo;
}

SoXipImageTextElement* 
SoXipImageTextElement::getInstance( SoState* state )
{
	return (SoXipImageTextElement *) getConstElement(state, classStackIndex);
}

int 
SoXipImageTextElement::getNum() const
{
	return (int) mTextInfo.size();
}

SoXipImageTextElement::TextElementPosition
SoXipImageTextElement::getPosition( int index ) const
{
	if( index < 0 || index >= (int) mTextInfo.size() )
	{
		SoDebugError::post( "SoXipImageTextElement::getPosition()",
			   "Index (%d) is out of range 0 - %d",
			   index, mTextInfo.size() - 1 );
	}

	return mTextInfo[index].position;
}

const SbString&
SoXipImageTextElement::getText( int index ) const
{

	if( index < 0 || index >= (int) mTextInfo.size() )
	{
		SoDebugError::post( "SoXipImageTextElement::getText()",
			   "Index (%d) is out of range 0 - %d",
			   index, mTextInfo.size() - 1 );
	}

	return mTextInfo[index].text;
}

