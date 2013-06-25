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
*	@file	SoXipPlot2AreaElement.cpp
*	@brief	Implementation of the SoXipPlot2AreaElement class
*	@author	Julien Gein
**/

#include <xip/inventor/overlay/SoXipPlot2AreaElement.h>

SO_ELEMENT_SOURCE( SoXipPlot2AreaElement );

SoXipPlot2AreaElement::~SoXipPlot2AreaElement()
{

}

void
SoXipPlot2AreaElement::initClass()
{
	SO_ELEMENT_INIT_CLASS( SoXipPlot2AreaElement, SoReplacedElement );
}

void
SoXipPlot2AreaElement::init( SoState* )
{
	
}

void
SoXipPlot2AreaElement::set( SoState* state, SoNode* node, const SbBox3f& bbox,
	float xStartTick, float xTickSpacing, int xNumTicks, float yStartTick, float yTickSpacing, int yNumTicks )
{
    SoXipPlot2AreaElement* elt = (SoXipPlot2AreaElement *)
		getElement( state, classStackIndex, node );

    if( elt )
	{
		elt->mBBox			= bbox;
		elt->mXStartTick	= xStartTick;
		elt->mXTickSpacing	= xTickSpacing;
		elt->mXNumTicks		= xNumTicks;
		elt->mYStartTick	= yStartTick;
		elt->mYTickSpacing	= yTickSpacing;
		elt->mYNumTicks		= yNumTicks;
	}
}

SbBool
SoXipPlot2AreaElement::matches( const SoElement* elt ) const
{
	const SoXipPlot2AreaElement* other = (const SoXipPlot2AreaElement *) elt;

	return 
		other->mBBox			== mBBox &&
		other->mXStartTick		== mXStartTick &&
		other->mXTickSpacing	== mXTickSpacing &&
		other->mXNumTicks		== mXNumTicks &&
		other->mYStartTick		== mYStartTick &&
		other->mYTickSpacing	== mYTickSpacing &&
		other->mYNumTicks		== mYNumTicks;
}

SoElement*
SoXipPlot2AreaElement::copyMatchInfo() const
{
    SoXipPlot2AreaElement* result = (SoXipPlot2AreaElement *) getTypeId().createInstance();

	if( result )
	{
		result->mBBox			= mBBox;
		result->mXStartTick		= mXStartTick;
		result->mXTickSpacing	= mXTickSpacing;
		result->mXNumTicks		= mXNumTicks;
		result->mYStartTick		= mYStartTick;
		result->mYTickSpacing	= mYTickSpacing;
		result->mYNumTicks		= mYNumTicks;
	}

	return result;
}

const SbBox3f&
SoXipPlot2AreaElement::getBBox( SoState* state )
{
	const SoXipPlot2AreaElement* elt = (const SoXipPlot2AreaElement*)
		getConstElement( state, classStackIndex );

	SbBox3f empty;
	empty.makeEmpty();
	
	return elt ? elt->mBBox : empty;
}

void
SoXipPlot2AreaElement::getXTick( SoState* state, float& startTick, float& tickSpacing, int& numTicks  )
{
	const SoXipPlot2AreaElement* elt = (const SoXipPlot2AreaElement*)
		getConstElement( state, classStackIndex );

	if( elt )
	{
		startTick = elt->mXStartTick;
		tickSpacing = elt->mXTickSpacing;
		numTicks = elt->mXNumTicks;
	}
}

void
SoXipPlot2AreaElement::getYTick( SoState* state, float& startTick, float& tickSpacing, int& numTicks )
{
	const SoXipPlot2AreaElement* elt = (const SoXipPlot2AreaElement*)
		getConstElement( state, classStackIndex );

	if( elt )
	{
		startTick = elt->mYStartTick;
		tickSpacing = elt->mYTickSpacing;
		numTicks = elt->mYNumTicks;
	}
}
