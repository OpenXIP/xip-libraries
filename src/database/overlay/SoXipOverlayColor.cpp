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
// Disable the warning raised because of the std::map<>
#pragma warning ( disable : 4786 )

#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/inventor/overlay/SoXipOverlayColor.h>
#include "SoXipOverlayColorElement.h"

SO_NODE_SOURCE( SoXipOverlayColor )

SoXipOverlayColor::SoXipOverlayColor()
{
	SO_NODE_CONSTRUCTOR( SoXipOverlayColor );

	SO_NODE_ADD_FIELD(        label,      ("") );
	SO_NODE_ADD_FIELD(        color, (1, 1, 1) );
	SO_NODE_ADD_FIELD( transparency,       (0) );
	label.setNum(0);
}

SoXipOverlayColor::~SoXipOverlayColor()
{

}

void
SoXipOverlayColor::initClass()
{
	SO_NODE_INIT_CLASS( SoXipOverlayColor, SoNode, "Node" );

	SO_ENABLE( SoGLRenderAction, SoXipOverlayColorElement );
}

void
SoXipOverlayColor::GLRender( SoGLRenderAction* action )
{
	SoXipOverlayColorElement::add( action->getState(),
		label, color.getValue(), transparency.getValue() );
}
