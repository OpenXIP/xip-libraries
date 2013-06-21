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
#ifndef SOXIPIMAGEOVERLAYSEARCH_H
#define SOXIPIMAGEOVERLAYSEARCH_H

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFTrigger.h>

class SoXipImageOverlaySearch : public SoEngine
{
	SO_ENGINE_HEADER( SoXipImageOverlaySearch );

public:
	SoXipImageOverlaySearch();

	SoXipSFDataImage	image;
	/// shapes should match given label, if not "" 
	SoMFString			label;
	/// shapes should match given caption , if not "" 
	SoSFString			caption;
	/// shapes class name should match given type, if not "" 
	SoSFString			type;
	SoSFTrigger			search;

	SoEngineOutput		overlays;

	static void initClass();

protected:
	~SoXipImageOverlaySearch();

	virtual SbBool readInstance( SoInput* in, unsigned short flags );
	virtual void inputChanged( SoField* whichField );
	virtual void evaluate();

	SbBool				m_ReadInstance;

};

#endif // SOXIPIMAGEOVERLAYSEARCH_H
