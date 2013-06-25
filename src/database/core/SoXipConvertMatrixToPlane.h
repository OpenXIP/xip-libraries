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

#ifndef SOXIPCONVERTMATRIXTOPLANE_H
#define SOXIPCONVERTMATRIXTOPLANE_H

#include <Inventor/engines/SoFieldConverter.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFPlane.h>


class SoXipConvertMatrixToPlane : public SoFieldConverter 
{
	SO_ENGINE_HEADER(SoXipConvertMatrixToPlane);

public:
	// Input:
	SoSFMatrix input;

	// Output:
	SoEngineOutput   output;

	// Initialization
	static void initClass();

	// Constructor
	SoXipConvertMatrixToPlane();

protected:
	// Destructor
	virtual ~SoXipConvertMatrixToPlane();

	// Evaluation method
	virtual void evaluate();

	// These must be defined for a field converter. They return
	// the input and output connections of the given types. In
	// our case, we have only one input and one output, so we
	// know that those will be the given types.
	virtual SoField *        getInput(SoType type);
	virtual SoEngineOutput * getOutput(SoType type);
};


#endif // SOXIPCONVERTMATRIXTOPLANE_H
