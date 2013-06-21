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
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoFontSizeElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include "SoXipFontAutoScale.h"

SO_NODE_SOURCE( SoXipFontAutoScale );

SoXipFontAutoScale::SoXipFontAutoScale()
{
	SO_NODE_CONSTRUCTOR( SoXipFontAutoScale );
    
    SO_NODE_ADD_FIELD( relative, (FALSE) );
}

SoXipFontAutoScale::~SoXipFontAutoScale()
{
    
}

void
SoXipFontAutoScale::initClass()
{
	SO_NODE_INIT_CLASS( SoXipFontAutoScale, SoNode, "Node" );
}

void 
SoXipFontAutoScale::GLRender( SoGLRenderAction* action )
{
	const SbViewportRegion& viewport = SoViewportRegionElement::get( action->getState() );
	const SbVec2s& viewportSize = viewport.getViewportSizePixels();	

	float minDim = viewportSize[0] > viewportSize[1] ? viewportSize[1] : viewportSize[0];

	// If relative is checked, scale the previous font size
	// Whatever was set before corresponds to 300 pixels (8 maps to 300 pixels when relative
	// is unchecked). Apply factor to this basis.
	if( relative.getValue() )
	{
		float scale = minDim / 300.f;
		if( scale < 1.f )
			scale = 1.f;

		float oldFontSize = SoFontSizeElement::get( action->getState() );

		SoFontSizeElement::set( action->getState(), scale * oldFontSize );
	}
	else
	{
        float fontSize = 0.025 * minDim;
        if( fontSize < 8.0 )
            fontSize = 8.0;
        
        SoFontSizeElement::set( action->getState(), fontSize );
    }
}
