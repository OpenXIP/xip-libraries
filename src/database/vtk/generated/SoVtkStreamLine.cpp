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

# include "SoVtkStreamLine.h"
# include "SoVtkUtils.h"

# include "vtkDataSet.h"
# include "vtkDataObject.h"
# include "vtkAlgorithmOutput.h"
# include "vtkInitialValueProblemSolver.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkStreamLine )

SoVtkStreamLine::SoVtkStreamLine()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkStreamLine);

	mObject = vtkStreamLine::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkStreamLine *aStreamLine = vtkStreamLine::New();

	SO_ENGINE_ADD_INPUT(StartPosition, ());
	StartPosition.setFormat("double double double");

	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aStreamLine->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(IntegrationStepLength, (0));
	IntegrationStepLength.setValue(aStreamLine->GetIntegrationStepLength());

	SO_ENGINE_ADD_INPUT(MaximumPropagationTime, (0));
	MaximumPropagationTime.setValue(aStreamLine->GetMaximumPropagationTime());

	SO_ENGINE_ADD_INPUT(Source, (0));

	SO_ENGINE_ADD_INPUT(IntegrationDirection, (0));
	IntegrationDirection.setValue(aStreamLine->GetIntegrationDirection());

	SO_ENGINE_ADD_INPUT(TerminalSpeed, (0));
	TerminalSpeed.setValue(aStreamLine->GetTerminalSpeed());

	SO_ENGINE_ADD_INPUT(InputArrayToProcess, ());
	InputArrayToProcess.setFormat("int int int int char*");

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(StepLength, (0));
	StepLength.setValue(aStreamLine->GetStepLength());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(OrientationScalars, (0));
	OrientationScalars.setValue(aStreamLine->GetOrientationScalars());

	SO_ENGINE_ADD_INPUT(SpeedScalars, (0));
	SpeedScalars.setValue(aStreamLine->GetSpeedScalars());

	SO_ENGINE_ADD_INPUT(Vorticity, (0));
	Vorticity.setValue(aStreamLine->GetVorticity());

	SO_ENGINE_ADD_INPUT(Integrator, (0));

	SO_ENGINE_ADD_INPUT(SavePointInterval, (0));
	SavePointInterval.setValue(aStreamLine->GetSavePointInterval());

	aStreamLine->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

}

SoVtkStreamLine::~SoVtkStreamLine()
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
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkStreamLine::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkStreamLine, SoEngine, "Engine" );
}

void SoVtkStreamLine::evaluate()
{
	try
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
		
		// Get the input type(s)
		SoVtkObject *inputPtr = Input.getValue();
		
		if (inputPtr && inputPtr->getPointer()->IsA("vtkDataObject"))
			mObject->SetInput(vtkDataObject::SafeDownCast(inputPtr->getPointer()));

		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

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

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkStreamLine::inputChanged(SoField * f)
{
	// Get the StartPosition value
	if ( f == &StartPosition )
	{
		SbVariant vStartPosition = (SbVariant)StartPosition.getValue();
		SoInput input;
		double val0;
		double val1;
		double val2;
	
		input.setBuffer((void *)vStartPosition.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		input.read(val2);
		mObject->SetStartPosition( 
			(double) val0,
			(double) val1,
			(double) val2
		);
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

	// Get the Source value
	if ( f == &Source )
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkDataSet);

	// Get the IntegrationDirection value
	if ( f == &IntegrationDirection )
		SO_VTK_SET_FIELD_VALUE( mObject, IntegrationDirection);

	// Get the TerminalSpeed value
	if ( f == &TerminalSpeed )
		SO_VTK_SET_FIELD_VALUE( mObject, TerminalSpeed);

	// Get the InputArrayToProcess value
	if ( f == &InputArrayToProcess )
	{
		SbVariant vInputArrayToProcess = (SbVariant)InputArrayToProcess.getValue();
		SoInput input;
		int val0;
		int val1;
		int val2;
		int val3;
		SbString val4;
	
		input.setBuffer((void *)vInputArrayToProcess.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		input.read(val2);
		input.read(val3);
		input.read(val4);
		mObject->SetInputArrayToProcess( 
			(int) val0,
			(int) val1,
			(int) val2,
			(int) val3,
			val4.getString()
		);
	}
	// Get the StepLength value
	if ( f == &StepLength )
		SO_VTK_SET_FIELD_VALUE( mObject, StepLength);

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

	//mObject->Update();
	
}

