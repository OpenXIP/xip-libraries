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
*	@file	SoXipLutColorBar.h
*	@brief	Declaration of the SoXipLutColorBar class
*	@author	Julien Gein
**/

#ifndef SOXIPLUTCOLORBAR_H
#define SOXIPLUTCOLORBAR_H

#include <xip/inventor/core/SoXipSubKit.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/sensors/SoFieldSensor.h>

// forward references
class SbXipImage;

class SoXipLutColorBar : public SoXipKit
{
	SO_NODE_HEADER( SoXipLutColorBar );

	SO_XIP_KIT_ENTRY_HEADER( mTopSeparator );

	// Camera
	SO_XIP_KIT_ENTRY_HEADER( mCamera );

	// Coordinates
	SO_XIP_KIT_ENTRY_HEADER( mCoord );

	// Border
	SO_XIP_KIT_ENTRY_HEADER( mBorderSeparator );
	SO_XIP_KIT_ENTRY_HEADER( mBorderColor );
	SO_XIP_KIT_ENTRY_HEADER( mBorderLines );

	// Texture Quad
	SO_XIP_KIT_ENTRY_HEADER( mTextureSeparator );
	SO_XIP_KIT_ENTRY_HEADER( mTexture );	
	SO_XIP_KIT_ENTRY_HEADER( mTexCoord );
	SO_XIP_KIT_ENTRY_HEADER( mTriangleSet );

	// Bottom Label
	SO_XIP_KIT_ENTRY_HEADER( mBottomTextSeparator );
	SO_XIP_KIT_ENTRY_HEADER( mBottomTextOffset );
	SO_XIP_KIT_ENTRY_HEADER( mBottomText );

	// Top Label
	SO_XIP_KIT_ENTRY_HEADER( mTopTextSeparator );
	SO_XIP_KIT_ENTRY_HEADER( mTopTextOffset );
	SO_XIP_KIT_ENTRY_HEADER( mTopText );

public:
	enum BarPosition
	{
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};

	SoXipLutColorBar();

	SoSFEnum					position;
	SoSFVec2f					origin;
	SoSFVec2f					size;
	SoSFBool					showAlpha;
	SoSFColor					borderColor;
	SoSFString					bottomLabel;
	SoSFString					topLabel;

	static void initClass();

protected:
	~SoXipLutColorBar();

	virtual void setOrthographicCamera();

	virtual void GLRender( SoGLRenderAction* action );
	virtual void GLRenderSub( SoGLRenderAction* action );

	virtual void fieldChanged( SoField* whichField );

    void loadTexture( SbXipImage* image );

	SoXipDataImage*				mDataTexture;

	unsigned int				mLutId;

private:
	SoFieldSensor*				mFieldSensors[2];

	static void fieldSensorCB( void* userData, SoSensor* sensor );

	SbBool						mReloadTexture;

};

#endif // SOXIPLUTCOLORBAR_H
