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

# ifndef SO_VTK_PLOT3DREADER_H_
# define SO_VTK_PLOT3DREADER_H_


# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkPLOT3DReader.h"

# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoMFString.h"
# include "Inventor/fields/SoSFFloat.h"
# include <xip/inventor/core/SoMFVariant.h>
# include <xip/inventor/core/SoSFVariant.h>

class SoVtkPLOT3DReader : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkPLOT3DReader );

public:

	/// Constructor
	SoVtkPLOT3DReader();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// HasByteCount
	SoSFInt32 HasByteCount;
	/// ByteOrder
	SoSFInt32 ByteOrder;
	/// QFileName
	SoMFString QFileName;
	/// Uvinf
	SoSFFloat Uvinf;
	/// Function
	SoMFVariant Function;
	/// ScalarFunctionNumber
	SoSFInt32 ScalarFunctionNumber;
	/// DoNotReduceNumberOfOutputs
	SoSFInt32 DoNotReduceNumberOfOutputs;
	/// InputArrayToProcess
	SoSFVariant InputArrayToProcess;
	/// Vvinf
	SoSFFloat Vvinf;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// BinaryFile
	SoSFInt32 BinaryFile;
	/// IBlanking
	SoSFInt32 IBlanking;
	/// TwoDimensionalGeometry
	SoSFInt32 TwoDimensionalGeometry;
	/// Wvinf
	SoSFFloat Wvinf;
	/// NumberOfInputConnections
	SoSFVariant NumberOfInputConnections;
	/// Gamma
	SoSFFloat Gamma;
	/// VectorFunctionNumber
	SoSFInt32 VectorFunctionNumber;
	/// ForceRead
	SoSFInt32 ForceRead;
	/// FileName
	SoMFString FileName;
	/// R
	SoSFFloat R;
	/// MultiGrid
	SoSFInt32 MultiGrid;
	/// XYZFileName
	SoMFString XYZFileName;

	
	// Outputs
	/// SoSFVtkObject of type vtkStructuredGrid
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkPLOT3DReader();

	/// Evaluate Function
	virtual void evaluate();

	virtual void inputChanged(SoField *);
	
	/// vtkStructuredGrid
	SoVtkObject *mOutput;
	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

private:

	vtkPLOT3DReader* mObject;
};

#endif // SO_VTK_PLOT3DREADER_H_

