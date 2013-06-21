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
#ifndef SOXIPCONVERTDICOMTOXIPIMAGE_H
#define SOXIPCONVERTDICOMTOXIPIMAGE_H

#include <Inventor/engines/SoFieldConverter.h>
#include <Inventor/fields/SoSFShort.h>
#include <xip/inventor/core/SoXipMFDataImage.h>
#include <xip/inventor/dicom/SoXipSFDataDicom.h>
#include <xip/inventor/dicom/SoXipMFDataDicom.h>

class SoXipDataImage;

class SoXipConvertMFDicomToMFImage : public SoFieldConverter  
{
	SO_ENGINE_HEADER(SoXipConvertMFDicomToMFImage);

public:
	// Input:
	SoXipMFDataDicom input;

	// Output:
	SoEngineOutput   output;  // (SoXipMFDataImage)

	// Initialization
	static void initClass();

	// Constructor
	SoXipConvertMFDicomToMFImage();

protected:
	// Destructor
	virtual ~SoXipConvertMFDicomToMFImage();

	// Evaluation method
	virtual void evaluate();

	// These must be defined for a field converter. They return
	// the input and output connections of the given types. In
	// our case, we have only one input and one output, so we
	// know that those will be the given types.
	virtual SoField *        getInput(SoType type);
	virtual SoEngineOutput * getOutput(SoType type);

	SoXipMFDataImage	mData;

};

class SoXipConvertMFDicomToSFImage : public SoFieldConverter  
{
	SO_ENGINE_HEADER(SoXipConvertMFDicomToSFImage);

public:
	// Input:
	SoXipMFDataDicom input;
	SoSFShort		 index;

	// Output:
	SoEngineOutput   output;  // (SoXipSFDataImage)

	// Initialization
	static void initClass();

	// Constructor
	SoXipConvertMFDicomToSFImage();

protected:
	// Destructor
	virtual ~SoXipConvertMFDicomToSFImage();

	// Evaluation method
	virtual void evaluate();

	// These must be defined for a field converter. They return
	// the input and output connections of the given types. In
	// our case, we have only one input and one output, so we
	// know that those will be the given types.
	virtual SoField *        getInput(SoType type);
	virtual SoEngineOutput * getOutput(SoType type);

	SoXipDataImage *mOutputImage;
};


class SoXipConvertSFDicomToSFImage : public SoFieldConverter  
{
	SO_ENGINE_HEADER(SoXipConvertSFDicomToSFImage);

public:
	// Input:
	SoXipSFDataDicom input;

	// Output:
	SoEngineOutput   output;  // (SoXipSFDataImage)

	// Initialization
	static void initClass();

	// Constructor
	SoXipConvertSFDicomToSFImage();

protected:
	// Destructor
	virtual ~SoXipConvertSFDicomToSFImage();

	// Evaluation method
	virtual void evaluate();

	// These must be defined for a field converter. They return
	// the input and output connections of the given types. In
	// our case, we have only one input and one output, so we
	// know that those will be the given types.
	virtual SoField *        getInput(SoType type);
	virtual SoEngineOutput * getOutput(SoType type);

	SoXipDataImage *mOutputImage;
};

#endif	// SOXIPCONVERTDICOMTOXIPIMAGE_H
