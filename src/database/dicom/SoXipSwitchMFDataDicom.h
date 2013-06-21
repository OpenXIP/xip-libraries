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
#ifndef SOXIPSWITCHMFDATADICOM_H
#define SOXIPSWITCHMFDATADICOM_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFShort.h>
#include <xip/inventor/dicom/SoXipMFDataDicom.h>

class SoXipSwitchMFDataDicom : public SoEngine
{
	SO_ENGINE_HEADER( SoXipSwitchMFDataDicom );

public:
	/// Constructor
	SoXipSwitchMFDataDicom();

	/// Input image fields
	SoXipMFDataDicom	dicom1;
	SoXipMFDataDicom	dicom2;
	SoXipMFDataDicom	dicom3;
	SoXipMFDataDicom	dicom4;
    SoSFShort			index;

	/// Selected image output
	SoEngineOutput		dicom;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
    virtual ~SoXipSwitchMFDataDicom();

	/// Engines' evaluate method
    virtual void evaluate();

};

#endif // SOXIPSWITCHMFDATADICOM_H
