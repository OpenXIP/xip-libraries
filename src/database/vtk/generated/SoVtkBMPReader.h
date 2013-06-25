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
#ifndef SO_VTK_BMPREADER_H_
#define SO_VTK_BMPREADER_H_

#include <Inventor/engines/SoSubEngine.h>

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFULong.h>

#include <xip/inventor/vtk/SoSFVtkAlgorithmOutput.h>
#include <xip/inventor/vtk/SoSFVtkObject.h>

#include "vtkBMPReader.h"

class SoVtkBMPReader : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkBMPReader );

public:

	/// Constructor
	SoVtkBMPReader();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// DataSpacing
	SoSFVec3f DataSpacing;
	/// Transform of type vtkTransform
	SoSFVtkObject Transform;
	/// DataVOI
	SoMFInt32 DataVOI;
	/// FilePattern
	SoMFString FilePattern;
	/// FilePrefix
	SoMFString FilePrefix;
	/// FileDimensionality
	SoSFInt32 FileDimensionality;
	/// DataOrigin
	SoSFVec3f DataOrigin;
	/// Allow8BitBMP
	SoSFInt32 Allow8BitBMP;
	/// DataMask
	SoSFInt32 DataMask;
	/// DataScalarType
	SoSFInt32 DataScalarType;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// DataExtent
	SoMFInt32 DataExtent;
	/// HeaderSize
	SoSFULong HeaderSize;
	/// FileNameSliceOffset
	SoSFInt32 FileNameSliceOffset;
	/// NumberOfScalarComponents
	SoSFInt32 NumberOfScalarComponents;
	/// FileLowerLeft
	SoSFInt32 FileLowerLeft;
	/// ScalarArrayName
	SoMFString ScalarArrayName;
	/// DataByteOrder
	SoSFInt32 DataByteOrder;
	/// FileName
	SoMFString FileName;
	/// SwapBytes
	SoSFInt32 SwapBytes;
	/// FileNameSliceSpacing
	SoSFInt32 FileNameSliceSpacing;

	
	// Outputs
	/// SoSFVtkObject of type vtkTransform
	SoEngineOutput oTransform;
	/// SoSFVtkObject of type vtkImageData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkBMPReader();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkTransform
	SoVtkObject *mTransform;

	/// vtkImageData
	SoVtkObject *mOutput;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;


private:

	vtkBMPReader* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_BMPREADER_H_


