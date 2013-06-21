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
#ifndef SOXIPSWITCHMFDATAIMAGE_H
#define SOXIPSWITCHMFDATAIMAGE_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFShort.h>
#include <xip/inventor/core/SoXipMFDataImage.h>

class SoXipSwitchMFDataImage : public SoEngine
{
	SO_ENGINE_HEADER( SoXipSwitchMFDataImage );

public:
	/// Constructor
	SoXipSwitchMFDataImage();

	/// Input image fields
	SoXipMFDataImage	image1;
	SoXipMFDataImage	image2;
	SoXipMFDataImage	image3;
	SoXipMFDataImage	image4;
    SoSFShort			index;

	/// Selected image output
	SoEngineOutput		image;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
    virtual ~SoXipSwitchMFDataImage();

	/// Engines' evaluate method
    virtual void evaluate();

};

#endif // SOXIPSWITCHMFDATAIMAGE_H
