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
 *	Node class for texture-based volume rendering
 */

#ifndef _SO_XIP_PLUGIN_SLICER_H
#define _SO_XIP_PLUGIN_SLICER_H

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>
#include <xip/inventor/core/SoXipRenderModeElement.h>
#include <vector>


#define MAX_VR_CLIP_PLANES	12

class SoHandleEventAction;

/**
 *	SoXipPluginSlicer. An Open Inventor node to create the geometry
 *	for texture-based volume rendering
 */
class SoXipPluginSlicer : public SoShape
{
	SO_NODE_HEADER( SoXipPluginSlicer );

public:
	/**
	 *	Constructor
	 */
	SoXipPluginSlicer();

	/**	
	 *	Initializes the class
	 */
	static void initClass();

	/**	
	 *	Fields for the number of slices in X, Y and Z directions
	 *	(Object-aligned)
	 */
	SoSFInt32 numSlicesX;
	SoSFInt32 numSlicesY;
	SoSFInt32 numSlicesZ;

	/**	
	 *	Fields for the number of slices in X, Y and Z directions
	 *	(Object-aligned)
	 */
	SoSFInt32 numSlices;
	SoSFBool  useComplexity;

	

	/**	
	 *	An enumeration of different slicing directions
	 */
	enum SliceDir {
		  SD_X_FRONT_TO_BACK, //!< in direction of the negative x-axis 
			SD_X_BACK_TO_FRONT, //!< in direction of the positive x-axis 
			SD_Y_FRONT_TO_BACK, //!< in direction of the negative y-axis 
			SD_Y_BACK_TO_FRONT, //!< in direction of the positive y-axis 
			SD_Z_FRONT_TO_BACK, //!< in direction of the negative z-axis 
			SD_Z_BACK_TO_FRONT  //!< in direction of the positive z-axis 
	};

	/**	
	 *	An enumeration of different types of slicing (2D vs. 3D)
	 */
    enum Slicing {
		VIEW_ALIGNED,
		OBJECT_ALIGNED
    };

	/**	
	 *	An enumeration of different compositing directions
	 */
    enum Compositing {
		BACK_TO_FRONT,
		FRONT_TO_BACK
    };

	/**	
	 *	An enumeration of different rendering modes
	 */
	enum Mode {
    MPR     = SoXipRenderModeElement::MPR,
		MAXIP   = SoXipRenderModeElement::MAXIP,
		MINIP   = SoXipRenderModeElement::MINIP,
    VRT     = SoXipRenderModeElement::VRT_COLOR
	};

	/**	
	 *	Fields for rendering mode, slicing type and compositing direction
	 */
	SoSFEnum		mode;
  SoSFEnum		slicing;
  SoSFEnum		compositing;

protected:
	/**	
	 *	Destructor
	 */
	~SoXipPluginSlicer();

	/**	
	 *	GLRender
	 */
	virtual void GLRender( SoGLRenderAction* action );

	virtual void	computeBBox(SoAction *action, SbBox3f &box,
				    SbVec3f &center);
	virtual void	generatePrimitives(SoAction *action);

	/**	
	 *	Create geometry for view-aligned slicing (ie. 3D texture-based)
	 */
	void sliceViewAligned(SoState  *state);

	/**	
	 *	Create geometry for object-aligned slicing (ie. 2D texture-based)
	 */
	void sliceObjectAligned(SoState  *state);

	/**	
	 *	Gets the slicing direction, regarding the camera position &
	 *	orientation
	 */
	int getSlicingDirection(SoState *pState, SbVec3f *pViewDir = NULL);

	/**	
	 *	Clips the passed polygon with SoXipVRClipPlaneElements present in
	 *	state
	 */
	int clipPolygon(SbVec3f *poly, int numPoints);

  void volumeRendering(SoState *state);

  void mprRendering(SoState *state);

	/// Clip planes
	SbPlane		mClipPlanes[MAX_VR_CLIP_PLANES];
	int			  mNumClipPlanes;
	SbVec3f		mTmpPoly1[12 + MAX_VR_CLIP_PLANES];
	SbVec3f		mTmpPoly2[12 + MAX_VR_CLIP_PLANES];
};

#endif // _SO_XIP_PLUGIN_SLICER_H

