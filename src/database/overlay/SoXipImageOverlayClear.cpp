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
#include <Inventor/fields/SoSFString.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include "SoXipImageOverlayClear.h"
#include <xip/inventor/overlay/XipOverlayUtils.h>

SO_ENGINE_SOURCE( SoXipImageOverlayClear );

SoXipImageOverlayClear::SoXipImageOverlayClear ()
{
	SO_ENGINE_CONSTRUCTOR( SoXipImageOverlayClear );

	SO_ENGINE_ADD_INPUT( image, (0) );
	SO_ENGINE_ADD_INPUT( clear, () );

	SO_ENGINE_ADD_OUTPUT( status, SoSFString );

	m_ReadInstance = FALSE;
}

SoXipImageOverlayClear::~SoXipImageOverlayClear ()
{

}

void
SoXipImageOverlayClear::initClass ()
{
	SO_ENGINE_INIT_CLASS( SoXipImageOverlayClear, SoEngine, "SoEngine" );
}

void
SoXipImageOverlayClear::inputChanged( SoField* whichField )
{
	if( whichField == &clear )
		status.enable( TRUE );
}

void
SoXipImageOverlayClear::evaluate()
{
	// Do not evaluate at loading
	if( m_ReadInstance )
	{
		m_ReadInstance = FALSE;
		status.enable( FALSE );
		return ;
	}

    try
    {
		for( int k = 0; k < image.getNum(); ++ k )
		{
			SoXipDataImage* refData = 0;
			SoXipDataImage* imageData = image[k];

			if( !imageData )
				return ;
					
			while( (refData = (SoXipDataImage *) imageData->getRefByType( SoXipDataImage::getClassTypeId() )) )
				imageData = refData;

			imageData->setProperty( "overlays", "" );
		}

	    SO_ENGINE_OUTPUT( status, SoSFString, setValue( "OK" ) );
    }
    catch( ... )
    {
	    SO_ENGINE_OUTPUT( status, SoSFString, setValue( "" ) );
	    
		SoDebugError::post( __FILE__, "Error during adding");
    }

	status.enable( FALSE );
}

SbBool 
SoXipImageOverlayClear::readInstance( SoInput* in, unsigned short flags )
{
	m_ReadInstance = TRUE;

	return SoEngine::readInstance( in, flags );
}
