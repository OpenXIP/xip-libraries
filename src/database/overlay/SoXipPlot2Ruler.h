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
*	@file	SoXipPlot2Ruler.h
*	@brief	Declaration of the SoXipPlot2Ruler class
*	@author	Julien Gein
**/

#ifndef SOXIPPLOT2RULER_H
#define SOXIPPLOT2RULER_H

#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/projectors/SbPlaneProjector.h>

class SoXipPlot2Ruler : public SoNode
{
	SO_NODE_HEADER( SoXipPlot2Ruler );

public:
	enum RulerType
	{
		HORIZONTAL,
		VERTICAL
	};

	SoXipPlot2Ruler();

	SoSFEnum		type;
	SoMFFloat		value;

	static void initClass();

protected:
	virtual ~SoXipPlot2Ruler();

	virtual void GLRender( SoGLRenderAction* action );
	virtual void handleEvent( SoHandleEventAction* action );
	virtual void saveViewInformation( SoHandleEventAction* action );
	virtual SbVec3f projectScreenOffsetToWorld( const SbVec2s& pixelOffset );

	SbViewportRegion		mViewportRegion;
	SbViewVolume			mViewVolume;
	SbPlaneProjector		mPlaneProj;
	SbBox3f					mBBox;

	class SoCoordinate3*	mCoord;
	class SoLineSet*		mLineSet;

	int						mSelectedValue;

};

#endif // SOXIPPLOT2RULER_H
