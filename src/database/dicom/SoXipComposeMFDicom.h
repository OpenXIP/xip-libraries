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

#ifndef SOXIPCOMPOSEMFDICOM_H
#define SOXIPCOMPOSEMFDICOM_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFShort.h>
#include <xip/inventor/dicom/SoXipSFDataDicom.h>

class SoXipComposeMFDicom : public SoEngine
{
	SO_ENGINE_HEADER( SoXipComposeMFDicom );

public:
	SoXipComposeMFDicom();

	SoXipSFDataDicom	input0;
	SoXipSFDataDicom	input1;
	SoXipSFDataDicom	input2;
	SoXipSFDataDicom	input3;
	SoXipSFDataDicom	input4;
	SoXipSFDataDicom	input5;
	SoXipSFDataDicom	input6;
	SoXipSFDataDicom	input7;

	SoEngineOutput		output;

	static void initClass();

protected:
	~SoXipComposeMFDicom();

	virtual void evaluate();
};

#endif // SOXIPCOMPOSEMFDICOM_H
