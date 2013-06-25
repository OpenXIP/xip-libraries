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
#ifndef SoXipDecomposeVec6_H
#define SoXipDecomposeVec6_H

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

class SoXipDecomposeVec6 : public SoEngine
{
	SO_ENGINE_HEADER( SoXipDecomposeVec6 );

public:
	SoXipDecomposeVec6();

	SoSFMatrix			modelMatrix;
	SoSFPlane			plane;
	SoXipSFDataImage    image;
	SoSFShort			sliceIndex;
	SoMFInt32			inVOI;

	SoEngineOutput		output;
	SoEngineOutput		numSlices;
	SoEngineOutput		xmin;
	SoEngineOutput		xmax;
	SoEngineOutput		ymin;
	SoEngineOutput		ymax;
	SoEngineOutput		zmin;
	SoEngineOutput		zmax;

	static void initClass();

protected:
	~SoXipDecomposeVec6();

	virtual void evaluate();

	SoXipDataImage*		mImageData;
	SoXipMFDataImage	mOutputs;	

};

#endif // SoXipDecomposeVec6_H
