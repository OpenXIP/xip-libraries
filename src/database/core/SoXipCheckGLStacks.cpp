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

#include <xip/system/GL/gl.h>
#include <xip/system/GL/glu.h>

#include "SoXipCheckGLStacks.h"
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/errors/SoDebugError.h>

SO_NODE_SOURCE(SoXipCheckGLStacks);


SoXipCheckGLStacks::SoXipCheckGLStacks(void)
{
    SO_NODE_CONSTRUCTOR(SoXipCheckGLStacks);

    SO_NODE_ADD_FIELD(checkState, (TRUE));
    SO_NODE_ADD_FIELD(label, (SbString("")));

    mProjectionStackDepth = 1;
    mModelviewStackDepth = 1;
    mColorStackDepth = 1;
    mTextureStackDepth = 1;
    mAttribStackDepth = 1;

    mMaxProjectionStackDepth = -1;
    mMaxModelviewStackDepth = -1;
    mMaxColorStackDepth = -1;
    mMaxTextureStackDepth = -1;
    mMaxAttribStackDepth = -1;
}


SoXipCheckGLStacks::~SoXipCheckGLStacks()
{
}

void 
SoXipCheckGLStacks::initClass(void)
{
    SO_NODE_INIT_CLASS(SoXipCheckGLStacks, SoNode, "Node");
}

void SoXipCheckGLStacks::GLRender(SoGLRenderAction * /* action */)
{
    GLenum err = glGetError(); 
    if (err != GL_NO_ERROR)
    { 
        SoDebugError::postInfo(label.getValue().getString(),
                               "OPENGL ERROR DETECTED: %s",
			       (char *)gluErrorString(err));
    }

    if (checkState.getValue())
    {
        if (mMaxProjectionStackDepth < 0)
        {
            glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &mMaxProjectionStackDepth);
            glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &mMaxModelviewStackDepth);
            glGetIntegerv(GL_MAX_COLOR_MATRIX_STACK_DEPTH, &mMaxColorStackDepth);
            glGetIntegerv(GL_MAX_TEXTURE_STACK_DEPTH, &mMaxTextureStackDepth);
            glGetIntegerv(GL_MAX_ATTRIB_STACK_DEPTH, &mMaxAttribStackDepth);
        }


        int projectionStackDepth = 1;
        int modelviewStackDepth = 1;
        int colorStackDepth = 1;
        int textureStackDepth = 1;
        int attribStackDepth = 1;

        glGetIntegerv(GL_PROJECTION_STACK_DEPTH, &projectionStackDepth);
        glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &modelviewStackDepth);
        glGetIntegerv(GL_COLOR_MATRIX_STACK_DEPTH, &colorStackDepth);
        glGetIntegerv(GL_TEXTURE_STACK_DEPTH, &textureStackDepth);
        glGetIntegerv(GL_ATTRIB_STACK_DEPTH, &attribStackDepth);

        if (projectionStackDepth != mProjectionStackDepth)
        {
            SoDebugError::postInfo(label.getValue().getString(),
			           "Projection Stack Depth Changed: %d (max %d)",
			           projectionStackDepth, mMaxProjectionStackDepth);

	    mProjectionStackDepth = projectionStackDepth;
        }

        if (modelviewStackDepth != mModelviewStackDepth)
        {
            SoDebugError::postInfo(label.getValue().getString(),
			           "Modelview Stack Depth Changed: %d (max %d)",
			           modelviewStackDepth, mMaxModelviewStackDepth);

	    mModelviewStackDepth = modelviewStackDepth;
        }

        if (colorStackDepth != mColorStackDepth)
        {
            SoDebugError::postInfo(label.getValue().getString(),
			           "Color Stack Depth Changed: %d (max %d)",
			           colorStackDepth, mMaxColorStackDepth);

	    mColorStackDepth = colorStackDepth;
        }

        if (textureStackDepth != mTextureStackDepth)
        {
            SoDebugError::postInfo(label.getValue().getString(),
			           "Texture Stack Depth Changed: %d (max %d)",
			           textureStackDepth, mMaxTextureStackDepth);

	    mTextureStackDepth = textureStackDepth;
        }

        if (attribStackDepth != mAttribStackDepth)
        {
            SoDebugError::postInfo(label.getValue().getString(),
			           "Attrib Stack Depth Changed: %d (max %d)",
			           attribStackDepth, mMaxAttribStackDepth);

	    mAttribStackDepth = attribStackDepth;
        }
    }
}

