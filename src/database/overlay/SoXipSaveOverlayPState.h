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
*	@file    SoXipSaveOverlayPState.h
*	@brief   Declaration of the SoXipSaveOverlayPState class
*	@author  Babu Samuel
**/

#ifndef SOXIPSAVEOVERLAYPSTATE_H
#define SOXIPSAVEOVERLAYPSTATE_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoMFNode.h>
#include <xip/inventor/dicom/SoXipSFDataDicom.h>

class SoXipPState;


class SoXipSaveOverlayPState : public SoEngine
{
	SO_ENGINE_HEADER(SoXipSaveOverlayPState);

public:
	SoXipSaveOverlayPState();
	static void initClass();

protected:
	virtual ~SoXipSaveOverlayPState();

public:
	SoMFNode			overlays;			// Input
	SoXipSFDataDicom	image;				// Input
	SoSFString			pstateFile;			// Input
	SoSFTrigger			save;

	SoEngineOutput		status;				// Output 

protected:
	//! This is called when an input value changes - we will use
	//! it to figure out which input was changed most recently
	virtual void inputChanged(SoField *whichField);

	virtual void evaluate();

private:
	// Adds the graphic shape to presentation state
	void addGraphicToPState(SoXipManipulableShape* shape, SoXipPState *pstate, SbMatrix modelMatrix, SbXipImageDimensions imgDimension, int layerIdx);

	// Adds the annotation to presentation state
	void addAnnotationToPState(SoXipManipulableShape* shape, SoXipPState *pstate, SbMatrix modelMatrix, SbXipImageDimensions imgDimension, int layerIdx);
};


#endif // SOXIPSAVEOVERLAYPSTATE_H
