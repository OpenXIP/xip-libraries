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
#ifndef SOXIPGETDICOMREFERENCE_H
#define SOXIPGETDICOMREFERENCE_H

#include <Inventor/engines/SoSubEngine.h>
#include <xip/inventor/dicom/SoXipMFDataDicom.h>
#include <xip/inventor/core/SoXipMFDataImage.h>

class SoXipGetDicomReference : public SoEngine
{
	SO_ENGINE_HEADER( SoXipGetDicomReference );

public:
	SoXipGetDicomReference();

	SoXipMFDataImage	image;

	SoEngineOutput		dicom; // SoXipMFDataDicom

	static void initClass();

protected:
	virtual ~SoXipGetDicomReference();

	virtual void evaluate();

};

#endif // SOXIPGETDICOMREFERENCE_H
