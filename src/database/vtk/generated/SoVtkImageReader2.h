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
/*
 * \brief
 * \author Sylvain Jaume, Francois Huguet
 */
/*
 * \author Sylvain Jaume, Francois Huguet
 */
#ifndef SO_VTK_IMAGEREADER2_H_
#define SO_VTK_IMAGEREADER2_H_

#include <Inventor/engines/SoSubEngine.h>

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFULong.h>

#include <xip/inventor/vtk/SoSFVtkAlgorithmOutput.h>
#include <xip/inventor/vtk/SoSFVtkObject.h>
#include <xip/inventor/core/SoSFVariant.h>

#include "vtkImageReader2.h"

class SoVtkImageReader2 : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkImageReader2 );

public:

	/// Constructor
	SoVtkImageReader2();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// DataSpacing
	SoSFVec3f DataSpacing;
	/// FilePattern
	SoMFString FilePattern;
	/// FilePrefix
	SoMFString FilePrefix;
	/// FileDimensionality
	SoSFInt32 FileDimensionality;
	/// DataOrigin
	SoSFVec3f DataOrigin;
	/// InputArrayToProcess
	SoSFVariant InputArrayToProcess;
	/// Input data of type vtkDataObject
	SoSFVtkObject Input;
	/// DataScalarType
	SoSFInt32 DataScalarType;
	/// DataExtent
	SoMFInt32 DataExtent;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// HeaderSize
	SoSFULong HeaderSize;
	/// FileNameSliceOffset
	SoSFInt32 FileNameSliceOffset;
	/// NumberOfScalarComponents
	SoSFInt32 NumberOfScalarComponents;
	/// FileLowerLeft
	SoSFInt32 FileLowerLeft;
	/// DataByteOrder
	SoSFInt32 DataByteOrder;
	/// FileName
	SoMFString FileName;
	/// SwapBytes
	SoSFInt32 SwapBytes;
	/// FileNameSliceSpacing
	SoSFInt32 FileNameSliceSpacing;

	
	// Outputs
	/// SoSFVtkObject of type vtkImageData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkImageReader2();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);
	
	/// vtkImageData
	SoVtkObject *mOutput;
	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

private:

	vtkImageReader2* mObject;
};

#endif // SO_VTK_IMAGEREADER2_H_


