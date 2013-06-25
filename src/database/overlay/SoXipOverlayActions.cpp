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
#include <xip/inventor/overlay/SoXipShape.h>
#include "SoXipShapeList.h"
#include "SoXipOverlayActions.h"

SO_ENGINE_SOURCE( SoXipOverlayActions );

SoXipOverlayActions::SoXipOverlayActions()
{
	SO_ENGINE_CONSTRUCTOR( SoXipOverlayActions );

	SO_ENGINE_ADD_INPUT( overlays, (0) );
	SO_ENGINE_ADD_INPUT( show, () );
	SO_ENGINE_ADD_INPUT( hide, () );
	SO_ENGINE_ADD_INPUT( select, () );
	SO_ENGINE_ADD_INPUT( unselect, () );

	SO_ENGINE_ADD_OUTPUT( status, SoSFString );

	mActionTrigger = 0;
}

SoXipOverlayActions::~SoXipOverlayActions()
{

}

void
SoXipOverlayActions::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipOverlayActions, SoEngine, "Engine" );
}

void
SoXipOverlayActions::doAction( SoXipShape* shape )
{
	if( mActionTrigger == &show )
		shape->on.setValue( TRUE );
	else if( mActionTrigger == &hide )
		shape->on.setValue( FALSE );
	else if( mActionTrigger == &select )
		shape->select( TRUE );
	else if( mActionTrigger == &unselect )
		shape->select( FALSE );
}

void
SoXipOverlayActions::inputChanged( SoField* whichField )
{
	if( whichField->isOfType( SoSFTrigger::getClassTypeId() ) )
	{
		status.enable( TRUE );
		mActionTrigger = (SoSFTrigger *) whichField;
	}
}

void
SoXipOverlayActions::evaluate()
{
	int numOverlays = overlays.getNum();

	for( int i = 0; i < numOverlays; ++ i )
	{
		SoXipShapeList* shapeList = (SoXipShapeList *) overlays[i];

		if( !shapeList->isOfType( SoXipShapeList::getClassTypeId() ) )
			continue ;

		int numShapes = shapeList->getNumChildren();
		for( int j = 0; j < numShapes; ++ j )
		{
			SoXipShape* shape = (SoXipShape *) shapeList->getChild(j);
			doAction( shape );
		}
	}

	mActionTrigger = 0;
	status.enable( FALSE );
}

