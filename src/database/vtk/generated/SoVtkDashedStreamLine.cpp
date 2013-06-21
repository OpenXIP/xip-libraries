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
 
 
# include "SoVtkDashedStreamLine.h"
# include "SoVtkUtils.h"

# include "vtkDataSet.h"
# include "vtkAlgorithmOutput.h"
# include "vtkInitialValueProblemSolver.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkDashedStreamLine )

SoVtkDashedStreamLine::SoVtkDashedStreamLine()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDashedStreamLine);

	mObject = vtkDashedStreamLine::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkDashedStreamLine *aDashedStreamLine = vtkDashedStreamLine::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(StartPosition, ());
	StartPosition.setFormat("double double double");

	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aDashedStreamLine->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(IntegrationStepLength, (0));
	IntegrationStepLength.setValue(aDashedStreamLine->GetIntegrationStepLength());

	SO_ENGINE_ADD_INPUT(MaximumPropagationTime, (0));
	MaximumPropagationTime.setValue(aDashedStreamLine->GetMaximumPropagationTime());

	SO_ENGINE_ADD_INPUT(DashFactor, (0));
	DashFactor.setValue(aDashedStreamLine->GetDashFactor());

	SO_ENGINE_ADD_INPUT(TerminalSpeed, (0));
	TerminalSpeed.setValue(aDashedStreamLine->GetTerminalSpeed());

	SO_ENGINE_ADD_INPUT(Source, (0));

	SO_ENGINE_ADD_INPUT(IntegrationDirection, (0));
	IntegrationDirection.setValue(aDashedStreamLine->GetIntegrationDirection());

	SO_ENGINE_ADD_INPUT(StepLength, (0));
	StepLength.setValue(aDashedStreamLine->GetStepLength());

	SO_ENGINE_ADD_INPUT(StartLocation, ());
	StartLocation.setFormat("vtkIdType int double double double");

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(OrientationScalars, (0));
	OrientationScalars.setValue(aDashedStreamLine->GetOrientationScalars());

	SO_ENGINE_ADD_INPUT(SpeedScalars, (0));
	SpeedScalars.setValue(aDashedStreamLine->GetSpeedScalars());

	SO_ENGINE_ADD_INPUT(Vorticity, (0));
	Vorticity.setValue(aDashedStreamLine->GetVorticity());

	SO_ENGINE_ADD_INPUT(Integrator, (0));

	SO_ENGINE_ADD_INPUT(SavePointInterval, (0));
	SavePointInterval.setValue(aDashedStreamLine->GetSavePointInterval());

	aDashedStreamLine->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( oSource, SoSFVtkObject );
	mSource = 0;


	addCalled = 0;
}

SoVtkDashedStreamLine::~SoVtkDashedStreamLine()
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

void SoVtkDashedStreamLine::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDashedStreamLine, SoEngine, "Engine" );
}

void SoVtkDashedStreamLine::evaluate()
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


void SoVtkDashedStreamLine::inputChanged(SoField * f)
{
	// Get the StartPosition value
	if ( f == &StartPosition )
	{
		SbVariant *vStartPosition = (SbVariant *)StartPosition.getValues(0);
		SoInput input;
		int nb_fields = StartPosition.getNum();

		double val0;
		double val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vStartPosition[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetStartPosition( 
				(double) val0,
				(double) val1,
				(double) val2
			);
		}
	}

	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the IntegrationStepLength value
	if ( f == &IntegrationStepLength )
		SO_VTK_SET_FIELD_VALUE( mObject, IntegrationStepLength);

	// Get the MaximumPropagationTime value
	if ( f == &MaximumPropagationTime )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumPropagationTime);

	// Get the DashFactor value
	if ( f == &DashFactor )
		SO_VTK_SET_FIELD_VALUE( mObject, DashFactor);

	// Get the TerminalSpeed value
	if ( f == &TerminalSpeed )
		SO_VTK_SET_FIELD_VALUE( mObject, TerminalSpeed);

	// Get the Source value
	if ( f == &Source )
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkDataSet);

	// Get the IntegrationDirection value
	if ( f == &IntegrationDirection )
		SO_VTK_SET_FIELD_VALUE( mObject, IntegrationDirection);

	// Get the StepLength value
	if ( f == &StepLength )
		SO_VTK_SET_FIELD_VALUE( mObject, StepLength);

	// Get the StartLocation value
	if ( f == &StartLocation )
	{
		SbVariant *vStartLocation = (SbVariant *)StartLocation.getValues(0);
		SoInput input;
		int nb_fields = StartLocation.getNum();

		vtkIdType val0;
		int val1;
		double val2;
		double val3;
		double val4;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vStartLocation[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			mObject->SetStartLocation( 
				(vtkIdType) val0,
				(int) val1,
				(double) val2,
				(double) val3,
				(double) val4
			);
		}
	}

	// Get the OrientationScalars value
	if ( f == &OrientationScalars )
		SO_VTK_SET_FIELD_VALUE( mObject, OrientationScalars);

	// Get the SpeedScalars value
	if ( f == &SpeedScalars )
		SO_VTK_SET_FIELD_VALUE( mObject, SpeedScalars);

	// Get the Vorticity value
	if ( f == &Vorticity )
		SO_VTK_SET_FIELD_VALUE( mObject, Vorticity);

	// Get the Integrator value
	if ( f == &Integrator )
		SO_VTK_SET_FIELD_DATA( mObject, Integrator, vtkInitialValueProblemSolver);

	// Get the SavePointInterval value
	if ( f == &SavePointInterval )
		SO_VTK_SET_FIELD_VALUE( mObject, SavePointInterval);

	mObject->Update();
}

void SoVtkDashedStreamLine::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkDashedStreamLine::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the StartPosition value
	if (addCalled == 1)
	{
		SbVariant *vStartPosition = (SbVariant *)StartPosition.getValues(0);
		SoInput input;
		int nb_fields = StartPosition.getNum();

		double val0;
		double val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vStartPosition[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetStartPosition( 
				(double) val0,
				(double) val1,
				(double) val2
			);
		}
	}

	// Get the NumberOfThreads value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the IntegrationStepLength value
	
		SO_VTK_SET_FIELD_VALUE( mObject, IntegrationStepLength);

	// Get the MaximumPropagationTime value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumPropagationTime);

	// Get the DashFactor value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DashFactor);

	// Get the TerminalSpeed value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TerminalSpeed);

	// Get the Source value
	
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkDataSet);

	// Get the IntegrationDirection value
	
		SO_VTK_SET_FIELD_VALUE( mObject, IntegrationDirection);

	// Get the StepLength value
	
		SO_VTK_SET_FIELD_VALUE( mObject, StepLength);

	// Get the StartLocation value
	if (addCalled == 1)
	{
		SbVariant *vStartLocation = (SbVariant *)StartLocation.getValues(0);
		SoInput input;
		int nb_fields = StartLocation.getNum();

		vtkIdType val0;
		int val1;
		double val2;
		double val3;
		double val4;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vStartLocation[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			mObject->SetStartLocation( 
				(vtkIdType) val0,
				(int) val1,
				(double) val2,
				(double) val3,
				(double) val4
			);
		}
	}

	// Get the OrientationScalars value
	
		SO_VTK_SET_FIELD_VALUE( mObject, OrientationScalars);

	// Get the SpeedScalars value
	
		SO_VTK_SET_FIELD_VALUE( mObject, SpeedScalars);

	// Get the Vorticity value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Vorticity);

	// Get the Integrator value
	
		SO_VTK_SET_FIELD_DATA( mObject, Integrator, vtkInitialValueProblemSolver);

	// Get the SavePointInterval value
	
		SO_VTK_SET_FIELD_VALUE( mObject, SavePointInterval);

	mObject->Update();
}
