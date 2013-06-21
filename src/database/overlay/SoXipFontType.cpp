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
/**
*	@file	SoXipFontType.cpp
*	@brief	Implementation of the SoXipFontType class
*	@author	Julien Gein
**/

#include <Inventor/actions/SoGLRenderAction.h>
#include "SoXipFontType.h"

SO_NODE_SOURCE( SoXipFontType );

SoXipFontType::SoXipFontType()
{
	SO_NODE_CONSTRUCTOR( SoXipFontType );
    
	SO_NODE_DEFINE_ENUM_VALUE( fontType, BITMAP );
	SO_NODE_DEFINE_ENUM_VALUE( fontType, PIXMAP );
	SO_NODE_DEFINE_ENUM_VALUE( fontType, TEXTURE );
	SO_NODE_SET_SF_ENUM_TYPE( type, fontType );

    SO_NODE_ADD_FIELD( type, (BITMAP) );
}

SoXipFontType::~SoXipFontType()
{

}

void SoXipFontType::initClass()
{
	SO_NODE_INIT_CLASS( SoXipFontType, SoNode, "SoNode" );

	SO_ENABLE( SoGLRenderAction, SoXipFontTypeElement );
}

void
SoXipFontType::GLRender( SoGLRenderAction* action )
{    
    SoXipFontTypeElement::set( action->getState(), this, 
		(SoXipFontTypeElement::FontType) type.getValue() );
}
