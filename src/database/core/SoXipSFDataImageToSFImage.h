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

#ifndef SOXIPSFDATAIMAGETOSFIMAGE_H
#define SOXIPSFDATAIMAGETOSFIMAGE_H

#include <xip/inventor/core/SoXipSFDataImage.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFImage.h>

class SoXipSFDataImageToSFImage : public SoEngine
{
	SO_ENGINE_HEADER( SoXipSFDataImageToSFImage );

public:
	/// Constructor
	SoXipSFDataImageToSFImage();

	/// Input image
	SoXipSFDataImage	input;

	/// Output image
	SoEngineOutput		output;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipSFDataImageToSFImage();

	/// Evaluate method
	virtual void evaluate();
};

#endif // SOXIPSFDATAIMAGETOSFIMAGE_H
