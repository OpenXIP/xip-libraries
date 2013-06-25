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
#include "SoXipMenuStyle.h"
#include "SoXipMenuStyleElement.h"

SO_NODE_SOURCE( SoXipMenuStyle );

SoXipMenuStyle::SoXipMenuStyle()
{
	SO_NODE_CONSTRUCTOR( SoXipMenuStyle );

	SO_NODE_ADD_FIELD(         color, (0xccccccff) );
	SO_NODE_ADD_FIELD(  focusedColor, (0xffffaaff) );
	SO_NODE_ADD_FIELD( disabledColor, (0xccccccff) );

	SO_NODE_ADD_FIELD(         textColor, (0, 0, 0) );
	SO_NODE_ADD_FIELD(  focusedTextColor, (0, 0, 0) );
	SO_NODE_ADD_FIELD( disabledTextColor, (0.8, 0.8, 0.8) );
}

SoXipMenuStyle::~SoXipMenuStyle()
{

}

void
SoXipMenuStyle::initClass()
{
	SO_NODE_INIT_CLASS( SoXipMenuStyle, SoNode, "Node" );

	SO_ENABLE( SoGLRenderAction, SoXipMenuStyleElement );
}

void
SoXipMenuStyle::GLRender( SoGLRenderAction* action )
{
	if( action->getState() )
	{
		SbXipMenuStyle style( color, focusedColor, disabledColor,
			textColor.getValue(), focusedTextColor.getValue(), disabledTextColor.getValue() );

		SoXipMenuStyleElement::set( action->getState(), this, style );
	}
}
