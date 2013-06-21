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
*	@file	SoXipPlot2AreaElement.h
*	@brief	Declaration of the SoXipPlot2AreaElement class
*	@author	Julien Gein
**/

#ifndef SOXIPPLOT2AREAELEMENT_H
#define SOXIPPLOT2AREAELEMENT_H

#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/SbBox.h>

class SoXipPlot2AreaElement : public SoReplacedElement
{
	SO_ELEMENT_HEADER( SoXipPlot2AreaElement );

public:
	static void initClass();

	virtual void init( SoState* state );

	static void set( SoState* state, SoNode* node, const SbBox3f& bbox,
		float xStartTick, float xTickSpacing, int xNumTicks,
		float yStartTick, float yTickSpacing, int yNumTicks );

	virtual SoElement* copyMatchInfo() const;

	virtual SbBool matches( const SoElement* elt ) const;

	static const SbBox3f& getBBox( SoState* state );
	static void getXTick( SoState* state, float& startTick, float& tickSpacing, int& numTicks );
	static void getYTick( SoState* state, float& startTick, float& tickSpacing, int& numTicks );

protected:
	virtual ~SoXipPlot2AreaElement();

	SbBox3f		mBBox;
	float		mXStartTick;
	float		mXTickSpacing;
	int			mXNumTicks;
	float		mYStartTick;
	float		mYTickSpacing;
	int			mYNumTicks;

};

#endif // SOXIPPLOT2AREAELEMENT_H
