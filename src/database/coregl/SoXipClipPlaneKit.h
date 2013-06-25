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

#ifndef SO_XIP_BSP_KITS_SIMPLE_RAYCASTER_H
#define SO_XIP_BSP_KITS_SIMPLE_RAYCASTER_H


/** @file
Components      : SoXipClipPlaneKit
Author          : Lindholm S, SCR, Princeton
Creation Date   : 26-Aug-2008

Description     :

    Nodekit designed to wrap SoXipClipPlane and SoXipDrawClip plane nodes.
    Option exists to duplicate incoming plane and so cut out a "slice" of
    the volume(s).

Copyright © Siemens AG 2006-2007. All Rights Reserved.
*/


#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFPlane.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <xip/inventor/core/SoXipSFDataImage.h>

/**
 *	An Open Inventor node kit.
 */
class SoXipClipPlaneKit : public SoBaseKit
{
	SO_KIT_HEADER(SoXipClipPlaneKit);

public:
	/**
	 *	Constructor
	 */
	SoXipClipPlaneKit();
	/**	
	 *	Initializes the class
	 */
	static void initClass();

    SoSFPlane   plane;
    SoSFBool    on;
    SoSFBool    draw;
    SoSFBool    simMPR;
    SoSFFloat   widthMPR;

public:
	/**	
	 *	Defines fields for the new parts in the catalog
	 */
	SO_KIT_CATALOG_ENTRY_HEADER(top);

    SO_KIT_CATALOG_ENTRY_HEADER(rPlane);
    SO_KIT_CATALOG_ENTRY_HEADER(rDraw);
    SO_KIT_CATALOG_ENTRY_HEADER(rPlaneMpr);
    SO_KIT_CATALOG_ENTRY_HEADER(rDrawMpr);

protected:
	/**	
	 *	Destructor
	 */
	virtual ~SoXipClipPlaneKit();
	/**	
	 *	GLRender
	 */
	virtual void GLRender(SoGLRenderAction * action);
	/**	
	 *	create field connections and initial setup
	 */
    void setKitConnections();

    int mNodeId;
};


#endif // SO_XIP_BSP_SIMPLE_RAYCASTER_KIT_H
