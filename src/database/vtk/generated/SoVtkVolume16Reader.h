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
#ifndef SO_VTK_VOLUME16READER_H_
#define SO_VTK_VOLUME16READER_H_

#include <Inventor/engines/SoSubEngine.h>

#include <xip/inventor/vtk/SoSFVtkAlgorithmOutput.h>
#include <xip/inventor/vtk/SoSFVtkObject.h>

#include "vtkVolume16Reader.h"

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFUShort.h>

#include <xip/inventor/core/SoSFVariant.h>
#include <xip/inventor/core/SbVariant.h>

class SoVtkVolume16Reader : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkVolume16Reader );

public:

	/// Constructor
	SoVtkVolume16Reader();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// DataSpacing
	SoSFVec3f DataSpacing;
	/// Transform of type vtkTransform
	SoSFVtkObject Transform;
	/// HeaderSize
	SoSFInt32 HeaderSize;
	/// DataDimensions
	SoSFVec2f DataDimensions;
	/// FilePattern
	SoMFString FilePattern;
	/// FilePrefix
	SoMFString FilePrefix;
	/// DataByteOrder
	SoSFInt32 DataByteOrder;
	/// ImageRange
	SoSFVec2f ImageRange;
	/// SwapBytes
	SoSFInt32 SwapBytes;
	/// DataOrigin
	SoSFVec3f DataOrigin;
	/// DataMask
	SoSFUShort DataMask;
	/// InputArrayToProcess
	SoSFVariant InputArrayToProcess;
	/// Input data of type vtkDataObject
	SoSFVtkObject Input;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkObject of type vtkImageData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type vtkVolume16Reader
	SoEngineOutput OutputDCO;

protected:

	/// Destructor
	~SoVtkVolume16Reader();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);
	
	/// vtkImageData
	SoVtkObject *mOutput;
	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;
	/// vtkVolume16Reader
	SoVtkObject *mOutputDCO;

private:

	vtkVolume16Reader* mObject;
};

#endif // SO_VTK_VOLUME16READER_H_


