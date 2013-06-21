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
*	@file	SoXipPlot2Extent.h
*	@brief	Declaration of the SoXipPlot2Extent class
*	@author	Julien Gein
**/

#ifndef SOXIPPLOT2EXTENT_H
#define SOXIPPLOT2EXTENT_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFVec2f.h>

class SoXipPlot2Extent : public SoShape
{
	SO_NODE_HEADER( SoXipPlot2Extent );

public:
	SoXipPlot2Extent();

	SoSFVec2f	xRange;
	SoSFVec2f	yRange;

	static void initClass();

protected:
	virtual ~SoXipPlot2Extent();

	virtual void generatePrimitives( class SoAction* );
	virtual void computeBBox( SoAction* action, SbBox3f& box, SbVec3f& center );

};

#endif // SOXIPPLOT2EXTENT_H
