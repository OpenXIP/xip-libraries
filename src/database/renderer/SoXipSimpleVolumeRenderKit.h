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
 *	SoXipSimpleVolumeRenderKit. An Open Inventor node kit to
 *	wrap the SoXipSlicer node
 */

#ifndef SO_XIP_SIMPLE_VOLUME_RENDER_KIT_H
#define SO_XIP_SIMPLE_VOLUME_RENDER_KIT_H

#define USE_DATA_IMAGE_LUT

#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>

#include <xip/inventor/core/SoXipSFDataImage.h>

//#include <xip/inventor/core/SoXipDataImage.h>
//#include <xip/inventor/core/SbXipImage.h>
//#include "../core/SoXipTexture.h"
//#include "../coregl/SoXipTextureUnit.h"

#include "SoXipSlicerShader.h"
#include "SoXipSlicer.h"

/**
 *	SoXipSimpleVolumeRenderKit. An Open Inventor node kit to
 *	wrap the SoXipSlicer node.
 *	(Utility class for grouping nodes of the intersection line geometry)
 */
class SoXipSimpleVolumeRenderKit : public SoBaseKit 
{
	SO_KIT_HEADER(SoXipSimpleVolumeRenderKit);

public:
	/**
	 *	Constructor
	 */
	SoXipSimpleVolumeRenderKit();
	/**	
	 *	Initializes the class
	 */
	static void initClass();

    SoXipSFDataImage volumeData;
    SoXipSFDataImage lutData;
    SoSFBool         useComplexity;
    SoSFInt32		 samplingFrequency;
    SoSFBool		 selfShading;
    SoSFBool		 gradLighting;

public:
	/**	
	 *	Defines fields for the new parts in the catalog
	 */ 
	SO_KIT_CATALOG_ENTRY_HEADER(top);
	SO_KIT_CATALOG_ENTRY_HEADER(volumeUnit);
	SO_KIT_CATALOG_ENTRY_HEADER(volume);
	SO_KIT_CATALOG_ENTRY_HEADER(lutUnit);
	SO_KIT_CATALOG_ENTRY_HEADER(lut);
	SO_KIT_CATALOG_ENTRY_HEADER(shader);
	SO_KIT_CATALOG_ENTRY_HEADER(slicer);

protected:
	/**	
	 *	Destructor
	 */
	virtual ~SoXipSimpleVolumeRenderKit();
	/**	
	 *	GLRender
	 */
	virtual void GLRender(SoGLRenderAction * action);
	/**	
	 *	getBoundingBox
	 */
	virtual void getBoundingBox (SoGetBoundingBoxAction * action);
	/**	
	 *	create field connections and initial setup
	 */
    void setKitConnections();

    int  mNodeId;
};


#endif // SO_XIP_SIMPLE_VOLUME_RENDER_KIT_H
