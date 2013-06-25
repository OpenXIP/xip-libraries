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
#include <Inventor/fields/SoMFNode.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include "SoXipImageOverlaySearch.h"
#include <xip/inventor/overlay/XipOverlayUtils.h>
SO_ENGINE_SOURCE( SoXipImageOverlaySearch );

SoXipImageOverlaySearch::SoXipImageOverlaySearch()
{
	SO_ENGINE_CONSTRUCTOR( SoXipImageOverlaySearch );

	SO_ENGINE_ADD_INPUT(  image, (0) );
	SO_ENGINE_ADD_INPUT(  label, ("") );
	SO_ENGINE_ADD_INPUT(  type, ("") );
	SO_ENGINE_ADD_INPUT(  caption, ("") );
	SO_ENGINE_ADD_INPUT(  search, () );
	label.setNum(0);

	SO_ENGINE_ADD_OUTPUT( overlays, SoMFNode );

	m_ReadInstance = FALSE;
}

SoXipImageOverlaySearch::~SoXipImageOverlaySearch()
{

}

void
SoXipImageOverlaySearch::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipImageOverlaySearch, SoEngine, "Engine" );
}

void
SoXipImageOverlaySearch::inputChanged( SoField* whichField )
{
	if( whichField == &search )
		overlays.enable( TRUE );
}

void
SoXipImageOverlaySearch::evaluate()
{
	// Remove all the previous overlays
	SO_ENGINE_OUTPUT( overlays, SoMFNode, setNum(0) );

	// Do not evaluate at loading
	if( m_ReadInstance )
	{
		m_ReadInstance = FALSE;
		overlays.enable( FALSE );
		return ;
	}   

	SoXipDataImage* refData = 0;
	SoXipDataImage* imageData = image.getValue();
			
	while( (refData = (SoXipDataImage *) imageData->getRefByType( SoXipDataImage::getClassTypeId() )) )
		imageData = refData;

	// Read overlays from Dicom
	SbString overlayStr = imageData->getProperty("overlays");
	SoNodeList dataOverlays = XipOverlayUtils::loadOverlaysFromString( 
		overlayStr.getString(), overlayStr.getLength(), TRUE );

	// Match search criteria
	SoNodeList matches = XipOverlayUtils::filterOverlays( dataOverlays,
		label, type.getValue(), caption.getValue() );

	SoMFNode accum;
	for( int i = 0; i < matches.getLength(); ++ i )
	{
		accum.set1Value( accum.getNum(), matches[i] );
	}

	SO_ENGINE_OUTPUT( overlays, SoMFNode, copyFrom(accum) );

	overlays.enable( FALSE );
}

SbBool 
SoXipImageOverlaySearch::readInstance( SoInput* in, unsigned short flags )
{
	m_ReadInstance = TRUE;

	return SoEngine::readInstance( in, flags );
}
