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
*	@file	SoXipPlot2Element.h
*	@brief	Declaration of the SoXipPlot2Element class
*	@author	Julien Gein
**/

#ifndef SOXIPPLOT2ELEMENT_H
#define SOXIPPLOT2ELEMENT_H

#include <vector>
#include <xip/inventor/overlay/SbXipPlot2LegendInfo.h>
#include <Inventor/elements/SoAccumulatedElement.h>
#include <Inventor/SbPList.h>
#include <Inventor/SbColor.h>

class SoXipPlot2Element : public SoAccumulatedElement 
{
	SO_ELEMENT_HEADER( SoXipPlot2Element );

public:
	static void initClass();

	// add with complete parameter list
	static void	add(SoState* state, SoNode* node, const SbString& label,
		float lineWidth, unsigned short linePattern, const SbColor &lineColor,
		int markerType, float markerSize, const SbColor &markerColor);

	// add with reduced parameter list (reads missing parameters from state object)
	static void	add(SoState* state, SoNode* node, const SbString& label, int markerType, const SbColor &markerColor);

	// add with reduced parameter list (only for color area)
	static void	add(SoState* state, SoNode* node, const SbString& label, const SbColor &lineColor, const SbColor &areaColor);

	static SoXipPlot2Element* getInstance( SoState* state );

	virtual int getNum() const;
	virtual void init(SoState* state);
	virtual void push(SoState* state);	
	virtual void pop(SoState *, const SoElement *prevTopElement);

	virtual const SbXipPlot2LegendInfo& getInfo( int index ) const;
	virtual const SbString& getLabel( int index ) const; 
	virtual float getLineWidth( int index ) const; 
	virtual unsigned short getLinePattern( int index ) const; 
	virtual SbColor getLineColor( int index ) const; 
	virtual int getMarkerType( int index ) const; 
	virtual float getMarkerSize( int index ) const; 
	virtual SbColor getMarkerColor( int index ) const; 
	virtual SbBool isLine( int index ) const;
	virtual SbBool isArea( int index ) const;
	virtual SbColor getAreaColor( int index ) const;

protected:
	virtual ~SoXipPlot2Element();

	SbPList		mPlotInfoList;
	int			mStartIndex;
};

#endif // SOXIPPLOT2ELEMENT_H
