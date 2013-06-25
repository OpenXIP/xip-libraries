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
#ifndef SOXIPIMAGEOVERLAYADD_H
#define SOXIPIMAGEOVERLAYADD_H

#include <xip/inventor/core/SoXipMFDataImage.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFTrigger.h>

class SoXipImageOverlayAdd : public SoEngine
{
	SO_ENGINE_HEADER( SoXipImageOverlayAdd );

public:
	SoXipImageOverlayAdd();

	SoXipMFDataImage	image;
	SoMFNode			overlays; 
	SoSFBool			overwrite;
	SoSFTrigger			add;

	SoEngineOutput		status;	// SoSFString

	static void initClass();

protected:
    ~SoXipImageOverlayAdd ();

	virtual SbBool readInstance( SoInput* in, unsigned short flags );
    virtual void inputChanged( SoField* whichField );
    virtual void evaluate();

	SbBool				m_ReadInstance;

};

#endif // SOXIPIMAGEOVERLAYADD_H
