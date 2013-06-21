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
#ifndef SOXIPSAVEDIOCM_H
#define SOXIPSAVEDIOCM_H

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/dicom/SoXipSFDataDicom.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFTrigger.h>

class SoXipSaveDicom : public SoEngine
{
	SO_ENGINE_HEADER(SoXipSaveDicom);

public:
	SoXipSaveDicom();
	static void initClass();

protected:
	virtual ~SoXipSaveDicom();

public:
	SoXipSFDataImage	image;			// input
	SoXipSFDataDicom	referenceImage;	// Input
	SoSFString			storage;		// Input
	SoSFShort			seriesNumber;	// Input
	SoSFShort		    imageNumber;	// Input
	SoSFTrigger			apply;

	SoEngineOutput		id;				// output

protected:
	//! This is called when an input value changes - we will use
	//! it to figure out which input was changed most recently
	virtual void inputChanged(SoField *whichField);

	//! Evaluation method
	virtual void evaluate();

};

#endif // SOXIPSAVEDIOCM_H
