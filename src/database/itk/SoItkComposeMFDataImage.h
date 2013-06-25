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
#ifndef SOITKCOMPOSEMFDATAIMAGE_H
#define SOITKCOMPOSEMFDATAIMAGE_H

#include <Inventor/engines/SoSubEngine.h>
#include <xip/inventor/itk/SoItkSFDataImage.h>

class SoItkComposeMFDataImage : public SoEngine
{
	SO_ENGINE_HEADER( SoItkComposeMFDataImage );

public:
	SoItkComposeMFDataImage();

	SoItkSFDataImage 	input1;
	SoItkSFDataImage 	input2;
	SoItkSFDataImage 	input3;
	SoItkSFDataImage 	input4;
	SoItkSFDataImage 	input5;
	SoItkSFDataImage 	input6;
	SoItkSFDataImage 	input7;
	SoItkSFDataImage 	input8;

	SoEngineOutput		output;

	static void initClass();

protected:
	~SoItkComposeMFDataImage();

	virtual void evaluate();

};

#endif // SOITKCOMPOSEMFDATAIMAGE_H
