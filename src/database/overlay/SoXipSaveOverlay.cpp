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
#include <Inventor/sensors/SoFieldSensor.h>
#include "SoXipSaveOverlay.h"
#include  <xip/inventor/overlay/XipOverlayUtils.h>

SO_ENGINE_SOURCE( SoXipSaveOverlay );

SoXipSaveOverlay::SoXipSaveOverlay()
{
	SO_ENGINE_CONSTRUCTOR( SoXipSaveOverlay );

	SO_ENGINE_ADD_INPUT( filename, ("") );
	SO_ENGINE_ADD_INPUT( overlays,  (0) );
	SO_ENGINE_ADD_INPUT(     save,   () );

	SO_ENGINE_ADD_OUTPUT( status, SoSFString );

	m_ReadInstance = FALSE;
}

SoXipSaveOverlay::~SoXipSaveOverlay()
{

}

void
SoXipSaveOverlay::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipSaveOverlay, SoEngine, "Engine" );
}

void
SoXipSaveOverlay::inputChanged( SoField* whichField )
{
	if( whichField == &save )
		status.enable( TRUE );
}

void
SoXipSaveOverlay::evaluate()
{
	// SGI automatically triggers evaluate after loading. Disable
	// evaluation in this case.
	if( m_ReadInstance )
	{
		m_ReadInstance = FALSE;
		return ;
	}

	SbString file = filename.getValue();
	if( file.getLength() )
	{
		SoNodeList nodes;
		for( int i = 0; i < overlays.getNum(); ++ i )
			nodes.append( overlays[i] );

		XipOverlayUtils::saveOverlaysToFile( nodes, file.getString() );
	}

	// Disable output (save has to be triggered again for evaluation to occur)
	status.enable( FALSE );
}

SbBool
SoXipSaveOverlay::readInstance( SoInput* in, unsigned short flags )
{
	m_ReadInstance = TRUE;

	return SoEngine::readInstance( in, flags );
}
