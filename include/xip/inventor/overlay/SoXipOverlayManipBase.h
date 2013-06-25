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
*	@file    SoXipOverlayManipBase.h
*	@brief   Declaration of the SoXipOverlayManipBase class
*	@author  Julien Gein
**/

#ifndef SOXIPOVERLAYMANIPBASE_H
#define SOXIPOVERLAYMANIPBASE_H

#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoSubNode.h>
#include <xip/inventor/overlay/SoXipOverlayElement.h>
#include  <xip/inventor/overlay/SoXipManipulableShape.h>
#include  <xip/inventor/overlay/xipivoverlay.h>
/**
*	@class SoXipOverlayManipBase
*
* Base class for all overlay manipulators
*
**/
class XIPIVOVERLAY_API  SoXipOverlayManipBase : public SoNode
{
	SO_NODE_ABSTRACT_HEADER( SoXipOverlayManipBase );

public:
	/// Constructor
	SoXipOverlayManipBase();

	/// turn on/off the manipulator
	SoSFBool				on;
	/// Number of nodes upward where overlay manipulators can start
	/// searching for overlays.
	SoSFInt32				numNodesUpToContainer;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipOverlayManipBase();

	virtual SbBool getPoint( SoHandleEventAction* action, SbVec3f& point );
	virtual void handleEvent( SoHandleEventAction* action );
	virtual SoXipManipulableShape* isShapePicked( SoHandleEventAction* action );

	SoXipManipulableShape*	mPickedShape;
	SoNode*					mActionNode;

	virtual void saveViewInformation( SoAction* action );
	virtual SbVec3f projectScreenOffsetToWorld( const SbVec2s& pixelOffset ) const;

	class SbPlaneProjector*	mPlaneProj;
	SbViewVolume			mViewVolume;
	SbViewportRegion		mViewport;

	SbXipOverlaySettings	mOverlaySettings;

	virtual void transform( SoNode* root );
	virtual void applyTransform( SoNode* root );

	SbVec3f					mTransformationOrigin;
	SbMatrix				mTransformationMatrix;

};

#endif // SOXIPOVERLAYMANIPBASE_H
