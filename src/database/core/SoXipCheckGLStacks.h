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
/*
  ------------------------------------------------------------------------

    SoXipCheckGLStacks.h

    Check the usage of OpenGL stacks

    Copyright (C) 2007 - 2009, Siemens Corporate Research, Inc.

    Authors:
      Patric Ljung, patric.ljung@siemens.com

    This file is part of Open XIP under the caBig license, see end of
    file for details.

  ------------------------------------------------------------------------
*/

/*
  Scope:

  This node checks some OpenGL states and track changes in stack depth.
*/

#ifndef SOXIPCHECKGLSTACKS_H
#define SOXIPCHECKGLSTACKS_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFBool.h>


class SoXipCheckGLStacks : public SoNode
{
    SO_NODE_HEADER(SoXipCheckGLStacks);
 
public:
    static void initClass();

    SoXipCheckGLStacks();

    SoSFBool    checkState;
    SoSFString  label;

protected:	
    ~SoXipCheckGLStacks();

    virtual void GLRender(SoGLRenderAction* action);

    int		mProjectionStackDepth;
    int		mModelviewStackDepth;
    int		mColorStackDepth;
    int		mTextureStackDepth;
    int		mAttribStackDepth;

    int		mMaxProjectionStackDepth;
    int		mMaxModelviewStackDepth;
    int		mMaxColorStackDepth;
    int		mMaxTextureStackDepth;
    int		mMaxAttribStackDepth;
};



#endif // SOXIPCHECKGL_H
