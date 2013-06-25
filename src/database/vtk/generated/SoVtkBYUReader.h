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
#ifndef SO_VTK_BYUREADER_H_
#define SO_VTK_BYUREADER_H_

#include <Inventor/engines/SoSubEngine.h>

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFString.h>

#include <xip/inventor/vtk/SoSFVtkAlgorithmOutput.h>
#include <xip/inventor/vtk/SoSFVtkObject.h>
#include <xip/inventor/core/SoSFVariant.h>

#include "vtkBYUReader.h"

class SoVtkBYUReader : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkBYUReader );

public:

	/// Constructor
	SoVtkBYUReader();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// ReadTexture
	SoSFInt32 ReadTexture;
	/// ScalarFileName
	SoMFString ScalarFileName;
	/// TextureFileName
	SoMFString TextureFileName;
	/// ReadDisplacement
	SoSFInt32 ReadDisplacement;
	/// GeometryFileName
	SoMFString GeometryFileName;
	/// PartNumber
	SoSFInt32 PartNumber;
	/// DisplacementFileName
	SoMFString DisplacementFileName;
	/// FileName
	SoMFString FileName;
	/// InputArrayToProcess
	SoSFVariant InputArrayToProcess;
	/// Input data of type vtkDataObject
	SoSFVtkObject Input;
	/// ReadScalar
	SoSFInt32 ReadScalar;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;

	
	// Outputs
	/// SoSFVtkObject of type vtkPolyData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkBYUReader();

	/// Evaluate Function
	virtual void evaluate();

	virtual void inputChanged(SoField *);
	
	/// vtkPolyData
	SoVtkObject *mOutput;
	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

private:

	vtkBYUReader* mObject;
};

#endif // SO_VTK_BYUREADER_H_


