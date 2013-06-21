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
#include "SoXipOverlayProperties.h"
#include "SoXipShapeList.h"
#include <xip/inventor/overlay/SoXipShape.h>


SO_ENGINE_SOURCE( SoXipOverlayProperties );

SoXipOverlayProperties::SoXipOverlayProperties()
{
	SO_ENGINE_CONSTRUCTOR( SoXipOverlayProperties );

	SO_ENGINE_ADD_INPUT( overlays, (0) );
	SO_ENGINE_ADD_INPUT( label, ("") );
	SO_ENGINE_ADD_INPUT( addLabel, () );
	SO_ENGINE_ADD_INPUT( clearLabel, () );
	SO_ENGINE_ADD_INPUT( caption, ("") );
	SO_ENGINE_ADD_INPUT( setCaption, () );
	SO_ENGINE_ADD_INPUT( rank, (-1) );
	SO_ENGINE_ADD_INPUT( setRank, () );
	overlays.setNum(0);

	SO_ENGINE_ADD_OUTPUT( status, SoSFString );

	m_Trigger = 0;
}

SoXipOverlayProperties::~SoXipOverlayProperties()
{

}

void
SoXipOverlayProperties::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipOverlayProperties, SoEngine, "Engine" );
}

void
SoXipOverlayProperties::inputChanged( SoField* whichField )
{
	if( whichField == &addLabel ||
		whichField == &clearLabel ||
		whichField == &setCaption ||
		whichField == &setRank )
	{
		status.enable( TRUE );
		m_Trigger = whichField;
	}	
}

void
SoXipOverlayProperties::evaluate()
{
	if( m_Trigger == &addLabel )
	{
		for( int i = 0; i < overlays.getNum(); ++ i )
		{
			SoXipShapeList* shapeList = (SoXipShapeList *) overlays[i];
			if( !shapeList->isOfType( SoXipShapeList::getClassTypeId() ) )
				continue ;

			int numShapes = shapeList->getNumChildren();
			for( int j = 0; j < numShapes; ++ j )
			{
				SoXipShape* shape = (SoXipShape *) shapeList->getChild(j);

				// Verify the label does not already exist
				SbBool ignore = FALSE;
				for( int k = 0; k < shape->label.getNum(); ++ k )
				{
					if( shape->label[k] == label.getValue() )
					{
						ignore = TRUE;
						break ;
					}
				}

				// Add new label
				if( ignore == FALSE )
				{
					shape->label.set1Value( shape->label.getNum(), label.getValue() );
				}
			}
		}
	}
	else if( m_Trigger == &clearLabel )
	{
		for( int i = 0; i < overlays.getNum(); ++ i )
		{
			SoXipShapeList* shapeList = (SoXipShapeList *) overlays[i];
			if( !shapeList->isOfType( SoXipShapeList::getClassTypeId() ) )
				continue ;

			int numShapes = shapeList->getNumChildren();
			for( int j = 0; j < numShapes; ++ j )
			{
				SoXipShape* shape = (SoXipShape *) shapeList->getChild(j);
				shape->label.setNum(0);
			}
		}
	}
	else if( m_Trigger == &setCaption )
	{
		for( int i = 0; i < overlays.getNum(); ++ i )
		{
			SoXipShapeList* shapeList = (SoXipShapeList *) overlays[i];
			if( !shapeList->isOfType( SoXipShapeList::getClassTypeId() ) )
				continue ;

			int numShapes = shapeList->getNumChildren();
			for( int j = 0; j < numShapes; ++ j )
			{
				SoXipShape* shape = (SoXipShape *) shapeList->getChild(j);
				shape->caption.setValue( caption.getValue() );
			}
		}
	}
	else if( m_Trigger == &setRank )
	{
		for( int i = 0; i < overlays.getNum(); ++ i )
		{
			SoXipShapeList* shapeList = (SoXipShapeList *) overlays[i];
			if( !shapeList->isOfType( SoXipShapeList::getClassTypeId() ) )
				continue ;

			int numShapes = shapeList->getNumChildren();
			for( int j = 0; j < numShapes; ++ j )
			{
				SoXipShape* shape = (SoXipShape *) shapeList->getChild(j);
				shape->rank.setValue( rank.getValue() );
			}
		}
	}

	status.enable( FALSE );
}
