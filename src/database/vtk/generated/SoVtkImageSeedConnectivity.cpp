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
 
 
# include "SoVtkImageSeedConnectivity.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageConnector.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageSeedConnectivity )

SoVtkImageSeedConnectivity::SoVtkImageSeedConnectivity()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageSeedConnectivity);

	mObject = vtkImageSeedConnectivity::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageSeedConnectivity *aImageSeedConnectivity = vtkImageSeedConnectivity::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Dimensionality, (0));
	Dimensionality.setValue(aImageSeedConnectivity->GetDimensionality());

	SO_ENGINE_ADD_INPUT(Seed, ());
	Seed.setFormat("int int int");

	SO_ENGINE_ADD_INPUT(InputConnectValue, (0));
	InputConnectValue.setValue(aImageSeedConnectivity->GetInputConnectValue());

	SO_ENGINE_ADD_INPUT(OutputConnectedValue, (0));
	OutputConnectedValue.setValue(aImageSeedConnectivity->GetOutputConnectedValue());

	SO_ENGINE_ADD_INPUT(OutputUnconnectedValue, (0));
	OutputUnconnectedValue.setValue(aImageSeedConnectivity->GetOutputUnconnectedValue());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageSeedConnectivity->Delete();


	SO_ENGINE_ADD_OUTPUT( oConnector, SoSFVtkObject );
	mConnector = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageSeedConnectivity::~SoVtkImageSeedConnectivity()
{
	// Deletion of the objects if they exist
	if ( mConnector )
	{
	
		mConnector->unref();
		mConnector = 0;
	}
	
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

void SoVtkImageSeedConnectivity::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageSeedConnectivity, SoEngine, "Engine" );
}

void SoVtkImageSeedConnectivity::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mConnector )
		{
		
			mConnector->unref();
			mConnector = 0;
		}
		
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

		mObject->GetConnector();
		mConnector = new SoVtkObject();
		mConnector->ref();
		mConnector->setPointer( mObject->GetConnector() );

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
	SO_ENGINE_OUTPUT( oConnector, SoSFVtkObject, setValue( mConnector ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkImageSeedConnectivity::inputChanged(SoField * f)
{
	// Get the Dimensionality value
	if ( f == &Dimensionality )
		SO_VTK_SET_FIELD_VALUE( mObject, Dimensionality);

	// Get the Seed value
	if ( f == &Seed )
		addCalled = 1;

	// Get the InputConnectValue value
	if ( f == &InputConnectValue )
		SO_VTK_SET_FIELD_VALUE( mObject, InputConnectValue);

	// Get the OutputConnectedValue value
	if ( f == &OutputConnectedValue )
		SO_VTK_SET_FIELD_VALUE( mObject, OutputConnectedValue);

	// Get the OutputUnconnectedValue value
	if ( f == &OutputUnconnectedValue )
		SO_VTK_SET_FIELD_VALUE( mObject, OutputUnconnectedValue);

	mObject->Update();
}

void SoVtkImageSeedConnectivity::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageSeedConnectivity::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Dimensionality value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Dimensionality);

	// Get the Seed value
	if (addCalled == 1)
	{
		SbVariant *vSeed = (SbVariant *)Seed.getValues(0);
		SoInput input;
		int nb_fields = Seed.getNum();

		int val0;
		int val1;
		int val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vSeed[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->AddSeed( 
				(int) val0,
				(int) val1,
				(int) val2
			);
		}
	}

	// Get the InputConnectValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InputConnectValue);

	// Get the OutputConnectedValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, OutputConnectedValue);

	// Get the OutputUnconnectedValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, OutputUnconnectedValue);

	mObject->Update();
}
