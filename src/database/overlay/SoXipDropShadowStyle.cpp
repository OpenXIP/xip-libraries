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
#include <Inventor/actions/SoGLRenderAction.h>
#include "SoXipDropShadowStyle.h"
#include "SoXipDropShadowElement.h"

SO_NODE_SOURCE( SoXipDropShadowStyle );

SoXipDropShadowStyle::SoXipDropShadowStyle()
{
	SO_NODE_CONSTRUCTOR( SoXipDropShadowStyle );

	SO_NODE_ADD_FIELD( on, (FALSE) );
	SO_NODE_ADD_FIELD( color, (0, 0, 0) );
	SO_NODE_ADD_FIELD( transparency, (0) );
	SO_NODE_ADD_FIELD( pixelOffset, (1, -1) );
}

SoXipDropShadowStyle::~SoXipDropShadowStyle()
{
	
}

void
SoXipDropShadowStyle::initClass()
{
	SO_NODE_INIT_CLASS( SoXipDropShadowStyle, SoNode, "Node" );

	SO_ENABLE( SoGLRenderAction, SoXipDropShadowElement );
}

void
SoXipDropShadowStyle::GLRender( SoGLRenderAction* action )
{
	SoState* state = action->getState();
	if( state )
	{
		SoXipDropShadowElement::set( state, this, 
			on.getValue(),
			color.getValue(),
			transparency.getValue(),
			pixelOffset.getValue() );
	}
}
