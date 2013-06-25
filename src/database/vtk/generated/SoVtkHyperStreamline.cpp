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
 
 
# include "SoVtkHyperStreamline.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkHyperStreamline )

SoVtkHyperStreamline::SoVtkHyperStreamline()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkHyperStreamline);

	mObject = vtkHyperStreamline::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkHyperStreamline *aHyperStreamline = vtkHyperStreamline::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(IntegrationEigenvector, (0));
	IntegrationEigenvector.setValue(aHyperStreamline->GetIntegrationEigenvector());

	SO_ENGINE_ADD_INPUT(Radius, (0));
	Radius.setValue(aHyperStreamline->GetRadius());

	SO_ENGINE_ADD_INPUT(StartPosition, ());
	StartPosition.setFormat("double double double");

	SO_ENGINE_ADD_INPUT(IntegrationStepLength, (0));
	IntegrationStepLength.setValue(aHyperStreamline->GetIntegrationStepLength());

	SO_ENGINE_ADD_INPUT(MaximumPropagationDistance, (0));
	MaximumPropagationDistance.setValue(aHyperStreamline->GetMaximumPropagationDistance());

	SO_ENGINE_ADD_INPUT(LogScaling, (0));
	LogScaling.setValue(aHyperStreamline->GetLogScaling());

	SO_ENGINE_ADD_INPUT(IntegrationDirection, (0));
	IntegrationDirection.setValue(aHyperStreamline->GetIntegrationDirection());

	SO_ENGINE_ADD_INPUT(NumberOfSides, (0));
	NumberOfSides.setValue(aHyperStreamline->GetNumberOfSides());

	SO_ENGINE_ADD_INPUT(StepLength, (0));
	StepLength.setValue(aHyperStreamline->GetStepLength());

	SO_ENGINE_ADD_INPUT(TerminalEigenvalue, (0));
	TerminalEigenvalue.setValue(aHyperStreamline->GetTerminalEigenvalue());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(StartLocation, ());
	StartLocation.setFormat("vtkIdType int double double double");

	aHyperStreamline->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkHyperStreamline::~SoVtkHyperStreamline()
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

void SoVtkHyperStreamline::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkHyperStreamline, SoEngine, "Engine" );
}

void SoVtkHyperStreamline::evaluate()
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

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkHyperStreamline::inputChanged(SoField * f)
{
	// Get the IntegrationEigenvector value
	if ( f == &IntegrationEigenvector )
		SO_VTK_SET_FIELD_VALUE( mObject, IntegrationEigenvector);

	// Get the Radius value
	if ( f == &Radius )
		SO_VTK_SET_FIELD_VALUE( mObject, Radius);

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

	// Get the IntegrationStepLength value
	if ( f == &IntegrationStepLength )
		SO_VTK_SET_FIELD_VALUE( mObject, IntegrationStepLength);

	// Get the MaximumPropagationDistance value
	if ( f == &MaximumPropagationDistance )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumPropagationDistance);

	// Get the LogScaling value
	if ( f == &LogScaling )
		SO_VTK_SET_FIELD_VALUE( mObject, LogScaling);

	// Get the IntegrationDirection value
	if ( f == &IntegrationDirection )
		SO_VTK_SET_FIELD_VALUE( mObject, IntegrationDirection);

	// Get the NumberOfSides value
	if ( f == &NumberOfSides )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfSides);

	// Get the StepLength value
	if ( f == &StepLength )
		SO_VTK_SET_FIELD_VALUE( mObject, StepLength);

	// Get the TerminalEigenvalue value
	if ( f == &TerminalEigenvalue )
		SO_VTK_SET_FIELD_VALUE( mObject, TerminalEigenvalue);

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

	mObject->Update();
}

void SoVtkHyperStreamline::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkHyperStreamline::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the IntegrationEigenvector value
	
		SO_VTK_SET_FIELD_VALUE( mObject, IntegrationEigenvector);

	// Get the Radius value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Radius);

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

	// Get the IntegrationStepLength value
	
		SO_VTK_SET_FIELD_VALUE( mObject, IntegrationStepLength);

	// Get the MaximumPropagationDistance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumPropagationDistance);

	// Get the LogScaling value
	
		SO_VTK_SET_FIELD_VALUE( mObject, LogScaling);

	// Get the IntegrationDirection value
	
		SO_VTK_SET_FIELD_VALUE( mObject, IntegrationDirection);

	// Get the NumberOfSides value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfSides);

	// Get the StepLength value
	
		SO_VTK_SET_FIELD_VALUE( mObject, StepLength);

	// Get the TerminalEigenvalue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TerminalEigenvalue);

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

	mObject->Update();
}
