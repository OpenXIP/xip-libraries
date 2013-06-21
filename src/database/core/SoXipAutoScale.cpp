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
*	@file	SoXipAutoScale.cpp
*	@brief	Implementation of the SoXipAutoScale class
*	@author	Julien Gein
**/

#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include "SoXipAutoScale.h"
//scale factor in pixel units that will define the scale.
const unsigned int PIXEL_SCALEFACTOR = 300;

SO_NODE_SOURCE( SoXipAutoScale );

SoXipAutoScale::SoXipAutoScale()
{
	SO_NODE_CONSTRUCTOR( SoXipAutoScale );

	SO_NODE_ADD_FIELD( scale, (1.f) );
}

SoXipAutoScale::~SoXipAutoScale()
{

}

void
SoXipAutoScale::initClass()
{
	SO_NODE_INIT_CLASS( SoXipAutoScale, SoNode, "Node" );
}

void
SoXipAutoScale::GLRender(SoGLRenderAction * action)
{
	const SbViewportRegion& viewport = SoViewportRegionElement::get( action->getState() );
	const SbVec2s& viewportSize = viewport.getViewportSizePixels();	

	float minDim = viewportSize[0] > viewportSize[1] ? viewportSize[1] : viewportSize[0];

	//scale will depend of the screen resolution and the scale factor
	float scale = minDim / PIXEL_SCALEFACTOR;
	if( scale < 1.f )
		scale = 1.f;

	this->scale.setValue( scale );
}


