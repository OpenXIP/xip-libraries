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
 
 
 
# ifndef SO_VTK_GENERICSTREAMTRACER_H_
# define SO_VTK_GENERICSTREAMTRACER_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkGenericStreamTracer.h"

# include "Inventor/fields/SoSFEnum.h"
# include "Inventor/fields/SoSFVec3f.h"
# include "Inventor/fields/SoSFFloat.h"
# include "Inventor/fields/SoSFInt32.h"
# include "vtkType.h"

class SoVtkGenericStreamTracer : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkGenericStreamTracer );

public:
	enum Solvers
	{
		NONE,
		RUNGE_KUTTA4,
		RUNGE_KUTTA2,
		UNKNOWN,
		RUNGE_KUTTA45
	};
	
	enum Units
	{
		CELL_LENGTH_UNIT,
		TIME_UNIT,
		LENGTH_UNIT
	};
	
	enum ReasonForTermination
	{
		STAGNATION,
		UNEXPECTED_VALUE,
		OUT_OF_TIME,
		NOT_INITIALIZED,
		OUT_OF_DOMAIN,
		OUT_OF_STEPS
	};
	

	/// Constructor
	SoVtkGenericStreamTracer();

	/// Class Initialization
	static void initClass();
	/// Enum SolversEnum
	SoSFEnum SolversEnum;
	/// Enum UnitsEnum
	SoSFEnum UnitsEnum;
	/// Enum ReasonForTerminationEnum
	SoSFEnum ReasonForTerminationEnum;
	
	// Inputs
	/// InterpolatorPrototype of type vtkGenericInterpolatedVelocityField
	SoSFVtkObject InterpolatorPrototype;
	/// StartPosition
	SoSFVec3f StartPosition;
	/// MinimumIntegrationStep
	SoSFFloat MinimumIntegrationStep;
	/// InitialIntegrationStepUnit
	SoSFInt32 InitialIntegrationStepUnit;
	/// MaximumPropagation
	SoSFFloat MaximumPropagation;
	/// MaximumIntegrationStepUnit
	SoSFInt32 MaximumIntegrationStepUnit;
	/// TerminalSpeed
	SoSFFloat TerminalSpeed;
	/// IntegrationDirection
	SoSFInt32 IntegrationDirection;
	/// Source of type vtkDataSet
	SoSFVtkObject Source;
	/// RotationScale
	SoSFFloat RotationScale;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// IntegratorType
	SoSFInt32 IntegratorType;
	/// MinimumIntegrationStepUnit
	SoSFInt32 MinimumIntegrationStepUnit;
	/// ComputeVorticity
	SoSFInt32 ComputeVorticity;
	/// MaximumError
	SoSFFloat MaximumError;
	/// InitialIntegrationStep
	SoSFFloat InitialIntegrationStep;
	/// Integrator of type vtkInitialValueProblemSolver
	SoSFVtkObject Integrator;
	/// MaximumIntegrationStep
	SoSFFloat MaximumIntegrationStep;
	/// MaximumPropagationUnit
	SoSFInt32 MaximumPropagationUnit;
	/// MaximumNumberOfSteps of type vtkIdType
	SoSFVtkObject MaximumNumberOfSteps;

	
	// Outputs
	/// SoSFVtkObject of type vtkPolyData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;
	/// SoSFVtkObject of type vtkDataSet
	SoEngineOutput oSource;

protected:

	/// Destructor
	~SoVtkGenericStreamTracer();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkPolyData
	SoVtkObject *mOutput;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;

	/// vtkDataSet
	SoVtkObject *mSource;


private:

	vtkGenericStreamTracer* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_GENERICSTREAMTRACER_H_

