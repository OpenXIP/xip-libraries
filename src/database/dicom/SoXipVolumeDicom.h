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
#ifndef SOXIPVOLUMEDICOM_H
#define SOXIPVOLUMEDICOM_H

#include <Inventor/engines/SoSubEngine.h>
#include <xip/inventor/dicom/SoXipMFDataDicom.h>

class SoXipDataImage;

class SoXipVolumeDicom : public SoEngine  
{
	SO_ENGINE_HEADER(SoXipVolumeDicom);

public:
	// Input:
	SoXipMFDataDicom input;

	// Output:
	SoEngineOutput   output;  // (SoXipSFDataImage)

	// Initialization
	static void initClass();

	// Constructor
	SoXipVolumeDicom();

protected:
	// Destructor
	virtual ~SoXipVolumeDicom();

	// Evaluation method
	virtual void evaluate();

	SoXipDataImage *mOutputImage;
};

#endif	// SOXIPVOLUMEDICOM_H
