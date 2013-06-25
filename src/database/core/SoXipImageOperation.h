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

#ifndef SOXIPIMAGEOPERATION_H
#define SOXIPIMAGEOPERATION_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFEnum.h>
#include <xip/inventor/core/SoXipSFDataImage.h>

class SoXipDataImage;

class SoXipImageOperation : public SoEngine
{
	SO_ENGINE_HEADER( SoXipImageOperation );

public:
	enum OperationEnum
	{
		MASK_OR,
		MASK_AND,
		MASK_NOR
	};

	SoXipImageOperation();

    // input curve 1
    SoXipSFDataImage		mask1;
    // input curve 2
    SoXipSFDataImage		mask2;
    // input of label 1 
    SoSFEnum				operation;

    // output of saving status
	SoEngineOutput			mask;

    static void initClass();

protected:
	virtual ~SoXipImageOperation();

	virtual void evaluate();

	SoXipDataImage*			mMaskData;
    
};

#endif // SOXIPIMAGEOPERATION_H
