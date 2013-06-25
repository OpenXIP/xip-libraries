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
#include <xip/inventor/overlay/SoXipImageTextColorElement.h>
#include "SoXipImageTextColor.h"

SO_NODE_SOURCE( SoXipImageTextColor );

SoXipImageTextColor::SoXipImageTextColor()
{
	SO_NODE_CONSTRUCTOR( SoXipImageTextColor );

	SO_NODE_DEFINE_ENUM_VALUE( TextPosition, TP_UPPER_LEFT );
	SO_NODE_DEFINE_ENUM_VALUE( TextPosition, TP_UPPER_CENTER );
	SO_NODE_DEFINE_ENUM_VALUE( TextPosition, TP_UPPER_RIGHT );
	SO_NODE_DEFINE_ENUM_VALUE( TextPosition, TP_CENTER_LEFT );
	SO_NODE_DEFINE_ENUM_VALUE( TextPosition, TP_CENTER_RIGHT );
	SO_NODE_DEFINE_ENUM_VALUE( TextPosition, TP_LOWER_LEFT );
	SO_NODE_DEFINE_ENUM_VALUE( TextPosition, TP_LOWER_CENTER );
	SO_NODE_DEFINE_ENUM_VALUE( TextPosition, TP_LOWER_RIGHT );

	SO_NODE_SET_SF_ENUM_TYPE( position, TextPosition );	

	SO_NODE_ADD_FIELD( position, (TP_UPPER_LEFT) );
	SO_NODE_ADD_FIELD( color, (0.8, 0.8, 0.8) );
}

SoXipImageTextColor::~SoXipImageTextColor()
{

}

void
SoXipImageTextColor::initClass()
{
	SO_NODE_INIT_CLASS( SoXipImageTextColor, SoNode, "Node" );

	SO_ENABLE( SoGLRenderAction, SoXipImageTextColorElement );
}

void
SoXipImageTextColor::GLRender( SoGLRenderAction* action )
{
	if( action->getState() )
	{
		SoXipImageTextColorElement::add( action->getState(),
			(SoXipImageTextElement::TextElementPosition) position.getValue(), 
			color.getValue() );
	}
}
