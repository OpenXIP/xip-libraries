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

# ifndef SO_VTK_STREAMLINE_H_
# define SO_VTK_STREAMLINE_H_


# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkStreamLine.h"

# include <xip/inventor/core/SoSFVariant.h>
# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoSFFloat.h"

class SoVtkStreamLine : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkStreamLine );

public:

	/// Constructor
	SoVtkStreamLine();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// StartPosition
	SoSFVariant StartPosition;
	/// NumberOfThreads
	SoSFInt32 NumberOfThreads;
	/// IntegrationStepLength
	SoSFFloat IntegrationStepLength;
	/// MaximumPropagationTime
	SoSFFloat MaximumPropagationTime;
	/// Source of type vtkDataSet
	SoSFVtkObject Source;
	/// IntegrationDirection
	SoSFInt32 IntegrationDirection;
	/// TerminalSpeed
	SoSFFloat TerminalSpeed;
	/// InputArrayToProcess
	SoSFVariant InputArrayToProcess;
	/// Input data of type vtkDataObject
	SoSFVtkObject Input;
	/// StepLength
	SoSFFloat StepLength;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// OrientationScalars
	SoSFInt32 OrientationScalars;
	/// SpeedScalars
	SoSFInt32 SpeedScalars;
	/// Vorticity
	SoSFInt32 Vorticity;
	/// Integrator of type vtkInitialValueProblemSolver
	SoSFVtkObject Integrator;
	/// SavePointInterval
	SoSFFloat SavePointInterval;

	
	// Outputs
	/// SoSFVtkObject of type vtkPolyData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkStreamLine();

	/// Evaluate Function
	virtual void evaluate();

	virtual void inputChanged(SoField *);
	
	/// vtkPolyData
	SoVtkObject *mOutput;
	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

private:

	vtkStreamLine* mObject;
};

#endif // SO_VTK_STREAMLINE_H_

