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
*	@file	SoXipAutoScale.h
*	@brief	Declaration of the SoXipAutoScale class
*	@author	Julien Gein
**/

#ifndef SOXIPAUTOSCALE_H
#define SOXIPAUTOSCALE_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFFloat.h>

class SoXipAutoScale : public SoNode  
{
	SO_NODE_HEADER( SoXipAutoScale );

public:
	SoXipAutoScale();

	SoSFFloat	scale;

	static void initClass();

protected:
	virtual ~SoXipAutoScale();
	
	virtual void GLRender( SoGLRenderAction* action );
};

#endif // SOXIPAUTOSCALE_H
