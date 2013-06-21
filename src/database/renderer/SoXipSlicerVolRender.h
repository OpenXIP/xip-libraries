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
 *	SoXipSlicerVolRender. An Open Inventor node kit to
 *	wrap the SoXipSlicer node
 */

#ifndef SoXIPSLICERVOLRENDER_H
#define SoXIPSLICERVOLRENDER_H

#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFEnum.h>


class SoXipSlicer;
class SoXipUniformMatrix4;



/**
 *	SoXipSlicerVolRender. An Open Inventor node kit to
 *	wrap the SoXipSlicer node.
 *	(Utility class for grouping nodes of the intersection line geometry)
 */
class SoXipSlicerVolRender : public SoBaseKit 
{
	SO_KIT_HEADER(SoXipSlicerVolRender);

public:
	/**
	 *	Constructor
	 */
	SoXipSlicerVolRender();
	/**	
	 *	Initializes the class
	 */
	static void initClass();

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
        VRT,
        MAXIP,
		MINIP
    };

	/**	
	 *	Fields for rendering mode, sampling rate and compositing direction
	 */
    SoSFEnum		compositing;
	SoSFEnum		mode;
    SoSFInt32		numSlices;

public:
	/**	
	 *	Defines fields for the new parts in the catalog
	 */ 
	SO_KIT_CATALOG_ENTRY_HEADER(boundingBoxMatrix);
	SO_KIT_CATALOG_ENTRY_HEADER(slicer);

protected:
	/**	
	 *	Destructor
	 */
	virtual ~SoXipSlicerVolRender();
	/**	
	 *	GLRender
	 */
	virtual void GLRender(SoGLRenderAction * action);

};


#endif 
