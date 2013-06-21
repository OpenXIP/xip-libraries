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
*	@file    SbXipPlot2LegendInfo.h
*	@brief   Declaration of the SbXipPlot2LegendInfo class
*	@author  Julien Gein
**/

#ifndef SBXIPPLOT2LEGENDINFO_H
#define SBXIPPLOT2LEGENDINFO_H

#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/SbColor.h>

struct SbXipPlot2LegendInfo
{
	SbXipPlot2LegendInfo();
	SbXipPlot2LegendInfo( const SbXipPlot2LegendInfo& rhs );
	SbXipPlot2LegendInfo& operator = ( const SbXipPlot2LegendInfo& rhs );

	SbString		label;
	float			lineWidth;
	unsigned short	linePattern;
	SbColor			lineColor;
	int				markerType;
	float			markerSize;
	SbColor			markerColor;
	SbBool			isArea;
	SbBool			isLine;
	SbColor			areaColor;
};

#endif // SBXIPPLOT2LEGENDINFO_H
