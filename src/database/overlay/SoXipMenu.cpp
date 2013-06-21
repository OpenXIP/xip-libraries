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
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTranslation.h>
#include "SoXipMenu.h"

SO_NODE_SOURCE( SoXipMenu );

SoXipMenu::SoXipMenu()
{
	SO_NODE_CONSTRUCTOR( SoXipMenu );

	SO_XIP_KIT_ADD_TYPE_ENTRY( mItemSeparator, SoSeparator, mMenuSeparator );
}

SoXipMenu::~SoXipMenu()
{

}

void
SoXipMenu::initClass()
{
	SO_NODE_INIT_CLASS( SoXipMenu, SoXipMenuBase, "SoXipMenuBase" );
}

void
SoXipMenu::onMenuChange()
{
	mItemSeparator->removeAllChildren();

	for( int i = 0; i < size(); ++ i )
	{
		SoTranslation* offset = new SoTranslation;
		offset->translation.setValue( 0, getItem(i)->getHeight(), 0 );

		SoGroup* itemGroup = new SoGroup;
		itemGroup->addChild( getItem(i) );
		itemGroup->addChild( offset );

		mItemSeparator->addChild( itemGroup );
	}
}
