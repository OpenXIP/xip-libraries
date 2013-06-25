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
#include "SoXipOverlayFilter.h"
#include "SoXipOverlayFilterElement.h"

SO_NODE_SOURCE( SoXipOverlayFilter )

SoXipOverlayFilter::SoXipOverlayFilter()
{
	SO_NODE_CONSTRUCTOR( SoXipOverlayFilter );

	SO_NODE_ADD_FIELD( label, ("") );
	label.setNum(0);
}

SoXipOverlayFilter::~SoXipOverlayFilter()
{

}

void
SoXipOverlayFilter::initClass()
{
	SO_NODE_INIT_CLASS( SoXipOverlayFilter, SoNode, "Node" );

	SO_ENABLE( SoGLRenderAction, SoXipOverlayFilterElement );
}

void
SoXipOverlayFilter::GLRender( SoGLRenderAction* action )
{
	SoXipOverlayFilterElement::add( action->getState(), label );
}
