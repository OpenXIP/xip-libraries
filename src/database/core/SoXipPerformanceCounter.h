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
#ifndef SOXIPPERFORMANCECOUNTER_H
#define SOXIPPERFORMANCECOUNTER_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFTrigger.h>


class SoXipPerformanceCounter : public SoEngine
{
	SO_ENGINE_HEADER(SoXipPerformanceCounter);

public:
	SoXipPerformanceCounter();
	static void initClass();

	SoSFInt32		min;
	SoSFInt32		max;
	SoSFInt32		step;
	SoSFBool		on;
	SoSFFloat		frequency;
	SoSFTime		timeIn;
	SoSFInt32		reset;
	
	SoEngineOutput	output;
	SoEngineOutput	syncOut;

protected:
	virtual ~SoXipPerformanceCounter();
	virtual void evaluate();
	virtual void inputChanged (SoField *which);

	int    mCounter;
	SbTime mStartTime;
	SbTime mDeltaTime;
};

#endif // SOXIPPERFORMANCECOUNTER_H
