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
#ifndef SOXIPSORTDICOM_H
#define SOXIPSORTDICOM_H

#include <Inventor/engines/SoSubEngine.h>
#include <xip/inventor/dicom/SoXipMFDataDicom.h>

// Forward Declarations
class DcmDataset;

class SoXipSortDicom : public SoEngine
{
	SO_ENGINE_HEADER( SoXipSortDicom );

public:
	SoXipSortDicom();
	static void initClass();

protected:
	~SoXipSortDicom();

public:
	SoXipMFDataDicom input;

	SoEngineOutput output; // SoXipMFDataDicom

protected:
	virtual void evaluate();
	virtual int getNumSlices( DcmDataset* dataset );
	virtual double computePositionZ( DcmDataset* dataset );

};

#endif	// SOXIPSORTDICOM_H
