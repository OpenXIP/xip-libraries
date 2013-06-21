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
*	@file	SoXipPlot2Legend.h
*	@brief	Declaration of the SoXipPlot2Legend class
*	@author	Julien Gein
**/

#ifndef SOXIPPLOT2LEGEND_H
#define SOXIPPLOT2LEGEND_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFColor.h>

class SoXipPlot2Legend : public SoNode
{
	SO_NODE_HEADER( SoXipPlot2Legend );

public:
	SoXipPlot2Legend();

	SoSFString		label;
	SoSFFloat		lineWidth;
	SoSFUShort		linePattern;
	SoSFColor		lineColor;
	SoSFEnum		marker;
	SoSFFloat		markerSize;
	SoSFColor		markerColor;

	static void initClass();

protected:
	virtual ~SoXipPlot2Legend();

	virtual void GLRender( SoGLRenderAction* action );

};

#endif // SOXIPPLOT2LEGEND_H
