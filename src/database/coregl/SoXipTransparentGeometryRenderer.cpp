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

#include <xip/system/standard.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>
#include <xip/inventor/coregl/SoXipFboElement.h>

#include "SoXipTransparentGeometryRenderer.h"
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h> 
#include <xip/inventor/core/SoXipTransparentGeometryGroupElement.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>
#include <Inventor/misc/SoChildList.h>

SO_NODE_SOURCE(SoXipTransparentGeometryRenderer);


/** \fn SoXipTransparentGeometryRenderer::SoXipTransparentGeometryRenderer()
* All input and output fields are added and initialized here. 
* \return none
*/
SoXipTransparentGeometryRenderer::SoXipTransparentGeometryRenderer(void)
{
	SO_NODE_CONSTRUCTOR(SoXipTransparentGeometryRenderer);
	SO_NODE_ADD_FIELD(maxNumLayers, (1));
	SO_NODE_ADD_FIELD(firstLayer, (1));
	SO_NODE_ADD_FIELD(sourceFBO, (0));
	SO_NODE_ADD_FIELD(textureUnit, (0));
	SO_NODE_ADD_FIELD(textureName, (""));

	SO_NODE_ADD_FIELD(mRenderMode, (PING_PONG));

	SO_NODE_DEFINE_ENUM_VALUE(RenderMode, PING_PONG);
	SO_NODE_DEFINE_ENUM_VALUE(RenderMode, TEXTURE_3D);
	SO_NODE_SET_SF_ENUM_TYPE(mRenderMode, RenderMode);
	
	// Output fields
	SO_NODE_ADD_FIELD(outputColorBufferHandle, (0));
	SO_NODE_ADD_FIELD(outputDepthBufferHandle, (0));

	mDepthBGLayerTex = 0;
	mLayerTexture3D = 0;
	mLayerColorTexture3D = 0;
}



/*! \fn SoXipTransparentGeometryRenderer::~SoXipTransparentGeometryRenderer()
 * \brief Destructor, cleans up internal data
 * \return None
 */
SoXipTransparentGeometryRenderer::~SoXipTransparentGeometryRenderer()
{
}


/*! \fn SoXipTransparentGeometryRenderer::initClass()
 * Initializes this class. Called on dll initialization.
 * \return void
 */
void SoXipTransparentGeometryRenderer::initClass(void)
{
	SO_NODE_INIT_CLASS(SoXipTransparentGeometryRenderer, SoShape, "Shape");

	SO_ENABLE(SoGLRenderAction, SoXipTransparentGeometryGroupElement);
	SO_ENABLE(SoPickAction,     SoXipTransparentGeometryGroupElement);
	SO_ENABLE(SoCallbackAction, SoXipTransparentGeometryGroupElement);
	SO_ENABLE(SoGetBoundingBoxAction, SoXipTransparentGeometryGroupElement);
}


/*! \fn SoXipTransparentGeometryRenderer::doAction(SoAction * action)
 *  Adds a node to the SoXipTransparentGeometryRendererElement in the current state
 *  \param action - the current state action, no action taken if input action is NULL
 *  \return void
 */
void SoXipTransparentGeometryRenderer::doAction(SoAction * action)
{
	// don't do anything if turned off
	// if (!on.isIgnored() && !on.getValue()) return;

	action->getState()->push();

	SoXipTransparentGeometryGroupElement * elem =
		SoXipTransparentGeometryGroupElement::getInstance(action->getState());

	if (!elem) return;

	int numGroups = elem->getNum();

	for (int i = 0; i < numGroups; i++)
	{
		//SoGroup * node = dynamic_cast<SoGroup *>(elem->getNode(i));
		SoGroup * node = (SoGroup *) (elem->getNode(i));

		if (node)
		{
			SoChildList *children = node->getChildren();

			if (children) children->traverse(action);
		}
	}

	action->getState()->pop();
}

/*! \fn SoXipTransparentGeometryRenderer::GLRender(SoGLRenderAction * action) 
*  Derived inventor GLRender method, overrides to doAction
*  \param action - the current state action
*  \return void
*/
void SoXipTransparentGeometryRenderer::GLRender(SoGLRenderAction * action)
{
	if(mRenderMode.getValue() == SoXipTransparentGeometryRenderer::PING_PONG)
	{
		//SoDebugError::post("SoXipTransparentGeometryRenderer::GLRender","render mode: PING_PONG");
		GLRenderPingPong(action);
	}
	else if(mRenderMode.getValue() == SoXipTransparentGeometryRenderer::TEXTURE_3D)
	{
		//SoDebugError::post("SoXipTransparentGeometryRenderer::GLRender","render mode: TEXTURE_3D");
		GLRenderTexture3D(action);
	}
	else
	{
		SoDebugError::post("SoXipTransparentGeometryRenderer::GLRender","render mode: UNKNOWN");
	}
}

/**
* GLRenderPingPong
*/
void SoXipTransparentGeometryRenderer::GLRenderPingPong(SoGLRenderAction * action)
{
	SoGLRenderAction::TransparencyType transparencyType = action->getTransparencyType();

	const GLubyte *version = glGetString(GL_VERSION);
	//const char *extensions = (const char*)glGetString(GL_EXTENSIONS);

	int width, height;

	// Where The Viewport Values Will Be Stored
	GLint viewport[4];

	// Retrieves The Viewport Values (X, Y, Width, Height)
	glGetIntegerv(GL_VIEWPORT, viewport);

	width = viewport[2];
	height = viewport[3];
	
	GLuint depthUnit;

	if (mDepthBGLayerTex == 0 )
	{
	    // allocate a texture name
		glGenTextures( 1, &mDepthBGLayerTex );
	}

	// create texture internally
	textureUnit.setValue(SoXipMultiTextureElement::getFreeUnit(action->getState()));

	SoXipMultiTextureElement::setUnit(action->getState(), textureUnit.getValue());

    depthUnit = textureUnit.getValue();

	glActiveTexture(GL_TEXTURE0 + depthUnit);

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, mDepthBGLayerTex );
    
    // when texture area is small
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    // when texture area is large
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

    // the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
#if 1
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_GREATER );
#else
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_NONE);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_GREATER ); 
    glTexParameterf( GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE ); 
#endif

#if 1 /* initialize the depth buffer with 0.0, transparent objects are removed */
	glClearDepth(0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 0, 0, width, height, 0);
#else /* initialize the depth buffer with objects already in the depth buffer */
	 glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, sourceFBO.getValue());

	  // bind the active depth texture in FBO
	  glActiveTexture(GL_TEXTURE0 + depthUnit);
		  
	  FboSetup * activeFBO = SoXipFboElement::getActive(action->getState(), this);

	  // select our current texture
	  glBindTexture( GL_TEXTURE_2D, activeFBO->depthHandle );

	  // Copy depth component from framebuffer to depth texture
      glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 0, 0, width, height, 0);
		
	  // Rebind the active Fbo
	  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, activeFBO->fboHandle);
#endif
	SoXipFboElement::flip(action->getState(), this);

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	int my_program = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &my_program);

	GLint layer_location = glGetUniformLocation(my_program,"layer");
	GLint depth_location = glGetUniformLocation(my_program,"depthtex");
	GLint color_location = glGetUniformLocation(my_program,"colortex");
	GLint viewsize_location = glGetUniformLocation(my_program,"viewsize");

	float viewsize[4] = {
		viewport[2], viewport[3], 1.0, 1.0
	};

	glUniform1i(depth_location, depthUnit);
	glUniform4fv(viewsize_location, 1, viewsize);

	int numLayers = maxNumLayers.getValue();

	SoXipTransparentGeometryGroupElement * elem =
		SoXipTransparentGeometryGroupElement::getInstance(action->getState());

	if (!elem) return;

	int numGroups = elem->getNum();

	unsigned int * colorUnits = SoXipFboElement::getUnits(action->getState(), this);

	if (!colorUnits) return;

	glUniform1i(color_location, colorUnits[0]);

#if 0 // debugging textures
	FboSetup * c1 = SoXipFboElement::getActive(action->getState(), this);
	FboSetup * c2 = SoXipFboElement::getPassive(action->getState(), this);
	if (c1->colorHandles)
		SoDebugError::post("before main layers loop", "c1 FBO %d COLOR %d", c1->fboHandle, c1->colorHandles[0]);
	if (c2->colorHandles)
		SoDebugError::post("before main layers loop", "c2 FBO %d COLOR %d", c2->fboHandle, c2->colorHandles[0]);
#endif

	for( int layer = 0; layer < numLayers; layer++ )
	  {
#if 0
	  glClear(GL_DEPTH_BUFFER_BIT);
#else
	  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, sourceFBO.getValue());

	  // BIND The active Depth texture in FBO
	  glActiveTexture(GL_TEXTURE0 + depthUnit);
		  
	  FboSetup * activeFBO = SoXipFboElement::getActive(action->getState(), this);

	  // select our current texture
	  glBindTexture( GL_TEXTURE_2D, activeFBO->depthHandle );

	  // Copy depth component from framebuffer to depth texture
      glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 0, 0, width, height, 0);
		
	  // Rebind the active Fbo
	  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, activeFBO->fboHandle);
#endif
	  glUniform1i(layer_location, layer);

	  //glEnable(GL_DEPTH_TEST);
      //glDepthFunc(GL_LESS);
	  glBlendFunc(GL_ONE, GL_ZERO);
	  //glDepthMask(GL_TRUE);

		/* BIND AND SETUP DEPTH BUFFER */
		int depthHandle = SoXipFboElement::getPassive(action->getState(), this)->depthHandle;

		glActiveTexture(GL_TEXTURE0 + depthUnit);

		// select our current texture
		glBindTexture( GL_TEXTURE_2D, depthHandle );
    
	    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		// the texture ends at the edges (clamp)
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
#if 1
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
	    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_GREATER );
#else
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_NONE);
	    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_GREATER ); 
		glTexParameterf( GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE ); 
#endif
		// SETUP PASSIVE DEPTH BUFFER TEXTURE
		//glActiveTexture(GL_TEXTURE0 + depthUnit);
		//glBindTexture( GL_TEXTURE_2D, fboSetup->depthHandle );
#if 0   // Already bound by the flip...
	    // SETUP PASSIVE COLOR BUFFER TEXTURE
		glActiveTexture(GL_TEXTURE0 + colortex);
		glBindTexture( GL_TEXTURE_2D, fboSetup->colorHandles[0] );
#endif
		action->getState()->push();

		for (int i = 0; i < numGroups; i++)
		  {
			//SoGroup * node = dynamic_cast<SoGroup *>(elem->getNode(i));
			SoGroup * node = (SoGroup *) (elem->getNode(i));

			if (node)
			{
				SoChildList *children = node->getChildren();

				if (children) children->traverse(action);
			}
		  }

		action->getState()->pop();

		if (layer == firstLayer.getValue())
		{
			glActiveTexture(GL_TEXTURE0 + depthUnit);
			glBindTexture(GL_TEXTURE_2D, mDepthBGLayerTex);

		    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_NONE);
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_GREATER ); 
			glTexParameterf( GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE ); 

			glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 0, 0, width, height, 0);
		}

		glActiveTexture(GL_TEXTURE0 + colorUnits[0]);
	    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, width, height, 0);

		SoXipFboElement::flip(action->getState(), this);
#if 0
		unsigned int colorTex = SoXipFboElement::getPassive(action->getState(), this)->colorHandles[0];

		outputColorBufferHandle.setValue(colorTex);
#endif
#if 0
		FboSetup * c = SoXipFboElement::getPassive(action->getState(), this);
		SoDebugError::post("loop flip", "Passive Layer %d, FBO %d COLOR %d", layer, c->fboHandle, c->colorHandles[0]);
#endif
	}

	// COMPOSITE INTO DEFAULT FB (i.e. 0)
	// glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	// Draw a quad with the final color and depth result (current passive color, and first depth buffer drawn)
	// But what's the texture unit for the color buffer??? How do we find that? ask stefan
	// We will reuse the texture for the depth for the saved first layer depth buffer.
	action->setTransparencyType(transparencyType);

	unsigned int colorTex = SoXipFboElement::getPassive(action->getState(), this)->colorHandles[0];

	outputColorBufferHandle.setValue(colorTex);
	outputDepthBufferHandle.setValue(mDepthBGLayerTex);
}

/**
* Render every layer to a different slice of a texture 3D
**/
void SoXipTransparentGeometryRenderer::GLRenderTexture3D(SoGLRenderAction * action)
{
	//const GLubyte *version = glGetString(GL_VERSION);
	//const char *extensions = (const char*)glGetString(GL_EXTENSIONS);
	//SoDebugError::post("SoXipTransparentGeometryRenderer version", (const char*)version);

	int width, height;

	// Where The Viewport Values Will Be Stored
	GLint viewport[4];

	// Retrieves The Viewport Values (X, Y, Width, Height)
	glGetIntegerv(GL_VIEWPORT, viewport);

	width = viewport[2];
	height = viewport[3];
	
	GLuint depthUnit;
#if 0
	if (mLayerTexture3D == 0)
	{
	    // allocate a texture name
		glGenTextures( 1, &mLayerTexture3D );
	}
#endif
	// create texture internally
	textureUnit.setValue(SoXipMultiTextureElement::getFreeUnit(action->getState()));

	SoXipMultiTextureElement::setUnit(action->getState(), textureUnit.getValue());

    depthUnit = textureUnit.getValue();

	glActiveTexture(GL_TEXTURE0 + depthUnit);

	//checkFramebufferStatus("status0");

#if 0 /* done in SoXipAttachDepth */
    // select our current texture
    //glBindTexture( GL_TEXTURE_3D, mLayerTexture3D );
    
    // when texture area is small
    glTexParameterf( GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    // when texture area is large
    glTexParameterf( GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

    // the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
//#if 0
	glTexParameterf( GL_TEXTURE_3D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
    glTexParameterf( GL_TEXTURE_3D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_GREATER );
//#else
	glTexParameterf( GL_TEXTURE_3D, GL_TEXTURE_COMPARE_MODE_ARB, GL_NONE);
	glTexParameterf( GL_TEXTURE_3D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_GREATER ); 
	glTexParameterf( GL_TEXTURE_3D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE ); 
#endif
    // Color texture
	// create texture internally
	unsigned int * colorUnits = SoXipFboElement::getUnits(action->getState(), this);

	if (!colorUnits) return;

	glActiveTexture(GL_TEXTURE0 + colorUnits[0]);

	FboSetup * activeFBO = SoXipFboElement::getActive(action->getState(), this);

	checkFramebufferStatus("status1");

	/* done in SoXipAttachColor */
    // select our current texture
	//glBindTexture( GL_TEXTURE_3D, activeFBO->colorHandles[0] );

    // when texture area is small
    //glTexParameterf( GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    // when texture area is large
    //glTexParameterf( GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

    // the texture ends at the edges (clamp)
    //glTexParameterf( GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    //glTexParameterf( GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	// Clear

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int my_program = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &my_program);

	GLint layer_location = glGetUniformLocation(my_program,"layer");
	GLint numLayers_location = glGetUniformLocation(my_program,"numLayers");
	GLint depth_location = glGetUniformLocation(my_program,"depthtex");
	GLint color_location = glGetUniformLocation(my_program,"colortex");
	GLint viewsize_location = glGetUniformLocation(my_program,"viewsize");

	float viewsize[4] = {
		viewport[2], viewport[3], 1.0, 1.0
	};

	glUniform1i(depth_location, depthUnit);
	glUniform4fv(viewsize_location, 1, viewsize);

	int numLayers = maxNumLayers.getValue();

	SoXipTransparentGeometryGroupElement * elem =
		SoXipTransparentGeometryGroupElement::getInstance(action->getState());

	if (!elem) return;

	int numGroups = elem->getNum();

	glUniform1i(color_location, colorUnits[0]);

	glUniform1i(numLayers_location, numLayers);

	for( int layer = 0; layer < numLayers; layer++ )
	  {
#if 0
	    glClear(GL_DEPTH_BUFFER_BIT);
#endif
		// Bind the source FBO
	    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, sourceFBO.getValue());

		checkFramebufferStatus("status2");

	  // Bind the active depth texture in FBO
	  glActiveTexture(GL_TEXTURE0 + depthUnit);

	  checkFramebufferStatus("status3");

	  // select our current texture
	  glBindTexture( GL_TEXTURE_3D, activeFBO->depthHandle );

	  checkFramebufferStatus("status4");

	  // Copy depth component from framebuffer to depth texture
      glCopyTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, layer, 0, 0, width, height);

	  checkFramebufferStatus("status5");

	  // Rebind the active Fbo
	  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, activeFBO->fboHandle);

	  checkFramebufferStatus("status6");

	  GLenum status2 = (GLenum)glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
      if(status2 != GL_FRAMEBUFFER_COMPLETE_EXT)
		{
		SoDebugError::post("SoXipTransparentGeometryRenderer status2", "GL FRAMEBUFFER INCOMPLETE");
		return;
		}

	  glFramebufferTexture3DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,
		GL_TEXTURE_3D, activeFBO->depthHandle, 0, layer);

	  checkFramebufferStatus("mystatus3");

	  GLenum status3 = (GLenum)glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		if(status3 != GL_FRAMEBUFFER_COMPLETE_EXT)
		{
		SoDebugError::post("SoXipTransparentGeometryRenderer status3", "GL FRAMEBUFFER INCOMPLETE");
		return;
		}

	  //SoXipFboElement::renderToSlice(action->getState(), this, layer);
	  glFramebufferTexture3DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
		GL_TEXTURE_3D, activeFBO->colorHandles[0], 0, layer);

		GLenum status4 = (GLenum)glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		if(status4 != GL_FRAMEBUFFER_COMPLETE_EXT)
		{
		SoDebugError::post("SoXipTransparentGeometryRenderer status4", "GL FRAMEBUFFER INCOMPLETE");
		return;
		}

	  //SoXipFboElement::renderToSlice(action->getState(), this, layer);

	  glUniform1f(layer_location, float(layer-0.5)/float(numLayers));

	  action->getState()->push();

	  for (int i = 0; i < numGroups; i++)
		{
			//SoGroup * node = dynamic_cast<SoGroup *>(elem->getNode(i));
			SoGroup * node = (SoGroup *) (elem->getNode(i));

			if (node)
			{
				SoChildList *children = node->getChildren();

				if (children) children->traverse(action);
			}
		}

		action->getState()->pop();
	}

	//unsigned int colorTex = SoXipFboElement::getActive(action->getState(), this)->colorHandles[0];

	outputColorBufferHandle.setValue(activeFBO->colorHandles[0]);
	outputDepthBufferHandle.setValue(activeFBO->depthHandle);
}

/*! \fn SoXipTransparentGeometryRenderer::callback(SoCallbackAction * action) 
*  Derived inventor callback method, overrides to doAction
*  \param action - the current state action
*  \return void
*/
void SoXipTransparentGeometryRenderer::callback(SoCallbackAction * action)
{
	doAction(action);
}


/*! \fn SoXipTransparentGeometryRenderer::pick(SoPickAction * action) 
*  Derived inventor pick method, overrides to doAction
*  \param action - the current state action
*  \return void
*/
void SoXipTransparentGeometryRenderer::pick(SoPickAction * action)
{
	doAction(action);
}

/*! \fn SoXipTransparentGeometryRenderer::getBoundingBox(SoGetBoundingBoxAction * action) 
*  Derived inventor getBoundingBox method, overrides to doAction
*  \param action - the current state action
*  \return void
*/
void SoXipTransparentGeometryRenderer::getBoundingBox(SoGetBoundingBoxAction *action)
{
	doAction(action);
}


/*! \fn SoXipTransparentGeometryRenderer::computeBBox(SoAction *action, SbBox3f &box,
				    SbVec3f &center)
* Computes bounding box for subclass using information in the
* given action (which may not necessarily be an
* SoGetBoundingBoxAction). This is used by getBoundingBox() and
* when rendering or picking a shape with bounding-box complexity.
* Subclasses must define this method.
* \param action - the current state action
* \return void
*/
void SoXipTransparentGeometryRenderer::computeBBox(SoAction *action, SbBox3f &box,
				    SbVec3f &center)
{
}

/*! \fn This method MUST be defined by each subclass to generate
* primitives (triangles, line segments, points) that represent
* the shape.
* \param action - the current state action
* \return void
*/
void SoXipTransparentGeometryRenderer::generatePrimitives(SoAction *action)
{
}

/**
 *  Run a check and output any errors.
 */
bool SoXipTransparentGeometryRenderer::checkFramebufferStatus(const char *msg) {
    bool isOk = false;
    GLenum status = (GLenum)glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    switch(status) {
        case GL_FRAMEBUFFER_COMPLETE_EXT:
            isOk = true;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
            SoDebugError::post("SoXipFbo", "%s GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT",msg);
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
            SoDebugError::post("SoXipFbo", "%s GL_FRAMEBUFFER_UNSUPPORTED_EXT",msg);
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
            //SoDebugError::post("SoXipFbo", "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT");
            SoDebugError::post("SoXipFbo", "%s The fbo will be incomplete without color attachments",msg);
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
            SoDebugError::post("SoXipFbo", "%s GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT",msg);
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
            SoDebugError::post("SoXipFbo", "%s GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT",msg);
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
            SoDebugError::post("SoXipFbo", "%s GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT",msg);
            SoDebugError::post("SoXipFbo", "%s One or more render targets have no attached buffer(s)",msg);
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
            SoDebugError::post("SoXipFbo", "%s GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT",msg);
            break;
        default:
            SoDebugError::post("SoXipFbo", "%s UNKNWON frambuffer fault",msg);
    }

    return isOk;
} 
#if 0
void SoXipTransparentGeometryRenderer::GLRenderTexture2D(SoGLRenderAction * action)
{
	int width, height;

	// Where The Viewport Values Will Be Stored
	GLint viewport[4];

	// Retrieves The Viewport Values (X, Y, Width, Height)
	glGetIntegerv(GL_VIEWPORT, viewport);

	width = viewport[2];
	height = viewport[3];

	GLuint fbo;
	glGenFramebuffersEXT(1, &fbo);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);

	GLuint depthbuffer;
	glGenRenderbuffersEXT(1, &depthbuffer);

	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthbuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height);

	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthbuffer);

	GLuint img;
	glGenTextures(1, &img);
	glBindTexture(GL_TEXTURE_2D, img);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, img, 0);
	GLenum status = (GLenum)glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	
	if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
	{
		SoDebugError::post("SoXipTransparentGeometryRenderer", "GL FRAMEBUFFER INCOMPLETE");
		return;
	}

	SoXipTransparentGeometryGroupElement * elem =
		SoXipTransparentGeometryGroupElement::getInstance(action->getState());

	if (!elem) return;

	int numGroups = elem->getNum();

	action->getState()->push();

	for (int i = 0; i < numGroups; i++)
		{
		//SoGroup * node = dynamic_cast<SoGroup *>(elem->getNode(i));
		SoGroup * node = (SoGroup *) (elem->getNode(i));

		if (node)
			{
			SoChildList *children = node->getChildren();

			if (children) children->traverse(action);
			}
		}

	action->getState()->pop();

	// Unbind the frame buffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	GLuint img2;
	glGenTextures(1, &img2);
	glBindTexture(GL_TEXTURE_2D, img2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmapEXT(GL_TEXTURE_2D);

	glDeleteFramebuffersEXT(1, &fbo);
	glDeleteRenderbuffersEXT(1, &depthbuffer);
}

#endif


