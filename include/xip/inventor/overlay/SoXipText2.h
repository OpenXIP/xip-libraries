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
*	@file    SoXipText2.h
*	@brief   Text node
*	@author  Thomas Moeller
**/

#ifndef SOXIPTEXT2_H
#define SOXIPTEXT2_H

#include <xip/inventor/overlay/SoXipFontTypeElement.h>
#include <Inventor/SbBox.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/sensors/SoFieldSensor.h>

/**
*	@class SoXipText2
*
* Text node
*
**/
class SoXipText2 : public SoShape
{
	SO_NODE_HEADER( SoXipText2 );

public:
	/// Horizontal and vertical alignment types
	enum alignmentType 
	{
		LEFT, 
		RIGHT,
		CENTER,
		TOP,
		BOTTOM
	};

	/// Constructor
	SoXipText2();

	/// String to be displayed
	SoSFString		string;
	/// Horizontal alignement
	SoSFEnum		justification;
	/// Vertical alignement
	SoSFEnum		vAlignment;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	virtual ~SoXipText2();
	
	virtual SbBool createFont( const SbName& fontName, SoXipFontTypeElement::FontType type, int fontSize );
	virtual void deleteFont();

	SbName			mCurrentFontName;
	int				mCurrentFontType;
	class FTFont*	mFont;

	virtual void generatePrimitives( SoAction* );
	virtual void computeJustification( SoGLRenderAction* action, SbVec3f& width, SbVec3f& height );	
	virtual void GLRender( SoGLRenderAction* action );
	virtual void computeBBox( SoAction* action, SbBox3f& box, SbVec3f& center );

	SbBox3f			mBBox;

	virtual void onStringChange();

	const char*		mCurrentString;

	SoFieldSensor*	mStringSensor;

private:
	static void stringSensorCB( void* userData, SoSensor* );	
};

#endif // SOXIPTEXT2_H

