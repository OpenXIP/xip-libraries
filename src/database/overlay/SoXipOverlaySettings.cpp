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
#include <Inventor/actions/SoHandleEventAction.h>
#include "SoXipOverlaySettings.h"

SO_NODE_SOURCE( SoXipOverlaySettings );

SoXipOverlaySettings::SoXipOverlaySettings()
{
	SO_NODE_CONSTRUCTOR( SoXipOverlaySettings );

	SO_NODE_DEFINE_ENUM_VALUE( LocationType, PICKING );
	SO_NODE_DEFINE_ENUM_VALUE( LocationType, FOCAL_PLANE );
	SO_NODE_DEFINE_ENUM_VALUE( LocationType, NEAR_PLANE );

	SO_NODE_SET_SF_ENUM_TYPE( location, LocationType );	

	SO_NODE_ADD_FIELD(        location, (FOCAL_PLANE) );
	SO_NODE_ADD_FIELD(  showAnnotation,        (TRUE) );
	SO_NODE_ADD_FIELD( showEnumeration,        (TRUE) );
}

SoXipOverlaySettings::~SoXipOverlaySettings()
{

}

void
SoXipOverlaySettings::initClass()
{
	SO_NODE_INIT_CLASS( SoXipOverlaySettings, SoNode, "Node" );

	SO_ENABLE( SoGLRenderAction,	SoXipOverlayElement );
	SO_ENABLE( SoHandleEventAction, SoXipOverlayElement );
}

void
SoXipOverlaySettings::doAction( SoAction* action )
{
	SoState* state = action->getState();
	if( state )
	{
		SbXipOverlaySettings settings(
			location.getValue(),
			showAnnotation.getValue(),
			showEnumeration.getValue() );

		SoXipOverlayElement::set( state, this, settings );
	}	
}

void
SoXipOverlaySettings::GLRender( SoGLRenderAction* action )
{
	doAction( action );	
}

void
SoXipOverlaySettings::handleEvent( SoHandleEventAction* action )
{
	doAction( action );	
}
