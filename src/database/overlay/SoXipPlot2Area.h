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
*	@file	SoXipPlot2Area.h
*	@brief	Declaration of the SoXipPlot2Area class
*	@author	Julien Gein
**/

#ifndef SOXIPPLOT2AREA_H
#define SOXIPPLOT2AREA_H

#include <xip/inventor/overlay/SbXipPlot2LegendInfo.h>
#include <xip/inventor/overlay/XipPrimitiveDraw.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SbColor.h>
#include <Inventor/SbBox.h>

class SoOrthographicCamera;
class SoCoordinate3;
class SoLineSet;
class SoTranslation;
class SoBaseColor;
class SoFaceSet;
class SoScale;

class SoXipPlot2Area : public SoGroup
{
	SO_NODE_HEADER(SoXipPlot2Area);

public:
	enum FlagsEnum
	{
		SCROLL_X	= 1,
		SCROLL_Y	= 2,
		FLIP_Y		= 4,
		NO_LEGEND	= 8
	};

	enum ManipMode
	{
		NONE,
		SCROLL_X_RESIZE_LEFT,
		SCROLL_X_RESIZE_RIGHT,
		SCROLL_X_MOVE,
		SCROLL_Y_RESIZE_BOTTOM,
		SCROLL_Y_RESIZE_TOP,
		SCROLL_Y_MOVE,
		LEGEND_MOVE
	};

	SoXipPlot2Area();	

	SoSFString		title;
	SoSFString		labelX;
	SoSFString		labelY;
	SoSFBitMask		flags;
	SoSFVec4f		padding;
	SoSFVec2f		legendPos;
	SoSFVec2f		scrollPosX;
	SoSFVec2f		scrollPosY;
	SoMFColor		scrollColors;

	static void initClass();

protected:
	virtual ~SoXipPlot2Area();

	virtual void handleEvent( SoHandleEventAction* action );
	virtual void GLRender( SoGLRenderAction* action );
	virtual void GLRenderText( SoGLRenderAction* action, SbVec3f position, const char* string );

	// Structure collecting information for the legend
	typedef std::vector< SbXipPlot2LegendInfo > LegendInfoVec;

	void GLRenderLegend( SoGLRenderAction* action, const LegendInfoVec& legendInfo );

	SbViewportRegion		mViewport;
	SbViewportRegion		mChildrenViewport;

	SbBox3f					mPlotBBox;

	SbVec2s					mBorderBottomLeft;
	SbVec2s					mBorderTopRight;
	SbVec2s					mBorderScrollBar;

	SbVec2f					mMouseDownPos;

	// nodes
	SoOrthographicCamera*	mCamera;
	SoCoordinate3*			mCoord;
	SoLineSet*				mLineSet;
	SoTranslation*			mTranslation;
	SoNode*					mText;
	SoBaseColor*			mColor;
	SoFaceSet*				mFaceSet;
	SoScale*				mScale;

	SbVec2s					mScrollSize;
	SbVec2s					mScrollBorder;
	int						mScrollDiffToStart;
	float					mFontSize;

	SbBox3f					mLegendBBox;

	XipPrimitiveDraw		mPrimitiveDraw;

	ManipMode				mManipMode;

};

#endif // SOXIPPLOT2AREA_H
