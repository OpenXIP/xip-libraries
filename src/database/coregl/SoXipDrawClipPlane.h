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

#ifndef SO_XIP_DRAW_CLIP_PLANE_H
#define SO_XIP_DRAW_CLIP_PLANE_H


/** @file
Components      : SoXipDrawClipPlaneKit
Author          : Burns M, Lindholm S, SCR, Princeton
Creation Date   : 26-Aug-2008

Description     :

    Visualizes a clip plane (or any plane) with a (black) polygon.

Copyright © Siemens AG 2006-2007. All Rights Reserved.
*/


#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFPlane.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/actions/SoGLRenderAction.h>

class SoXipDrawClipPlane : public SoNode
{
	SO_NODE_HEADER(SoXipDrawClipPlane);

public:
	SoXipDrawClipPlane();

	void GLRender(SoGLRenderAction* action);
	
	static void initClass();

	SoSFPlane  plane;
    SoSFBool   on;
	SoSFMatrix boundingBox;

private:
  const static char indexList[256][16];
  const static char edgeList[12][2];
};


#endif // SO_XIP_DRAW_CLIP_PLANE_H
