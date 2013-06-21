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

#ifndef  SOXIPCLIPPLANE_H
#define  SOXIPCLIPPLANE_H

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFPlane.h>
#include <Inventor/nodes/SoSubNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXipClipPlane
//
//  Clipping plane node used by the SoXipSlicer to clip slices computed for VR.
//
//////////////////////////////////////////////////////////////////////////////

class SoXipClipPlane : public SoNode {

    SO_NODE_HEADER(SoXipClipPlane);

  public:
    // Fields
    SoSFPlane		plane;	// Plane that defines half-space
    SoSFBool		on;		// Whether clipping plane is active
	SoSFBool		flip;	// Flip the plane direction when setting the element

    // Constructor
    SoXipClipPlane();

  SoEXTENDER public:
    virtual void	doAction(SoAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	pick(SoPickAction *action);

  SoINTERNAL public:
    static void		initClass();

  protected:
    virtual ~SoXipClipPlane();
};

#endif // SOXIPCLIPPLANE_H
