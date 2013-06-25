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
#ifndef SoXipIncrement_H
#define SoXipIncrement_H

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipMFDataImage.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFPlane.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/SbLinear.h>

class SoXipDataImage;

class SoXipIncrement : public SoEngine
{
	SO_ENGINE_HEADER( SoXipIncrement );

public:
	SoXipIncrement();

	SoSFShort			sliceIndex;

	SoSFTrigger next;
	SoSFTrigger previous;

	SoEngineOutput		outSliceIndex;

	static void initClass();

protected:
	~SoXipIncrement();

	virtual void evaluate();
	virtual void inputChanged(SoField *which);
};

#endif // SoXipIncrement_H
