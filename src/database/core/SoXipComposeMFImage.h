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
#ifndef SOXIPCOMPOSEMFIMAGE_H
#define SOXIPCOMPOSEMFIMAGE_H

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/engines/SoSubEngine.h>

class SoXipComposeMFImage : public SoEngine
{
	SO_ENGINE_HEADER( SoXipComposeMFImage );

public:
	SoXipComposeMFImage();

	SoXipSFDataImage	input0;
	SoXipSFDataImage	input1;
	SoXipSFDataImage	input2;
	SoXipSFDataImage	input3;
	SoXipSFDataImage	input4;
	SoXipSFDataImage	input5;
	SoXipSFDataImage	input6;
	SoXipSFDataImage	input7;

	SoEngineOutput		output;

	static void initClass();

protected:
	~SoXipComposeMFImage();

	virtual void evaluate();
};

#endif // SOXIPCOMPOSEMFIMAGE_H
