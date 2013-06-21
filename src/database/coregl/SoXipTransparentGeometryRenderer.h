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

#ifndef SOXIPTRANSPARENTGEOMETRYRENDERER_H
#define SOXIPTRANSPARENTGEOMETRYRENDERER_H

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFUInt32.h>
#include <Inventor/fields/SoSFString.h>
#include <xip/inventor/coregl/xipivcoregl.h>


/*! \class SoXipTransparentGeometryRenderer
*  \brief A volume group for collecting nodes relevant to a volume
*
* This node is typically used to group all nodes and property relevant 
* to a particular volume under one group such that a processing node 
* can apply the corresponding properties to the corresponding volume, 
* e.g. in a fusion scenario
*/
class XIPIVCOREGL_API SoXipTransparentGeometryRenderer : public SoShape
{
	SO_NODE_HEADER(SoXipTransparentGeometryRenderer);

	SoSFEnum    mRenderMode;

	// outputs
	SoSFUInt32	 outputColorBufferHandle;
	SoSFUInt32	 outputDepthBufferHandle;

public:
	enum RenderMode {
		PING_PONG = 0,
		TEXTURE_3D = 1
	};

    /// Constructor, initialize fields and defaults
    SoXipTransparentGeometryRenderer();

    /// Initializes the SoXipTransparentGeometryDataElement class
	static void initClass();

    /// returns a child node within this group, if any
    //virtual SoNode *getChildByType(const SoType &type) const;

	// Computes bounding box for subclass using information in the
    // given action (which may not necessarily be an
    // SoGetBoundingBoxAction). This is used by getBoundingBox() and
    // when rendering or picking a shape with bounding-box complexity.
    // Subclasses must define this method.
    virtual void	computeBBox(SoAction *action, SbBox3f &box,
				    SbVec3f &center);

	// This method MUST be defined by each subclass to generate
    // primitives (triangles, line segments, points) that represent
    // the shape.
    virtual void	generatePrimitives(SoAction *action);

protected:
    /// Destructor, dereference data
	virtual ~SoXipTransparentGeometryRenderer();

    /// Performs the action, sets the crop box data
	virtual void doAction(SoAction * action);

    /// Performs GL render action
	virtual void GLRender(SoGLRenderAction * action);

    /// Performs the callback
	virtual void callback(SoCallbackAction * action);

    /// Performs the pick action
	virtual void pick(SoPickAction * action);

    /// Performs the bounding box computation action
	virtual void getBoundingBox (SoGetBoundingBoxAction *action);

	/// render using the ping pong render mode
	virtual void GLRenderPingPong(SoGLRenderAction * action);

	/// render using the texture 3D render mode
	virtual void GLRenderTexture3D(SoGLRenderAction * action);

	/// render using the texture 2D render mode
	//virtual void GLRenderTexture2D(SoGLRenderAction * action);

	bool checkFramebufferStatus(const char *msg);

	/// Desired number of layers for depth peeling
	SoSFInt32 maxNumLayers;

    /// First layer to render
	SoSFInt32 firstLayer;

	/// Source FBO
	SoSFInt32	sourceFBO;

	/// Texture unit
	SoSFInt32	textureUnit;

	/// Texture name
	SoSFString	textureName;

	/// Depth Background layer texture
	unsigned int mDepthBGLayerTex;

	/// 3D texture for all layers
	unsigned int mLayerTexture3D;

	/// 3D color texture for all layers
	unsigned int mLayerColorTexture3D;
};

#endif // SOXIPTRANSPARENTGEOMETRYRENDERER_H
