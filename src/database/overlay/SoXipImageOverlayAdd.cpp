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
// Disable stl warnings
#pragma warning (disable:4786)

#include <map>
#include <Inventor/fields/SoSFString.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include "SoXipImageOverlayAdd.h"
#include "SoXipShapeList.h"
#include <xip/inventor/overlay/XipOverlayUtils.h>

SO_ENGINE_SOURCE( SoXipImageOverlayAdd );

SoXipImageOverlayAdd::SoXipImageOverlayAdd ()
{
	SO_ENGINE_CONSTRUCTOR( SoXipImageOverlayAdd );

	SO_ENGINE_ADD_INPUT( image, (0) );
	SO_ENGINE_ADD_INPUT( overlays, (0) );
	SO_ENGINE_ADD_INPUT( overwrite, (TRUE) );
	SO_ENGINE_ADD_INPUT( add, () );
	overlays.setNum(0);

	SO_ENGINE_ADD_OUTPUT( status, SoSFString );

	m_ReadInstance = FALSE;
}

SoXipImageOverlayAdd::~SoXipImageOverlayAdd ()
{

}

void
SoXipImageOverlayAdd::initClass ()
{
	SO_ENGINE_INIT_CLASS( SoXipImageOverlayAdd, SoEngine, "SoEngine" );
}

void
SoXipImageOverlayAdd::inputChanged( SoField* whichField )
{
	if( whichField == &add )
		status.enable( TRUE );
}

struct SbStringLessFunctor : public std::binary_function< SbString, SbString, bool >
{
	bool operator()( const SbString& s1, const SbString& s2 ) const
	{
		return strcmp( s1.getString(), s2.getString() ) < 0;
	}
};

void
SoXipImageOverlayAdd::evaluate()
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

			// Add new overlays and create a map label -> node
			std::map< SbString, SoNode*, SbStringLessFunctor > labelMap;

			SoNodeList nodes;
			for( int i = 0; i < overlays.getNum(); ++ i )
			{
				SoXipShapeList* shapeList = (SoXipShapeList *) overlays[i];
				if( shapeList )
				{
					nodes.append( shapeList );
					labelMap[ shapeList->label.getValue() ] = shapeList;
				}
			}

			// Retrieve existing overlays from Dicom if necessary
			if( overwrite.getValue() == FALSE )
			{
				SbString overlayStr = imageData->getProperty( "overlays" );
				SoNodeList existingNodes = XipOverlayUtils::loadOverlaysFromString(
					overlayStr.getString(), overlayStr.getLength(), TRUE );

				for( int i = 0; i < existingNodes.getLength(); ++ i )
				{
					SoXipShapeList* shapeList = (SoXipShapeList *) existingNodes[i];
					if( !shapeList->isOfType( SoXipShapeList::getClassTypeId() ) )
					{
						SoDebugError::post( __FILE__, "Not an overlay shape list. Ignore." );
						continue ;
					}

					const SbString& label = shapeList->label.getValue();

					SoXipShapeList* existingShapeList = (SoXipShapeList *) labelMap[label];
					if( existingShapeList )
					{
						for( int j = 0; j < shapeList->getNumChildren(); ++ j )
							existingShapeList->addChild( shapeList->getChild(j) );
					}
					else
					{
						nodes.append( shapeList );
					}
				}
			}

			SbString overlayStr = XipOverlayUtils::saveOverlaysToString( nodes );
			imageData->setProperty( "overlays", overlayStr );
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
SoXipImageOverlayAdd::readInstance( SoInput* in, unsigned short flags )
{
	m_ReadInstance = TRUE;

	return SoEngine::readInstance( in, flags );
}
