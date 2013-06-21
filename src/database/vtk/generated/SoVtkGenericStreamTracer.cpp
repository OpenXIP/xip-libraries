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
 
 
# include "SoVtkGenericStreamTracer.h"
# include "SoVtkUtils.h"

# include "vtkGenericInterpolatedVelocityField.h"
# include "vtkDataSet.h"
# include "vtkAlgorithmOutput.h"
# include "vtkInitialValueProblemSolver.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkGenericStreamTracer )

SoVtkGenericStreamTracer::SoVtkGenericStreamTracer()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkGenericStreamTracer);

	mObject = vtkGenericStreamTracer::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkGenericStreamTracer *aGenericStreamTracer = vtkGenericStreamTracer::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(InterpolatorPrototype, (0));

	SO_ENGINE_ADD_INPUT(StartPosition, (0,0,0));

	x = aGenericStreamTracer->GetStartPosition();
	StartPosition.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(MinimumIntegrationStep, (0));
	SO_ENGINE_ADD_INPUT(InitialIntegrationStepUnit, (0));
	InitialIntegrationStepUnit.setValue(aGenericStreamTracer->GetInitialIntegrationStepUnit());

	SO_ENGINE_ADD_INPUT(MaximumPropagation, (0));
	SO_ENGINE_ADD_INPUT(MaximumIntegrationStepUnit, (0));
	MaximumIntegrationStepUnit.setValue(aGenericStreamTracer->GetMaximumIntegrationStepUnit());

	SO_ENGINE_ADD_INPUT(TerminalSpeed, (0));
	TerminalSpeed.setValue(aGenericStreamTracer->GetTerminalSpeed());

	SO_ENGINE_ADD_INPUT(IntegrationDirection, (0));
	IntegrationDirection.setValue(aGenericStreamTracer->GetIntegrationDirection());

	SO_ENGINE_ADD_INPUT(Source, (0));

	SO_ENGINE_ADD_INPUT(RotationScale, (0));
	RotationScale.setValue(aGenericStreamTracer->GetRotationScale());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(IntegratorType, (0));
	SO_ENGINE_ADD_INPUT(MinimumIntegrationStepUnit, (0));
	MinimumIntegrationStepUnit.setValue(aGenericStreamTracer->GetMinimumIntegrationStepUnit());

	SO_ENGINE_ADD_INPUT(ComputeVorticity, (0));
	ComputeVorticity.setValue(aGenericStreamTracer->GetComputeVorticity());

	SO_ENGINE_ADD_INPUT(MaximumError, (0));
	MaximumError.setValue(aGenericStreamTracer->GetMaximumError());

	SO_ENGINE_ADD_INPUT(InitialIntegrationStep, (0));
	SO_ENGINE_ADD_INPUT(Integrator, (0));

	SO_ENGINE_ADD_INPUT(MaximumIntegrationStep, (0));
	SO_ENGINE_ADD_INPUT(MaximumPropagationUnit, (0));
	MaximumPropagationUnit.setValue(aGenericStreamTracer->GetMaximumPropagationUnit());

	aGenericStreamTracer->Delete();

	SO_ENGINE_DEFINE_ENUM_VALUE( Solvers, NONE );
	SO_ENGINE_DEFINE_ENUM_VALUE( Solvers, RUNGE_KUTTA4 );
	SO_ENGINE_DEFINE_ENUM_VALUE( Solvers, RUNGE_KUTTA2 );
	SO_ENGINE_DEFINE_ENUM_VALUE( Solvers, UNKNOWN );
	SO_ENGINE_DEFINE_ENUM_VALUE( Solvers, RUNGE_KUTTA45 );
	SO_ENGINE_SET_SF_ENUM_TYPE( SolversEnum, Solvers );
	SO_ENGINE_DEFINE_ENUM_VALUE( Units, CELL_LENGTH_UNIT );
	SO_ENGINE_DEFINE_ENUM_VALUE( Units, TIME_UNIT );
	SO_ENGINE_DEFINE_ENUM_VALUE( Units, LENGTH_UNIT );
	SO_ENGINE_SET_SF_ENUM_TYPE( UnitsEnum, Units );
	SO_ENGINE_DEFINE_ENUM_VALUE( ReasonForTermination, STAGNATION );
	SO_ENGINE_DEFINE_ENUM_VALUE( ReasonForTermination, UNEXPECTED_VALUE );
	SO_ENGINE_DEFINE_ENUM_VALUE( ReasonForTermination, OUT_OF_TIME );
	SO_ENGINE_DEFINE_ENUM_VALUE( ReasonForTermination, NOT_INITIALIZED );
	SO_ENGINE_DEFINE_ENUM_VALUE( ReasonForTermination, OUT_OF_DOMAIN );
	SO_ENGINE_DEFINE_ENUM_VALUE( ReasonForTermination, OUT_OF_STEPS );
	SO_ENGINE_SET_SF_ENUM_TYPE( ReasonForTerminationEnum, ReasonForTermination );

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( oSource, SoSFVtkObject );
	mSource = 0;


	addCalled = 0;
}

SoVtkGenericStreamTracer::~SoVtkGenericStreamTracer()
{
	// Deletion of the objects if they exist
	if ( mOutput )
	{
	
		mOutput->unref();
		mOutput = 0;
	}
	
	if ( mOutputPort )
	{
	
		mOutputPort->unref();
		mOutputPort = 0;
	}
	
	if ( mSource )
	{
	
		mSource->unref();
		mSource = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkGenericStreamTracer::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkGenericStreamTracer, SoEngine, "Engine" );
}

void SoVtkGenericStreamTracer::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mOutput )
		{
		
			mOutput->unref();
			mOutput = 0;
		}
		
		if ( mOutputPort )
		{
		
			mOutputPort->unref();
			mOutputPort = 0;
		}
		
		if ( mSource )
		{
		
			mSource->unref();
			mSource = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetOutput()->Register(0);
		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject->GetOutput() );

		if ( mObject->GetNumberOfOutputPorts() > 0 )
		{
			mObject->GetOutputPort()->Register(0);
			mOutputPort = new SoVtkAlgorithmOutput();
			mOutputPort->ref();
			mOutputPort->setPointer( mObject->GetOutputPort() );
		}

		mObject->GetSource();
		mSource = new SoVtkObject();
		mSource->ref();
		mSource->setPointer( mObject->GetSource() );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( oSource, SoSFVtkObject, setValue( mSource ) );
}


void SoVtkGenericStreamTracer::inputChanged(SoField * f)
{
	// Get the InterpolatorPrototype value
	if ( f == &InterpolatorPrototype )
		SO_VTK_SET_FIELD_DATA( mObject, InterpolatorPrototype, vtkGenericInterpolatedVelocityField);

	// Get the StartPosition value
	if ( f == &StartPosition )
		SO_VTK_SET_FIELD_VEC3F( mObject, StartPosition);

	// Get the MinimumIntegrationStep value
	if ( f == &MinimumIntegrationStep )
		SO_VTK_SET_FIELD_VALUE( mObject, MinimumIntegrationStep);

	// Get the InitialIntegrationStepUnit value
	if ( f == &InitialIntegrationStepUnit )
		SO_VTK_SET_FIELD_VALUE( mObject, InitialIntegrationStepUnit);

	// Get the MaximumPropagation value
	if ( f == &MaximumPropagation )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumPropagation);

	// Get the MaximumIntegrationStepUnit value
	if ( f == &MaximumIntegrationStepUnit )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumIntegrationStepUnit);

	// Get the TerminalSpeed value
	if ( f == &TerminalSpeed )
		SO_VTK_SET_FIELD_VALUE( mObject, TerminalSpeed);

	// Get the IntegrationDirection value
	if ( f == &IntegrationDirection )
		SO_VTK_SET_FIELD_VALUE( mObject, IntegrationDirection);

	// Get the Source value
	if ( f == &Source )
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkDataSet);

	// Get the RotationScale value
	if ( f == &RotationScale )
		SO_VTK_SET_FIELD_VALUE( mObject, RotationScale);

	// Get the IntegratorType value
	if ( f == &IntegratorType )
		SO_VTK_SET_FIELD_VALUE( mObject, IntegratorType);

	// Get the MinimumIntegrationStepUnit value
	if ( f == &MinimumIntegrationStepUnit )
		SO_VTK_SET_FIELD_VALUE( mObject, MinimumIntegrationStepUnit);

	// Get the ComputeVorticity value
	if ( f == &ComputeVorticity )
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeVorticity);

	// Get the MaximumError value
	if ( f == &MaximumError )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumError);

	// Get the InitialIntegrationStep value
	if ( f == &InitialIntegrationStep )
		SO_VTK_SET_FIELD_VALUE( mObject, InitialIntegrationStep);

	// Get the Integrator value
	if ( f == &Integrator )
		SO_VTK_SET_FIELD_DATA( mObject, Integrator, vtkInitialValueProblemSolver);

	// Get the MaximumIntegrationStep value
	if ( f == &MaximumIntegrationStep )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumIntegrationStep);

	// Get the MaximumPropagationUnit value
	if ( f == &MaximumPropagationUnit )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumPropagationUnit);

	mObject->Update();
}

void SoVtkGenericStreamTracer::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkGenericStreamTracer::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the InterpolatorPrototype value
	
		SO_VTK_SET_FIELD_DATA( mObject, InterpolatorPrototype, vtkGenericInterpolatedVelocityField);

	// Get the StartPosition value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, StartPosition);

	// Get the MinimumIntegrationStep value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MinimumIntegrationStep);

	// Get the InitialIntegrationStepUnit value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InitialIntegrationStepUnit);

	// Get the MaximumPropagation value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumPropagation);

	// Get the MaximumIntegrationStepUnit value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumIntegrationStepUnit);

	// Get the TerminalSpeed value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TerminalSpeed);

	// Get the IntegrationDirection value
	
		SO_VTK_SET_FIELD_VALUE( mObject, IntegrationDirection);

	// Get the Source value
	
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkDataSet);

	// Get the RotationScale value
	
		SO_VTK_SET_FIELD_VALUE( mObject, RotationScale);

	// Get the IntegratorType value
	
		SO_VTK_SET_FIELD_VALUE( mObject, IntegratorType);

	// Get the MinimumIntegrationStepUnit value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MinimumIntegrationStepUnit);

	// Get the ComputeVorticity value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeVorticity);

	// Get the MaximumError value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumError);

	// Get the InitialIntegrationStep value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InitialIntegrationStep);

	// Get the Integrator value
	
		SO_VTK_SET_FIELD_DATA( mObject, Integrator, vtkInitialValueProblemSolver);

	// Get the MaximumIntegrationStep value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumIntegrationStep);

	// Get the MaximumPropagationUnit value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumPropagationUnit);

	mObject->Update();
}
