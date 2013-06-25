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
#ifndef SOXIPLOADRAW_H
#define SOXIPLOADRAW_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFString.h>

class SoXipDataImage;

class SoXipLoadRaw : public SoEngine
{
	SO_ENGINE_HEADER( SoXipLoadRaw );

public:
	/// Voxel Type enum
	enum VoxelType
	{
		UBYTE,
		USHORT,
        SHORT,
		FLOAT32
	};

	/// Voxel type
	SoSFEnum		voxelType;
	/// Image width
	SoSFShort		width;
	/// Image height
	SoSFShort		height;
	/// Image depth
	SoSFShort		depth;
	/// Image number of bits used
	SoSFShort		bitsUsed;
	/// Image model matrix
	SoSFMatrix		modelMatrix;
	/// Input file
	SoSFString		file;

	/// Output image (SoXipSFDataImage)
	SoEngineOutput	output;

	/// Constructor
	SoXipLoadRaw();

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	virtual ~SoXipLoadRaw();

	/// Evaluate method
	virtual void evaluate();

	/// Read instance method
	virtual SbBool readInstance( SoInput* in, unsigned short flags );

	SoXipDataImage*		mDataOutput;
};

#endif // SOXIPLOADRAW_H
