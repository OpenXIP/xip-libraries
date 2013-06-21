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

    SoXipDisableTexturing.cc

    Disable texture for selected targets (1D, 2D, 3D, CubeMap)

    Copyright (C) 2008 - 2009, Siemens Corporate Research, Inc.

    Authors:
      Stefan Lindholm, stefan.lindholm.ext@siemens.com

    This file is part of Open XIP under the caBig license, see end of
    file for details.

  ------------------------------------------------------------------------
*/

#ifndef SO_XIP_DISABLE_TEXTURING_H
#define SO_XIP_DISABLE_TEXTURING_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFBool.h>

class SoXipDisableTexturing : public SoNode
{
    SO_NODE_HEADER(SoXipDisableTexturing);

public:
    SoSFBool	disable1D;
    SoSFBool	disable2D;
    SoSFBool	disable3D;
    SoSFBool	disableCubeMap;

    static void initClass();
    SoXipDisableTexturing();

protected:

    virtual void GLRender(SoGLRenderAction *action);

private:

    virtual ~SoXipDisableTexturing(); 

    int mTexUnits;
    int mNodeId;
};


#endif //SO_XIP_DISABLE_TEXTURING_H



