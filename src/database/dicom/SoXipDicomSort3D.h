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
#ifndef SOXIPDICOMSORT3D
#define SOXIPDICOMSORT3D

#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/engines/SoSubEngine.h>


class SoXipDicomSort3D : public SoEngine
{
	SO_ENGINE_HEADER(SoXipDicomSort3D);

public:
	SoMFString images;
	SoSFShort volumeIndex;

	SoEngineOutput imagesInVolume;
	SoEngineOutput numberOfVolumes;

	static void initClass();

protected:
	SoXipDicomSort3D();
	virtual ~SoXipDicomSort3D();

	virtual void evaluate();
};


#endif // SOXIPDICOMSORT3D
