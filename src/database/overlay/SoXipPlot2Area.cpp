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
*	@file	SoXipPlot2Area.cpp
*	@brief	Implementation of the SoXipPlot2Area class
*	@author	Julien Gein
**/

#include <vector>
#include <xip/inventor/overlay/SoXipPlot2Element.h>
#include <xip/inventor/overlay/SoXipPlot2AreaElement.h>
#include <xip/inventor/overlay/SbXipMarkerShapes.h>
#include <xip/inventor/core/SoXipCursor.h>
#include <xip/inventor/core/SoXipActiveViewportElement.h>
#include <Inventor/errors/SoErrors.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoComplexityElement.h>
#include <Inventor/elements/SoFontSizeElement.h>
#include <Inventor/elements/SoLinePatternElement.h>
#include <Inventor/elements/SoLineWidthElement.h>
#include <Inventor/elements/SoLightModelElement.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoScale.h>
#include "SoXipDropShadowElement.h"
#include "SoXipPlot2Area.h"

#define CLAMP(a,minBound,maxBound) { if( a < minBound ) a = minBound; else if( a > maxBound ) a = maxBound; }

SO_NODE_SOURCE(SoXipPlot2Area);

// computes axis parameters such as start value and spacing for ticks
// in world and pixel units
static void computeAxisParams( float minDistance, float minVal,
  float span, float spanPixels, float &tickSpacing,
	float &tickSpacingPixels, float &startTick,
	float &startOffsetPixels, int &numTicks )
{
	tickSpacing = 0;
	tickSpacingPixels = 0;
	startTick = 0;
	startOffsetPixels = 0;
	numTicks = 0;

	if( minDistance <= 0 )
	{
		return ;
	}

	// min distance between ticks is minDistance pixels
	float maxNumTicks = (int) (spanPixels / minDistance);

	if( maxNumTicks > 0 )
	{
		float spacing = span / (float) maxNumTicks;

		int rank = ceil( log10(spacing) );

		tickSpacing = pow( 10, (double) rank );

		if( spacing / tickSpacing < 0.2 )
			tickSpacing *= 0.2;
		else if( spacing / tickSpacing < 0.5 )
			tickSpacing *= 0.5;

		if( span )
		{
		  tickSpacingPixels = spanPixels * (tickSpacing / span);
		}

		if( tickSpacingPixels <= 0 )
		{
			//int breakhere =0;
		}
			
		float startPlot = minVal;
		int n = startPlot / tickSpacing;
		startTick = n * tickSpacing;
		startOffsetPixels = spanPixels * ((startTick - startPlot)  / span);

		if (startOffsetPixels < 0)
		{
			startOffsetPixels += tickSpacingPixels; 
			startTick += tickSpacing;
		}

		if( tickSpacingPixels )
		{
		numTicks = 1.f + (spanPixels + 0.5f - startOffsetPixels) /
					 	tickSpacingPixels;
		}
	}
}


// formats a numerical value (trims zeros at end)
static void formatValue(char *str, double value)
{
	sprintf(str, "%.*f", 4, value);

	// remove zeros at the end of fraction
	char *frac = strchr(str, '.');
	for (char *end = str + strlen(str) - 1;
			(end >= frac) && ((*end == '0') || (*end == '.'));
			end--) *end = 0;
}


void SoXipPlot2Area::initClass()
{
	SO_NODE_INIT_CLASS(SoXipPlot2Area, SoGroup, "Group");

	SO_ENABLE( SoGLRenderAction, SoXipDropShadowElement);
	SO_ENABLE( SoGLRenderAction, SoXipPlot2AreaElement);
}


SoXipPlot2Area::SoXipPlot2Area()
{
	SO_NODE_CONSTRUCTOR(SoXipPlot2Area);

	mBorderBottomLeft = SbVec2s(50, 50);
	mBorderTopRight = SbVec2s(20, 20);
	mBorderScrollBar = SbVec2s(10, 10);
	mManipMode = NONE;
	mFontSize = 10.f;

	mMouseDownPos = SbVec2f(0, 0);
	mViewport = SbViewportRegion(1, 1);

	SO_NODE_ADD_FIELD(title, (""));
	SO_NODE_ADD_FIELD(labelX, (""));
	SO_NODE_ADD_FIELD(labelY, (""));

	SO_NODE_DEFINE_ENUM_VALUE(FlagsEnum,  SCROLL_X);
	SO_NODE_DEFINE_ENUM_VALUE(FlagsEnum,  SCROLL_Y);
	SO_NODE_DEFINE_ENUM_VALUE(FlagsEnum,    FLIP_Y);
	SO_NODE_DEFINE_ENUM_VALUE(FlagsEnum, NO_LEGEND);

	SO_NODE_SET_SF_ENUM_TYPE(flags, FlagsEnum);

	SO_NODE_ADD_FIELD(flags, (SCROLL_X | SCROLL_Y));
	SO_NODE_ADD_FIELD(padding, (SbVec4f(0, 0, 0, 0)));
	SO_NODE_ADD_FIELD(scrollPosX, (SbVec2f(0, 1)));
	SO_NODE_ADD_FIELD(scrollPosY, (SbVec2f(0, 1)));
	SO_NODE_ADD_FIELD(legendPos, (SbVec2f(1, 1)));
	SO_NODE_ADD_FIELD(scrollColors, (0.2, 0.2, 0.2));
	scrollColors.set1Value(1, SbColor(0.6, 0.6, 0.6));

	// nodes
	mCamera = new SoOrthographicCamera;
	if (mCamera)
	{
		mCamera->ref();

		mCamera->viewportMapping.setValue(SoCamera::LEAVE_ALONE);
		mCamera->position.setValue(SbVec3f(0, 0, 0));
		mCamera->nearDistance.setValue(-1);
		mCamera->farDistance.setValue(1);
		mCamera->focalDistance.setValue(0);
	}

	mCoord = new SoCoordinate3;
	if (mCoord)
		mCoord->ref();

	mLineSet = new SoLineSet;
	if (mLineSet)
		mLineSet->ref();

	mTranslation = new SoTranslation;
	if (mTranslation)
		mTranslation->ref();

	// create the text node through SoType to avoid dependencies
	SoType type = SoType::fromName("SoXipText2");
	mText = (SoNode*) type.createInstance();
	if (mText)
		mText->ref();

	mColor = new SoBaseColor;
	if (mColor)
		mColor->ref();

	mFaceSet = new SoFaceSet;
	if (mFaceSet)
		mFaceSet->ref();

	mScale = new SoScale;
	if (mScale)
		mScale->ref();
}


SoXipPlot2Area::~SoXipPlot2Area()
{
	if (mCamera)
		mCamera->unref();
	if (mCoord)
		mCoord->unref();
	if (mLineSet)
		mLineSet->unref();
	if (mTranslation)
		mTranslation->unref();
	if (mText)
		mText->unref();
	if (mColor)
		mColor->unref();
	if (mFaceSet)
		mFaceSet->unref();
	if (mScale)
		mScale->unref();
}


// renders a string at the given position
void SoXipPlot2Area::GLRenderText(SoGLRenderAction *action,
								SbVec3f position, const char *string)
{
	if (!action || !string || !mTranslation || !mText) 
		return;

	action->getState()->push();

	mTranslation->translation.setValue(position);
	action->traverse(mTranslation);

	SbString s("string \"");
	s += SbString(string);
	s += SbString("\" ");
	mText->set(s.getString());
	action->traverse(mText);

	action->getState()->pop();
}

void
SoXipPlot2Area::GLRenderLegend( SoGLRenderAction* action,
								const LegendInfoVec& legendInfo )
{
	float fontSize = SoFontSizeElement::get( action->getState() );

	SbVec2s borderBottomLeft = mBorderBottomLeft;
	borderBottomLeft[1] += fontSize;

	const SbVec2s& plotSize = mChildrenViewport.getViewportSizePixels();

	const SbVec2f& legendNormPos = legendPos.getValue();

	const SbVec2f legendMargin(10, 10);
	const SbVec2f legendFrameSize(45, 0);		

	if( !(flags.getValue() & NO_LEGEND) )
	{	
		mText->set("justification RIGHT  vAlignment CENTER");

		SbBox3f legendTextBBox;

		// Compute legend text bouding box
		for( int i = 0; i < (int) legendInfo.size(); i ++ )
		{
			SbVec3f posOutsideViewport( 100000, 10000, 0 );
			GLRenderText( action, posOutsideViewport,
											legendInfo[i].label.getString() );

			SoGetBoundingBoxAction gba( SoViewportRegionElement::get(
															action->getState() ) );
			gba.apply( mText );

			legendTextBBox = gba.getBoundingBox();
		}

		SbVec2f legendTextSize;
		float dummy;
		legendTextBBox.getSize( legendTextSize[0], legendTextSize[1], dummy );

		for( int j = 0; j < (int) legendInfo.size(); j ++ )
		{
			SbVec2f legendOffset = SbVec2f( borderBottomLeft[0],
											borderBottomLeft[1] ) + legendMargin;
			legendOffset[0] += legendTextSize[0]; // Since text is right-aligned
			legendOffset[1] += .5 * fontSize + j * (fontSize + 2);

			SbVec2f legendSize = 2 * legendMargin;
			legendSize[0] += legendTextSize[0] + legendFrameSize[0];
			legendSize[1] += legendInfo.size() * (fontSize + 2);			

			SbVec3f pos = SbVec3f(
				legendOffset[0] + legendNormPos[0] * (plotSize[0] - legendSize[0]),
				legendOffset[1] + legendNormPos[1] * (plotSize[1] - legendSize[1]),
				0 );

			GLRenderText(action, pos, legendInfo[j].label.getString());

			SoGetBoundingBoxAction gba( SoViewportRegionElement::get(
															action->getState() ) );
			gba.apply( mText );

			SbMatrix translationMatrix;
			translationMatrix.setTranslate(
											mTranslation->translation.getValue() );
			SbBox3f bbox = gba.getBoundingBox();
			bbox.transform( translationMatrix );

			mLegendBBox.extendBy( bbox );

			if( legendInfo[j].isArea )
			{
				mPrimitiveDraw.quad( action, pos + SbVec3f(10, -4, 0),
												SbVec2f(30, 8), legendInfo[j].areaColor );

				SoMFVec3f borderLineCoords;
				borderLineCoords.setNum(5);
				borderLineCoords.set1Value( 0, pos + SbVec3f(10, -4, 0) );
				borderLineCoords.set1Value( 1, pos + SbVec3f(40, -4, 0) );
				borderLineCoords.set1Value( 2, pos + SbVec3f(40,  4, 0) );
				borderLineCoords.set1Value( 3, pos + SbVec3f(10,  4, 0) );
				borderLineCoords.set1Value( 4, pos + SbVec3f(10, -4, 0) );

				mPrimitiveDraw.lines( action, borderLineCoords,
												legendInfo[j].lineColor );

				// Update legend bounding box
				for( int index = 0; index < 4; ++ index )
					mLegendBBox.extendBy( borderLineCoords[index] );
			}
			else
			{
				if( legendInfo[j].isLine )
				{
					SbVec3f p1( pos + SbVec3f( 5, 0, 0) );
					SbVec3f p2( pos + SbVec3f(45, 0, 0) );

					mPrimitiveDraw.line( action, p1, p2,
						legendInfo[j].lineColor, 0,
						legendInfo[j].lineWidth, 
						legendInfo[j].linePattern );

					// Update legend bounding box
					mLegendBBox.extendBy( p1 );
					mLegendBBox.extendBy( p2 );
				}

				action->getState()->push();
				glDisable(GL_DEPTH_TEST);

				mTranslation->translation.setValue(pos + SbVec3f(25, 0, 0));
				action->traverse(mTranslation);

				mScale->scaleFactor.setValue(0.5f * legendInfo[j].markerSize,
											 	0.5f * legendInfo[j].markerSize, 1);
				action->traverse(mScale);

				mColor->rgb.setValue(legendInfo[j].markerColor);
				action->traverse(mColor);

				SbXipMarkerShapes::getVertices(legendInfo[j].markerType, mCoord->point);
				action->traverse(mCoord);

				SbXipMarkerShapes::getNumVertices(legendInfo[j].markerType, mFaceSet->numVertices);
				action->traverse(mFaceSet);

				action->getState()->pop();
			}
		}

		if( mManipMode == LEGEND_MOVE )
		{
			SbVec3f lMin = mLegendBBox.getMin() - SbVec3f(10, 10, 0);
			SbVec3f lMax = mLegendBBox.getMax() + SbVec3f(10, 10, 0);

			SoMFVec3f legendFrameCoords;
				legendFrameCoords.setNum(5);
				legendFrameCoords.set1Value( 0, SbVec3f(lMin[0], lMin[1], 0) );
				legendFrameCoords.set1Value( 1, SbVec3f(lMax[0], lMin[1], 0) );
				legendFrameCoords.set1Value( 2, SbVec3f(lMax[0], lMax[1], 0) );
				legendFrameCoords.set1Value( 3, SbVec3f(lMin[0], lMax[1], 0) );
				legendFrameCoords.set1Value( 4, SbVec3f(lMin[0], lMin[1], 0) );

			mPrimitiveDraw.lines( action, legendFrameCoords,
				SbColor(0.5, 0.5, 0.5), 0, 1, 0xf0f0 );
		}
	}
}

// render method (renders children, x/y axis, scroll bars and legend)
void SoXipPlot2Area::GLRender(SoGLRenderAction *action)
{
	// Reset the legend bounding box
	mLegendBBox.makeEmpty();

	int i;

	if (!action || !mCamera || !mCoord || !mLineSet || !mTranslation || !mText || !mColor || !mFaceSet || !mScale) return;

	SoState *state = action->getState();
	if (!state) return;

	float fontSize = SoFontSizeElement::get(state);
	if (SoXipActiveViewportElement::get(state))
	{
		// Need to store font size for active viewport because SoFontSizeElement is not set for the
		// SoHandleEventAction by the SoFont / SoFontStyle node.
		mFontSize = fontSize;
	}

	SbVec2s borderBottomLeft = mBorderBottomLeft;
	SbVec2s borderTopRight = mBorderTopRight;
	borderTopRight[1] += fontSize;
	borderBottomLeft[1] += fontSize;
	if (title.getValue().getLength() > 0)
	{
		borderTopRight[1] += 2.f * fontSize;
	}


	SbViewportRegion vp = SoViewportRegionElement::get(state);
	SbVec2s vpSize = vp.getViewportSizePixels();

	if ((vpSize[0] < (borderBottomLeft[0] + borderTopRight[0] + 2) ) ||
			(vpSize[1] < (borderBottomLeft[1] + borderTopRight[1] + 2)))
	{ 
	  return;
	}

	mChildrenViewport = SbViewportRegion(vp.getWindowSize());
	mChildrenViewport.setViewportPixels(
		vp.getViewportOriginPixels() + borderBottomLeft, 
		vpSize - borderBottomLeft - borderTopRight);

	// compute bounding box of all graphics (all children of this node)
	SoGetBoundingBoxAction ba(mChildrenViewport);
	ba.apply(this);

	SbBox3f childrenBBox = ba.getBoundingBox();
	SbVec3f minPt = childrenBBox.getMin();
	SbVec3f maxPt = childrenBBox.getMax();

	// Here we need to correct the bounding box in case it is flat
	// (It happens when the curves have a uniform Y value for instance)
	if( minPt[1] == maxPt[1] )
	{		
		if( minPt[1] == 0 )
		{
			minPt[1] = -0.1;
			maxPt[1] =  0.2;
		}
		else if( minPt[1] < 0 )
		{
			int num = floor( log10( -minPt[1] ) );
			minPt[1] = minPt[1] - 0.5 * pow( 10.0, num );
			maxPt[1] = 0;
		}
		else
		{
			int num = floor( log10( minPt[1] ) );
			maxPt[1] = minPt[1] + 0.5 * pow( 10.0, num );
			minPt[1] = 0;
		}
	}

	if( minPt[0] == maxPt[0] )
	{		
		if( minPt[0] == 0 )
		{
			minPt[0] = -0.1;
			maxPt[0] =  0.2;
		}
		else if( minPt[0] < 0 )
		{
			int num = floor( log10( -minPt[0] ) );
			minPt[0] = minPt[0] - 0.5 * pow( 10.0, num );
			maxPt[0] = 0;
		}
		else
		{
			int num = floor( log10( minPt[0] ) );
			maxPt[0] = minPt[0] + 0.5 * pow( 10.0, num );
			minPt[0] = 0;
		}
	}

	// modify the bounding box with the padding
	const SbVec4f& padVec = padding.getValue();
	minPt[0] -= padVec[0] * (maxPt[0] - minPt[0]);
	minPt[1] -= padVec[1] * (maxPt[1] - minPt[1]);
	maxPt[0] += padVec[2] * (maxPt[0] - minPt[0]);
	maxPt[1] += padVec[3] * (maxPt[1] - minPt[1]);

	childrenBBox.setBounds(minPt, maxPt);

	if( !childrenBBox.isEmpty() )
	{
		// render plotting area
		state->push();

		SbBool depthTest = glIsEnabled(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);

		mPlotBBox = childrenBBox;

		if (scrollPosX.getValue()[1] < 1)
		{
			SbVec3f minPt = mPlotBBox.getMin();
			SbVec3f maxPt = mPlotBBox.getMax();
			float newWidth = (maxPt[0] - minPt[0]) * scrollPosX.getValue()[1];
			minPt[0] += (maxPt[0] - minPt[0]) * scrollPosX.getValue()[0];
			maxPt[0] = minPt[0] + newWidth;
			mPlotBBox.setBounds(minPt, maxPt);
		}

		if (scrollPosY.getValue()[1] < 1)
		{
			SbVec3f minPt = mPlotBBox.getMin();
			SbVec3f maxPt = mPlotBBox.getMax();
			float newHeight = (maxPt[1] - minPt[1]) * scrollPosY.getValue()[1];

			if( flags.getValue() & FLIP_Y )
			{
				minPt[1] += (maxPt[1] - minPt[1]) * ( 1. - scrollPosY.getValue()[0] - scrollPosY.getValue()[1] );
				maxPt[1] = minPt[1] + newHeight;
			}
			else
			{
				minPt[1] += (maxPt[1] - minPt[1]) * scrollPosY.getValue()[0];
				maxPt[1] = minPt[1] + newHeight;
			}

			mPlotBBox.setBounds(minPt, maxPt);
		}		

		float bbSize[3];
		mPlotBBox.getSize(bbSize[0], bbSize[1], bbSize[2]);

		SoLightModelElement::set(state, SoLightModelElement::BASE_COLOR);		

		SbVec2s plotSize = mChildrenViewport.getViewportSizePixels();

		float xStartTick, xTickSpacing, xTickSpacingPixels, xStartOffsetPixels;
		float yStartTick, yTickSpacing, yTickSpacingPixels, yStartOffsetPixels;
		
		int xNumTicks;
		int yNumTicks;

		int numDigits_min = ceil( log10( fabs( mPlotBBox.getMin()[0] ) ) );
		int numDigits_max = ceil( log10( fabs( mPlotBBox.getMax()[0] ) ) );
		int numDigits = numDigits_max >= numDigits_min ? numDigits_max : numDigits_min;

		if( numDigits < 2 )
			numDigits = 2;

		float minTickSpacing = fontSize * (numDigits + 1);

		// x axis
		computeAxisParams(
			minTickSpacing, mPlotBBox.getMin()[0], bbSize[0], (float) plotSize[0],		// inputs
			xTickSpacing, xTickSpacingPixels, xStartTick, xStartOffsetPixels, xNumTicks);	// outputs

		minTickSpacing = fontSize * 2;

		// y axis
		computeAxisParams(
			minTickSpacing, mPlotBBox.getMin()[1], bbSize[1], (float) plotSize[1],		// inputs
			yTickSpacing, yTickSpacingPixels, yStartTick, yStartOffsetPixels, yNumTicks);	// outputs

		SoXipPlot2AreaElement::set( state, this, childrenBBox, 
			xStartTick, xTickSpacing, xNumTicks,
			yStartTick, yTickSpacing, yNumTicks );

		// adjust camera position and height
		mCamera->height.setValue(bbSize[1]);
		mCamera->aspectRatio.setValue(bbSize[0] / bbSize[1]);
		mCamera->position.setValue(mPlotBBox.getCenter());

		// If the graphics need to be flipped, rotate the camera
		if( flags.getValue() & FLIP_Y )
		{
			SbRotation flipRot( SbVec3f(1, 0, 0), M_PI );
			mCamera->orientation.setValue( flipRot );
		}

		action->traverse(mCamera);
		
		// Restore the camera
		if( flags.getValue() & FLIP_Y )
		{
			mCamera->orientation.setValue( SbVec3f(1, 0, 0), 0 );
		}

		// set plotting viewport area
		SoViewportRegionElement::set(state, mChildrenViewport);

		// default complexity (avoids removal of points in linesets etc.)
		SoComplexityElement::set(state, 1);

		// plot all children
		SoGroup::GLRender(action);

		LegendInfoVec legendInfo;

		// read legend information before popping the state
		if( !(flags.getValue() & NO_LEGEND) )
		{
			SoXipPlot2Element* plot2Element = SoXipPlot2Element::getInstance(state);
			for( int i = 0; i < plot2Element->getNum(); i ++ )
			{
				if( plot2Element->getLabel(i).getLength() )
					legendInfo.push_back( plot2Element->getInfo(i) );
			}
		}

		state->pop();


		// render axis and labels
		state->push();
		glDisable( GL_DEPTH_TEST );

		// set camera to pixel space
		mCamera->height.setValue(vpSize[1]);
		if( vpSize[1] )
		{
		mCamera->aspectRatio.setValue((float) vpSize[0] / (float) vpSize[1]);
		}

		mCamera->position.setValue(SbVec3f((float) vpSize[0] / 2.f,
													 	(float) vpSize[1] / 2.f, 0));
		action->traverse(mCamera);		

		// helper macro to render lineset from poins and numPoints
		std::vector<SbVec3f> points;
		std::vector<int> numPoints;

		#define RENDER_LINESET() \
			mCoord->point.setValues(0, points.size(), &points[0]); \
			mCoord->point.setNum(points.size()); \
			mLineSet->numVertices.setValues(0, numPoints.size(), &numPoints[0]); \
			mLineSet->numVertices.setNum(numPoints.size()); \
			action->traverse(mCoord); \
			action->traverse(mLineSet)

		#define RENDER_LINESET_SHADOW() \
		if (SoXipDropShadowElement::isOn(state)) { \
			GLboolean depthMask = TRUE; \
			glGetBooleanv(GL_DEPTH_WRITEMASK, &depthMask); \
			glDepthMask( FALSE ); \
			action->getState()->push(); \
			mColor->rgb.setValue(SoXipDropShadowElement::getColor(state)); \
			mTranslation->translation.setValue(SbVec3f(SoXipDropShadowElement::getPixelOffset(state)[0], SoXipDropShadowElement::getPixelOffset(state)[1], 0)); \
			action->traverse(mColor); \
			action->traverse(mTranslation); \
			RENDER_LINESET(); \
			action->getState()->pop(); \
			glDepthMask(depthMask); \
		} \
		RENDER_LINESET()


		// x axis
		points.resize(2);
		points[0] = SbVec3f(borderBottomLeft[0], borderBottomLeft[1], 0);
		points[1] = SbVec3f(borderBottomLeft[0] + plotSize[0] + 1, borderBottomLeft[1], 0);
		numPoints.resize(1);
		numPoints[0] = 2;
		RENDER_LINESET_SHADOW();

		// ticks and labels for x axis
		if( xNumTicks > 0 )
		{
			points.resize(xNumTicks * 2);
			numPoints.resize(xNumTicks);
			for (i = 0; i < xNumTicks; i++)
			{
				points[i * 2 + 0] = SbVec3f(borderBottomLeft[0] + xStartOffsetPixels + i * xTickSpacingPixels, borderBottomLeft[1], 0);
				points[i * 2 + 1] = SbVec3f(borderBottomLeft[0] + xStartOffsetPixels + i * xTickSpacingPixels, borderBottomLeft[1] - 4, 0);
				numPoints[i] = 2;
			}
			RENDER_LINESET_SHADOW();
		}

		char str[20];
		mText->set("justification CENTER  vAlignment TOP");
		for (i = 0; i < xNumTicks; i++)
		{
			formatValue(str, xStartTick + xTickSpacing * (double) i);
			GLRenderText(action, SbVec3f(borderBottomLeft[0] + xStartOffsetPixels + i * xTickSpacingPixels, borderBottomLeft[1] - 8, 0), str);
		}

		if (labelX.getValue().getLength() > 0)
		{
			mText->set("justification RIGHT  vAlignment TOP");
			GLRenderText(action, SbVec3f(borderBottomLeft[0] + plotSize[0], borderBottomLeft[1] - 6 - fontSize - 2, 0), labelX.getValue().getString());
		}

		// ticks and labels for y axis

		if( flags.getValue() & FLIP_Y )
		{
			yStartOffsetPixels = (float) plotSize[1] - yStartOffsetPixels;
			yTickSpacingPixels = -yTickSpacingPixels;			
		}

		if( yNumTicks )
		{
			points.resize(yNumTicks * 2);
			numPoints.resize(yNumTicks);
			for (i = 0; i < yNumTicks; i++)
			{
				points[i * 2 + 0] = SbVec3f(borderBottomLeft[0], borderBottomLeft[1] + yStartOffsetPixels + i * yTickSpacingPixels, 0);
				points[i * 2 + 1] = SbVec3f(borderBottomLeft[0] - 4, borderBottomLeft[1] + yStartOffsetPixels + i * yTickSpacingPixels, 0);
				numPoints[i] = 2;
			}
			RENDER_LINESET_SHADOW();
		}

		// y-axis
		points.resize(2);
		points[0] = SbVec3f(borderBottomLeft[0], borderBottomLeft[1], 0);
		points[1] = SbVec3f(borderBottomLeft[0], borderBottomLeft[1] + plotSize[1] + 1, 0);
		numPoints.resize(1);
		numPoints[0] = 2;
		RENDER_LINESET_SHADOW();

		mText->set("justification RIGHT  vAlignment CENTER");
		for (i = 0; i < yNumTicks; i++)
		{
			formatValue(str, yStartTick + yTickSpacing * (double) i);
			GLRenderText(action, SbVec3f(borderBottomLeft[0] - 8, borderBottomLeft[1] + yStartOffsetPixels + i * yTickSpacingPixels, 0), str);
		}

		if (labelY.getValue().getLength() > 0)
		{
			mText->set("justification LEFT  vAlignment BOTTOM");
			GLRenderText(action, SbVec3f(borderTopRight[0], borderBottomLeft[1] + plotSize[1] + (fontSize / 2) + 2, 0), labelY.getValue().getString());
		}

		if (title.getValue().getLength() > 0)
		{
			mText->set("justification CENTER  vAlignment TOP");
			GLRenderText(action, SbVec3f(vpSize[0] / 2, vpSize[1] - (fontSize * 0.5f), 0), title.getValue().getString());
		}

		// render legend
		GLRenderLegend( action, legendInfo );

		// scroll bars
		if( flags.getValue() & SCROLL_Y )
		{
			float offset = plotSize[1] * scrollPosY.getValue()[0];

			SbVec3f origin = SbVec3f( mBorderScrollBar[0] - 5, borderBottomLeft[1], 0);
			SbVec2f size(10, plotSize[1]);

			mPrimitiveDraw.quad( action, origin, size, scrollColors[0] );

			origin += SbVec3f(1, 1, 0);
			size += SbVec2f(-2, -2);

			mPrimitiveDraw.quad( action, origin, size, scrollColors[1] );

			origin = SbVec3f( mBorderScrollBar[0] - 4, borderBottomLeft[1] + offset, 0 );
			size[1] = plotSize[1] * scrollPosY.getValue()[1];
			
			mPrimitiveDraw.quad( action, origin, size, scrollColors[0] );

			// Arrows
			mPrimitiveDraw.triangle( action, 
				SbVec3f(        mBorderScrollBar[0], borderBottomLeft[1] + offset + 3, 0),
				SbVec3f(  3.5 + mBorderScrollBar[0], borderBottomLeft[1] + offset + 7, 0),
				SbVec3f( -3.5 + mBorderScrollBar[0], borderBottomLeft[1] + offset + 7, 0),
				scrollColors[1] );

			mPrimitiveDraw.triangle( action, 
				SbVec3f(        mBorderScrollBar[0], borderBottomLeft[1] + size[1] + offset - 3, 0),
				SbVec3f( -3.5 + mBorderScrollBar[0], borderBottomLeft[1] + size[1] + offset - 7, 0),
				SbVec3f(  3.5 + mBorderScrollBar[0], borderBottomLeft[1] + size[1] + offset - 7, 0),
				scrollColors[1] );

			if( size[1] > 24 )
			{
				mPrimitiveDraw.line( action,
					SbVec3f( mBorderScrollBar[0] - 3, borderBottomLeft[1] + offset + .5*size[1] - 3,  0),
					SbVec3f( mBorderScrollBar[0] + 3, borderBottomLeft[1] + offset + .5*size[1] - 3,  0),
					scrollColors[1] );

				mPrimitiveDraw.line( action,
					SbVec3f( mBorderScrollBar[0] - 3, borderBottomLeft[1] + offset + .5*size[1],  0),
					SbVec3f( mBorderScrollBar[0] + 3, borderBottomLeft[1] + offset + .5*size[1],  0),
					scrollColors[1] );

				mPrimitiveDraw.line( action,
					SbVec3f( mBorderScrollBar[0] - 3, borderBottomLeft[1] + offset + .5*size[1] + 3,  0),
					SbVec3f( mBorderScrollBar[0] + 3, borderBottomLeft[1] + offset + .5*size[1] + 3,  0),
					scrollColors[1] );
			}
		}

		if( flags.getValue() & SCROLL_X )
		{
			float offset = plotSize[0] * scrollPosX.getValue()[0];

			SbVec3f origin = SbVec3f(borderBottomLeft[0], mBorderScrollBar[1] - 5, 0);
			SbVec2f size(plotSize[0], 10);

			mPrimitiveDraw.quad( action, origin, size, scrollColors[0] );

			origin += SbVec3f(1, 1, 0);
			size += SbVec2f(-2, -2);

			mPrimitiveDraw.quad( action, origin, size, scrollColors[1] );

			origin = SbVec3f(borderBottomLeft[0] + offset, mBorderScrollBar[1] - 4, 0);
			size[0] = plotSize[0] * scrollPosX.getValue()[1];

			mPrimitiveDraw.quad( action, origin, size, scrollColors[0] );

			// Arrows
			mPrimitiveDraw.triangle( action,
				SbVec3f( borderBottomLeft[0] + offset + 3,        mBorderScrollBar[1], 0),
				SbVec3f( borderBottomLeft[0] + offset + 7, -3.5 + mBorderScrollBar[1], 0),
				SbVec3f( borderBottomLeft[0] + offset + 7,  3.5 + mBorderScrollBar[1], 0),
				scrollColors[1] );

			mPrimitiveDraw.triangle( action,
				SbVec3f( borderBottomLeft[0] + size[0] + offset - 7, -3.5 + mBorderScrollBar[1], 0),
				SbVec3f( borderBottomLeft[0] + size[0] + offset - 3,        mBorderScrollBar[1], 0),
				SbVec3f( borderBottomLeft[0] + size[0] + offset - 7,  3.5 + mBorderScrollBar[1], 0),
				scrollColors[1] );

			if( size[0] > 24 )
			{
				mPrimitiveDraw.line( action,
					SbVec3f( borderBottomLeft[0] + offset + .5*size[0] - 3, mBorderScrollBar[1] - 3, 0),
					SbVec3f( borderBottomLeft[0] + offset + .5*size[0] - 3, mBorderScrollBar[1] + 3, 0),
					scrollColors[1] );

				mPrimitiveDraw.line( action,
					SbVec3f( borderBottomLeft[0] + offset + .5*size[0], mBorderScrollBar[1] - 3, 0),
					SbVec3f( borderBottomLeft[0] + offset + .5*size[0], mBorderScrollBar[1] + 3, 0),
					scrollColors[1] );

				mPrimitiveDraw.line( action,
					SbVec3f( borderBottomLeft[0] + offset + .5*size[0] + 3, mBorderScrollBar[1] - 3, 0),
					SbVec3f( borderBottomLeft[0] + offset + .5*size[0] + 3, mBorderScrollBar[1] + 3, 0),
					scrollColors[1] );
			}
		}

		state->pop();

		if( depthTest )
			glEnable( GL_DEPTH_TEST );
	}
}

void 
SoXipPlot2Area::handleEvent(SoHandleEventAction *action)
{
	if (!action) return;
	const SoEvent *event = action->getEvent();

	if (!action->getGrabber())
	{
		// The viewport needs to be stored for later use. Once the grabber
		// is set it will no longer be valid in the action.
		mViewport = action->getViewportRegion();
		mMouseDownPos = event->getNormalizedPosition(mViewport);

		SbVec2s borderBottomLeft = mBorderBottomLeft;
		SbVec2s borderTopRight = mBorderTopRight;
		borderTopRight[1] += mFontSize;
		borderBottomLeft[1] += mFontSize;
		if (title.getValue().getLength() > 0)
		{
			borderTopRight[1] += 2.f * mFontSize;
		}

		SbVec2s vpSize = mViewport.getViewportSizePixels();
		mScrollBorder = SbVec2s(borderBottomLeft[0], borderBottomLeft[1]);
		mScrollSize = SbVec2s((vpSize - borderBottomLeft - borderTopRight)[0], (vpSize - borderBottomLeft - borderTopRight)[1]);

		SbVec2s pos;
		pos[0] = mMouseDownPos[0] * (float) vpSize[0];
		pos[1] = mMouseDownPos[1] * (float) vpSize[1];

		mManipMode = NONE;

		if ((flags.getValue() & SCROLL_X) && (abs(pos[1] - mBorderScrollBar[1]) < 10))
		{
			int xPos = pos[0] - borderBottomLeft[0];

			int start = mScrollSize[0] * scrollPosX.getValue()[0];
			int end = mScrollSize[0] * (scrollPosX.getValue()[0] + scrollPosX.getValue()[1]);

			if ((xPos >= 0) && (xPos < mScrollSize[0]))
			{
				if (abs(xPos - start) < 10)
				{
					mManipMode = SCROLL_X_RESIZE_LEFT;
				}
				else if (abs(xPos - end) < 10)
				{
					mManipMode = SCROLL_X_RESIZE_RIGHT;
				}
				else if ((xPos > start) && (xPos < end))
				{
					mManipMode = SCROLL_X_MOVE;
					mScrollDiffToStart = xPos - start;
				}
			}
		}

		if ((flags.getValue() & SCROLL_Y) && (abs(pos[0] - mBorderScrollBar[0]) < 10))
		{
			int yPos = pos[1] - borderBottomLeft[1];

			int start = mScrollSize[1] * scrollPosY.getValue()[0];
			int end = mScrollSize[1] * (scrollPosY.getValue()[0] + scrollPosY.getValue()[1]);

			if ((yPos >= 0) && (yPos < mScrollSize[1]))
			{
				if (abs(yPos - start) < 10)
				{
					mManipMode = SCROLL_Y_RESIZE_BOTTOM;
				}
				else if (abs(yPos - end) < 10)
				{
					mManipMode = SCROLL_Y_RESIZE_TOP;
				}
				else if ((yPos > start) && (yPos < end))
				{
					mManipMode = SCROLL_Y_MOVE;
					mScrollDiffToStart = yPos - start;
				}
			}
		}
		
		if( !(flags.getValue() & NO_LEGEND) && mLegendBBox.intersect( SbVec3f(pos[0], pos[1], 0) ) )
		{
			mManipMode = LEGEND_MOVE;
		}

		if (SO_MOUSE_PRESS_EVENT(event, BUTTON1))
		{
			// mouse pressed:
			if (mManipMode != NONE)
			{
				action->setHandled();
				action->setGrabber(this);
			}
		}

		if (event->isOfType(SoLocation2Event::getClassTypeId()))
		{
			SbVec2f mousePos = event->getNormalizedPosition(mViewport);

			if ((mousePos[0] >= 0) && (mousePos[0] <= 1) && (mousePos[1] >= 0) && (mousePos[1] <= 1))
			{
				switch (mManipMode)
				{
				case SCROLL_X_RESIZE_LEFT:		
				case SCROLL_X_RESIZE_RIGHT:
					SoXipCursor::setCursor( "LEFTRIGHT" );
					break;

				case SCROLL_Y_RESIZE_BOTTOM:
				case SCROLL_Y_RESIZE_TOP:
					SoXipCursor::setCursor( "UPDOWN" );
					break;

				case SCROLL_X_MOVE:
				case SCROLL_Y_MOVE:
				case LEGEND_MOVE:
					SoXipCursor::setCursor( "MOVE" );
					break;				
				}
				
				if( mManipMode != NONE )
					action->setHandled();
			}
		}
	}
	else if( action->getGrabber() == this )
	{
		if (SO_MOUSE_RELEASE_EVENT(event, BUTTON1))
		{
			if( mManipMode == LEGEND_MOVE )
			{
				mManipMode = NONE;

				// Since the release event does not affect the state of this node,
				// manually notify changes to force the legend manip frame to be hidden
				startNotify();
			}

			// mouse released:
			action->releaseGrabber();
			action->setHandled();
		}
		else if (event->isOfType(SoLocation2Event::getClassTypeId()))
		{
			// mouse moved while pressed:
			SbVec2f mousePos = event->getNormalizedPosition(mViewport);
			SbVec2s vpSize = mViewport.getViewportSizePixels();

			SbVec2s pos;
			pos[0] = mousePos[0] * (float) vpSize[0];
			pos[1] = mousePos[1] * (float) vpSize[1];

			switch (mManipMode)
			{
			case SCROLL_X_RESIZE_LEFT:
				{
					float minWidth = 10.f / (float) mScrollSize[0];
					pos[0] -= mScrollBorder[0];
					SbVec2f xPos = scrollPosX.getValue();
					float oldPos = xPos[0];
					xPos[0] = (float) pos[0] / (float) mScrollSize[0];
					if (xPos[0] < 0) xPos[0] = 0;
					xPos[1] += oldPos - xPos[0];
					if (xPos[1] > minWidth)
						scrollPosX.setValue(xPos);
				} break;

			case SCROLL_X_RESIZE_RIGHT:
				{
					float minWidth = 10.f / (float) mScrollSize[0];
					pos[0] -= mScrollBorder[0];
					if (pos[0] > mScrollSize[0]) pos[0] = mScrollSize[0];
					SbVec2f xPos = scrollPosX.getValue();
					xPos[1] = (float) pos[0] / (float) mScrollSize[0] - xPos[0];
					if (xPos[1] > minWidth)
						scrollPosX.setValue(xPos);
				} break;

			case SCROLL_X_MOVE:
				{
					pos[0] -= mScrollBorder[0];
					SbVec2f xPos = scrollPosX.getValue();
					xPos[0] = (float) (pos[0] - mScrollDiffToStart) / (float) mScrollSize[0];
					if (xPos[0] < 0) xPos[0] = 0;
					if ((xPos[0] + xPos[1]) > 1) xPos[0] = 1 - xPos[1]; 
					scrollPosX.setValue(xPos);
				} break;

			case SCROLL_Y_RESIZE_BOTTOM:
				{
					float minWidth = 10.f / (float) mScrollSize[1];
					pos[1] -= mScrollBorder[1];
					SbVec2f yPos = scrollPosY.getValue();
					float oldPos = yPos[0];
					yPos[0] = (float) pos[1] / (float) mScrollSize[1];
					if (yPos[0] < 0) yPos[0] = 0;
					yPos[1] += oldPos - yPos[0];
					if (yPos[1] > minWidth)
						scrollPosY.setValue(yPos);
				} break;

			case SCROLL_Y_RESIZE_TOP:
				{
					float minWidth = 10.f / (float) mScrollSize[1];
					pos[1] -= mScrollBorder[1];
					if (pos[1] > mScrollSize[1]) pos[1] = mScrollSize[1];
					SbVec2f yPos = scrollPosY.getValue();
					yPos[1] = (float) pos[1] / (float) mScrollSize[1] - yPos[0];
					if (yPos[1] > minWidth)
						scrollPosY.setValue(yPos);
				} break;

			case SCROLL_Y_MOVE:
				{
					pos[1] -= mScrollBorder[1];
					SbVec2f yPos = scrollPosY.getValue();
					yPos[0] = (float) (pos[1] - mScrollDiffToStart) / (float) mScrollSize[1];
					if (yPos[0] < 0) yPos[0] = 0;
					if ((yPos[0] + yPos[1]) > 1) yPos[0] = 1 - yPos[1]; 
					scrollPosY.setValue(yPos);
				} break;

			case LEGEND_MOVE:
				{
					const SbVec2s& vpSize = mViewport.getViewportSizePixels();
					
					SbVec3f legendSize;
					mLegendBBox.getSize( legendSize[0], legendSize[1], legendSize[2] );

					SbVec2s vpChildrenSize = mChildrenViewport.getViewportSizePixels();
					vpChildrenSize[0] -= legendSize[0];
					vpChildrenSize[1] -= legendSize[1];

					SbVec2f diff;
					if( vpChildrenSize[0] )
					{
					diff[0] = (mousePos[0] - mMouseDownPos[0]) * ((float) vpSize[0] / (float) vpChildrenSize[0]);
					}

					if( vpChildrenSize[1] )
					{
					diff[1] = (mousePos[1] - mMouseDownPos[1]) * ((float) vpSize[1] / (float) vpChildrenSize[1]);
					}

					SbVec2f newPos( legendPos.getValue() + diff );
					CLAMP( newPos[0], 0, 1 );
					CLAMP( newPos[1], 0, 1 );

					if( legendPos.getValue() != newPos )
						legendPos.setValue( newPos );

					mMouseDownPos = mousePos;

				} break;
			}

			action->setHandled();
		}
	}

	SbViewportRegion viewportRegion = SoViewportRegionElement::get( action->getState() );

	// Set plot area viewport before propagating the action to the children
	action->setViewportRegion( mChildrenViewport );

	action->getState()->push();
	{		
		SoViewportRegionElement::set( action->getState(), mChildrenViewport );

		// adjust camera position and height
		float bbSize[3];
		mPlotBBox.getSize(bbSize[0], bbSize[1], bbSize[2]);
		mCamera->height.setValue(bbSize[1]);
		mCamera->aspectRatio.setValue(bbSize[0] / bbSize[1]);
		mCamera->position.setValue(mPlotBBox.getCenter());

		// If the graphics need to be flipped, rotate the camera
		if( flags.getValue() & FLIP_Y )
		{
			SbRotation flipRot( SbVec3f(1, 0, 0), M_PI );
			mCamera->orientation.setValue( flipRot );
		}

		action->traverse( mCamera );

		SoGroup::handleEvent( action );
	}
	action->getState()->pop();

	// Restore the viewport
	action->setViewportRegion( viewportRegion );
}



