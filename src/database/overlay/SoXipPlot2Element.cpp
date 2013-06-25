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
*	@file	SoXipPlot2Element.cpp
*	@brief	Implementation of the SoXipPlot2Element class
*	@author	Julien Gein
**/

#include <xip/inventor/overlay/SoXipPlot2Element.h>
#include <xip/inventor/overlay/SbXipPlot2LegendInfo.h>
#include <Inventor/elements/SoLinePatternElement.h>
#include <Inventor/elements/SoLineWidthElement.h>
#include <Inventor/elements/SoPointSizeElement.h>
#include <Inventor/elements/SoLazyElement.h>

#ifdef DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif //DEBUG

SO_ELEMENT_SOURCE( SoXipPlot2Element );

void 
SoXipPlot2Element::initClass()
{
	SO_ELEMENT_INIT_CLASS( SoXipPlot2Element, SoAccumulatedElement );
}

SoXipPlot2Element::~SoXipPlot2Element()
{

}

void
SoXipPlot2Element::init( SoState* )
{
	mPlotInfoList.truncate(0);
	mStartIndex = 0;
}

void 
SoXipPlot2Element::add( SoState* state, SoNode* node, const SbString& label,
	float lineWidth, unsigned short linePattern, const SbColor& lineColor,
	int markerType, float markerSize, const SbColor& markerColor )
{
	SoXipPlot2Element* elt = (SoXipPlot2Element *) getElement(state, classStackIndex);

	if (elt) 
	{
		SbXipPlot2LegendInfo* newPlotInfo = new SbXipPlot2LegendInfo;
		if (newPlotInfo)
		{
			newPlotInfo->label = label;
			newPlotInfo->lineWidth = lineWidth;;
			newPlotInfo->linePattern = linePattern;
			newPlotInfo->lineColor = lineColor;
			newPlotInfo->markerType = markerType;
			newPlotInfo->markerSize = markerSize;
			newPlotInfo->markerColor = markerColor;
			newPlotInfo->isArea = FALSE;
			newPlotInfo->isLine = TRUE;

			elt->mPlotInfoList.append(newPlotInfo);
		}

		// Update node id list in element
		elt->addNodeId(node);
	}
}

void
SoXipPlot2Element::add( SoState* state, SoNode* node, const SbString& label, int markerType, const SbColor& markerColor )
{
	SoXipPlot2Element* elt = (SoXipPlot2Element *) getElement(state, classStackIndex);
	
	if (elt) 
	{
		SbXipPlot2LegendInfo* newPlotInfo = new SbXipPlot2LegendInfo;
		if (newPlotInfo)
		{
			newPlotInfo->label = label;
			newPlotInfo->markerType = markerType;
			newPlotInfo->markerSize = SoPointSizeElement::get(state);
			newPlotInfo->markerColor = markerColor;
			newPlotInfo->isArea = FALSE;
			newPlotInfo->isLine = FALSE;

			elt->mPlotInfoList.append(newPlotInfo);
		}

		// Update node id list in element
		elt->addNodeId(node);
	}
}

void 
SoXipPlot2Element::add( SoState* state, SoNode* node, const SbString& label, const SbColor& lineColor, const SbColor& areaColor )
{
	SoXipPlot2Element* elt = (SoXipPlot2Element *) getElement(state, classStackIndex);

	if (elt) 
	{
		SbXipPlot2LegendInfo* newPlotInfo = new SbXipPlot2LegendInfo;
		if (newPlotInfo)
		{
			newPlotInfo->label = label;
			newPlotInfo->isArea = TRUE;
			newPlotInfo->isLine = FALSE;
			newPlotInfo->lineColor = lineColor;
			newPlotInfo->areaColor = areaColor;

			elt->mPlotInfoList.append(newPlotInfo);
		}

		// Update node id list in element
		elt->addNodeId(node);
	}
}

void 
SoXipPlot2Element::push( SoState* state )
{
	const SoXipPlot2Element* elt = (const SoXipPlot2Element *) getNextInStack();

	mPlotInfoList = elt->mPlotInfoList;
	mStartIndex = mPlotInfoList.getLength();
	nodeIds = elt->nodeIds;
}

void 
SoXipPlot2Element::pop( SoState*, const SoElement* prevTopElement )
{
	const SoXipPlot2Element *prevElt = (const SoXipPlot2Element *) prevTopElement;

	// Free up any plane structures that were created by prevElt
	for (int i = prevElt->mStartIndex; i < prevElt->mPlotInfoList.getLength(); i++)
	{
		delete (SbXipPlot2LegendInfo *) prevElt->mPlotInfoList[i];
	}
}


SoXipPlot2Element*
SoXipPlot2Element::getInstance( SoState* state )
{
	return (SoXipPlot2Element *) getConstElement( state, classStackIndex );
}

int 
SoXipPlot2Element::getNum() const
{
	return (int) mPlotInfoList.getLength();
}

const 
SbXipPlot2LegendInfo& SoXipPlot2Element::getInfo( int index ) const
{
#ifdef DEBUG
	if( index < 0 || index >= mPlotInfoList.getLength() )
		SoDebugError::post("SoXipPlot2Element::getInfo",
		"Index (%d) is out of range 0 - %d",
		index, mPlotInfoList.getLength() - 1);
#endif

	SbXipPlot2LegendInfo* plotInfo = (SbXipPlot2LegendInfo *) mPlotInfoList[index];
	return *plotInfo;
}

const 
SbString& SoXipPlot2Element::getLabel( int index ) const
{
#ifdef DEBUG
	if( index < 0 || index >= mPlotInfoList.getLength() )
		SoDebugError::post("SoXipPlot2Element::getLabel",
		"Index (%d) is out of range 0 - %d",
		index, mPlotInfoList.getLength() - 1);
#endif

	SbXipPlot2LegendInfo* plotInfo = (SbXipPlot2LegendInfo *) mPlotInfoList[index];
	return plotInfo->label;
}

float 
SoXipPlot2Element::getLineWidth( int index ) const
{
#ifdef DEBUG
	if( index < 0 || index >= mPlotInfoList.getLength() )
		SoDebugError::post("SoXipPlot2Element::getLineWidth",
		"Index (%d) is out of range 0 - %d",
		index, mPlotInfoList.getLength() - 1);
#endif

	SbXipPlot2LegendInfo* plotInfo = (SbXipPlot2LegendInfo *) mPlotInfoList[index];
	return plotInfo->lineWidth;
}

unsigned short 
SoXipPlot2Element::getLinePattern( int index ) const
{
#ifdef DEBUG
	if( index < 0 || index >= mPlotInfoList.getLength() )
		SoDebugError::post("SoXipPlot2Element::getLinePattern",
		"Index (%d) is out of range 0 - %d",
		index, mPlotInfoList.getLength() - 1);
#endif

	SbXipPlot2LegendInfo* plotInfo = (SbXipPlot2LegendInfo *) mPlotInfoList[index];
	return plotInfo->linePattern;
}

SbColor 
SoXipPlot2Element::getLineColor( int index ) const
{
#ifdef DEBUG
	if( index < 0 || index >= mPlotInfoList.getLength() )
		SoDebugError::post("SoXipPlot2Element::getLineColor",
		"Index (%d) is out of range 0 - %d",
		index, mPlotInfoList.getLength() - 1);
#endif

	SbXipPlot2LegendInfo* plotInfo = (SbXipPlot2LegendInfo *) mPlotInfoList[index];
	return plotInfo->lineColor;
} 

int
SoXipPlot2Element::getMarkerType( int index ) const
{
#ifdef DEBUG
	if( index < 0 || index >= mPlotInfoList.getLength() )
		SoDebugError::post("SoXipPlot2Element::getMarkerType",
		"Index (%d) is out of range 0 - %d",
		index, mPlotInfoList.getLength() - 1);
#endif

	SbXipPlot2LegendInfo* plotInfo = (SbXipPlot2LegendInfo *) mPlotInfoList[index];
	return plotInfo->markerType;
}

float
SoXipPlot2Element::getMarkerSize( int index ) const
{
#ifdef DEBUG
	if( index < 0 || index >= mPlotInfoList.getLength() )
		SoDebugError::post("SoXipPlot2Element::getMarkerSize",
		"Index (%d) is out of range 0 - %d",
		index, mPlotInfoList.getLength() - 1);
#endif

	SbXipPlot2LegendInfo* plotInfo = (SbXipPlot2LegendInfo *) mPlotInfoList[index];
	return plotInfo->markerSize;
}

SbColor
SoXipPlot2Element::getMarkerColor( int index ) const
{
#ifdef DEBUG
	if( index < 0 || index >= mPlotInfoList.getLength() )
		SoDebugError::post("SoXipPlot2Element::getMarkerColor",
		"Index (%d) is out of range 0 - %d",
		index, mPlotInfoList.getLength() - 1);
#endif

	SbXipPlot2LegendInfo* plotInfo = (SbXipPlot2LegendInfo *) mPlotInfoList[index];
	return plotInfo->markerColor;
} 

SbBool 
SoXipPlot2Element::isLine( int index ) const
{
#ifdef DEBUG
	if( index < 0 || index >= mPlotInfoList.getLength() )
		SoDebugError::post("SoXipPlot2Element::isLine",
		"Index (%d) is out of range 0 - %d",
		index, mPlotInfoList.getLength() - 1);
#endif

	SbXipPlot2LegendInfo* plotInfo = (SbXipPlot2LegendInfo *) mPlotInfoList[index];
	return plotInfo->isLine;
} 

SbBool 
SoXipPlot2Element::isArea( int index ) const
{
#ifdef DEBUG
	if( index < 0 || index >= mPlotInfoList.getLength() )
		SoDebugError::post("SoXipPlot2Element::isArea",
		"Index (%d) is out of range 0 - %d",
		index, mPlotInfoList.getLength() - 1);
#endif

	SbXipPlot2LegendInfo* plotInfo = (SbXipPlot2LegendInfo *) mPlotInfoList[index];
	return plotInfo->isArea;
} 

SbColor 
SoXipPlot2Element::getAreaColor( int index ) const
{
#ifdef DEBUG
	if( index < 0 || index >= mPlotInfoList.getLength() )
		SoDebugError::post("SoXipPlot2Element::getAreaColor",
		"Index (%d) is out of range 0 - %d",
		index, mPlotInfoList.getLength() - 1);
#endif

	SbXipPlot2LegendInfo* plotInfo = (SbXipPlot2LegendInfo *) mPlotInfoList[index];
	return plotInfo->areaColor;
}

