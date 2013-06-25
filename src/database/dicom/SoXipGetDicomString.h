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
#ifndef SOXIPGETDICOMSTRING_H
#define SOXIPGETDICOMSTRING_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <xip/inventor/dicom/SoXipMFDataDicom.h>


class SoXipGetDicomString : public SoEngine
{
	SO_ENGINE_HEADER(SoXipGetDicomString);

public:
	SoXipGetDicomString();
	static void initClass();

	enum
	{
		METAINFO,
		DATASET
	} itemType;

	SoXipMFDataDicom	dicom;
	SoSFEnum			item;
	SoSFUShort			group;
	SoSFUShort			element;
	SoSFBool			searchIntoSub;

	SoEngineOutput		string;

protected:
	virtual ~SoXipGetDicomString();
	virtual void evaluate();
};

#endif // SOXIPGETDICOMSTRING_H
