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
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include "SoXipIcon.h"
#include "SoXipIconsResource.h"

SO_NODE_SOURCE( SoXipIcon );

SoXipIcon::SoXipIcon()
{
	SO_NODE_CONSTRUCTOR( SoXipIcon );

	SO_NODE_DEFINE_ENUM_VALUE( IconType, IC_NONE );
	SO_NODE_DEFINE_ENUM_VALUE( IconType, IC_COPY );
	SO_NODE_DEFINE_ENUM_VALUE( IconType, IC_CUT );
	SO_NODE_DEFINE_ENUM_VALUE( IconType, IC_PASTE );

	SO_NODE_SET_SF_ENUM_TYPE( icon, IconType );	

	SO_NODE_ADD_FIELD(             icon, (IC_NONE) );
	SO_NODE_ADD_FIELD(    isTransparent, (FALSE) );
	SO_NODE_ADD_FIELD( transparentColor, (0, 0, 0) );

	mTexture = new SoTexture2;
	mTexture->ref();

	mFieldSensors[0] = new SoFieldSensor( fieldSensorsCB, this );
	mFieldSensors[0]->attach( &icon );
	mFieldSensors[1] = new SoFieldSensor( fieldSensorsCB, this );
	mFieldSensors[1]->attach( &isTransparent );
	mFieldSensors[2] = new SoFieldSensor( fieldSensorsCB, this );
	mFieldSensors[2]->attach( &transparentColor );
}


SoXipIcon::~SoXipIcon()
{
	if( mTexture )
		mTexture->unref();

	for( int i = 0; i < 3; ++ i )
	{
		if( mFieldSensors[i] )
		{
			delete mFieldSensors[i];
			mFieldSensors[i] = 0;
		}
	}
}

void
SoXipIcon::initClass()
{
	SO_NODE_INIT_CLASS( SoXipIcon, SoNode, "Node" );
}

void
SoXipIcon::callback( SoCallbackAction* action )
{
    action->traverse( mTexture );
}

void
SoXipIcon::GLRender( SoGLRenderAction* action )
{
	action->traverse( mTexture );
}

static bool
isEqual( unsigned char a[3], unsigned char b[3] )
{
	return a[0] == b[0] && a[1] == b[1] &&  a[2] == b[2];
}

void
SoXipIcon::fieldChanged( SoField* whichField )
{
	char* rgbPtr;

	switch( icon.getValue() )
	{
	case IC_NONE:
		mTexture->image.setValue( SbVec2s( 0, 0 ), 0, 0 );
		return ;

	case IC_COPY:
		rgbPtr = copy_rgb;
		break ;

	case IC_CUT:
		rgbPtr = cut_rgb;
		break ;

	case IC_PASTE:
		rgbPtr = paste_rgb;
		break ;
	}

	SbVec2s dimensions( xipIconWidth, xipIconHeight );

	unsigned char* rgbaBuffer = new unsigned char[ dimensions[0] * dimensions[1] * 4 ];
	if( !rgbaBuffer )
	{
		SoDebugError::post( __FILE__, "Cannot allocate memory" );
		return ;
	}

	bool hasTransparent = isTransparent.getValue() == TRUE;
	unsigned char tColor[3] = {
		transparentColor.getValue()[0] * 255,
		transparentColor.getValue()[1] * 255,
		transparentColor.getValue()[2] * 255
	};

	unsigned char* ptr = rgbaBuffer;	
	for( int j = 0; j < dimensions[1]; ++ j )
	for( int i = 0; i < dimensions[0]; ++ i )
	{
		unsigned char pixel[3];

		XIP_GET_PIXEL( rgbPtr, pixel );

		*ptr ++ = pixel[0];
		*ptr ++ = pixel[1];
		*ptr ++ = pixel[2];
		
		*ptr ++ = hasTransparent && isEqual( pixel, tColor ) ? 0 : 255;
	}

	mTexture->image.setValue( dimensions, 4, rgbaBuffer );	
	mTexture->wrapS.setValue( SoTexture2::CLAMP );
	mTexture->wrapT.setValue( SoTexture2::CLAMP );

	delete [] rgbaBuffer;
}

void
SoXipIcon::fieldSensorsCB( void* userData, SoSensor* sensor )
{
	((SoXipIcon *) userData)->fieldChanged( 
		((SoFieldSensor *) sensor)->getAttachedField() );
}
