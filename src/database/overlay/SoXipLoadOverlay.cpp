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
#include <xip/inventor/overlay/XipOverlayUtils.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include "SoXipLoadOverlay.h"

SO_ENGINE_SOURCE( SoXipLoadOverlay );

SoXipLoadOverlay::SoXipLoadOverlay()
{
	SO_ENGINE_CONSTRUCTOR( SoXipLoadOverlay );

	SO_ENGINE_ADD_INPUT( filename, ("") );
	SO_ENGINE_ADD_INPUT( load, () );

	SO_ENGINE_ADD_OUTPUT( overlays, SoMFNode );
}

SoXipLoadOverlay::~SoXipLoadOverlay()
{

}

void
SoXipLoadOverlay::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipLoadOverlay, SoEngine, "Engine" );
}

void
SoXipLoadOverlay::inputChanged( SoField* whichField )
{
	if( whichField == &load )
		overlays.enable( TRUE );
}

void
SoXipLoadOverlay::evaluate()
{
	SbString file = filename.getValue();
	if( file.getLength() )
	{
		// Read the root node in the given file
		SoNodeList nodes = XipOverlayUtils::loadOverlaysFromFile( file.getString(), TRUE );

		SoMFNode nodesTmp;
		nodesTmp.setNum( nodes.getLength() );
		for( int i = 0; i < nodes.getLength(); ++ i )
			nodesTmp.set1Value( i, nodes[i] );

		SO_ENGINE_OUTPUT( overlays, SoMFNode, copyFrom( nodesTmp ) );
	}

	// Disable output (load has to be triggered again for evaluation to occur)
	overlays.enable( FALSE );
}
