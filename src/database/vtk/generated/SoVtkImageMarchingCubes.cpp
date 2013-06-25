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
 
 
# include "SoVtkImageMarchingCubes.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkImageMarchingCubes )

SoVtkImageMarchingCubes::SoVtkImageMarchingCubes()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageMarchingCubes);

	mObject = vtkImageMarchingCubes::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageMarchingCubes *aImageMarchingCubes = vtkImageMarchingCubes::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(NumberOfContours, (0));
	NumberOfContours.setValue(aImageMarchingCubes->GetNumberOfContours());

	SO_ENGINE_ADD_INPUT(Value, ());
	Value.setFormat("int double");

	SO_ENGINE_ADD_INPUT(LocatorPoint, ());
	LocatorPoint.setFormat("int int int int");

	SO_ENGINE_ADD_INPUT(ComputeScalars, (0));
	ComputeScalars.setValue(aImageMarchingCubes->GetComputeScalars());

	SO_ENGINE_ADD_INPUT(ComputeGradients, (0));
	ComputeGradients.setValue(aImageMarchingCubes->GetComputeGradients());

	SO_ENGINE_ADD_INPUT(ComputeNormals, (0));
	ComputeNormals.setValue(aImageMarchingCubes->GetComputeNormals());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(InputMemoryLimit, (0));
	InputMemoryLimit.setValue(aImageMarchingCubes->GetInputMemoryLimit());

	aImageMarchingCubes->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageMarchingCubes::~SoVtkImageMarchingCubes()
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

void SoVtkImageMarchingCubes::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageMarchingCubes, SoEngine, "Engine" );
}

void SoVtkImageMarchingCubes::evaluate()
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


void SoVtkImageMarchingCubes::inputChanged(SoField * f)
{
	// Get the NumberOfContours value
	if ( f == &NumberOfContours )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfContours);

	// Get the Value value
	if ( f == &Value )
	{
		SbVariant *vValue = (SbVariant *)Value.getValues(0);
		SoInput input;
		int nb_fields = Value.getNum();

		int val0;
		double val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vValue[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetValue( 
				(int) val0,
				(double) val1
			);
		}
	}

	// Get the LocatorPoint value
	if ( f == &LocatorPoint )
		addCalled = 1;

	// Get the ComputeScalars value
	if ( f == &ComputeScalars )
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeScalars);

	// Get the ComputeGradients value
	if ( f == &ComputeGradients )
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeGradients);

	// Get the ComputeNormals value
	if ( f == &ComputeNormals )
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeNormals);

	// Get the InputMemoryLimit value
	if ( f == &InputMemoryLimit )
		SO_VTK_SET_FIELD_VALUE( mObject, InputMemoryLimit);

	mObject->Update();
}

void SoVtkImageMarchingCubes::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageMarchingCubes::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the NumberOfContours value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfContours);

	// Get the Value value
	if (addCalled == 1)
	{
		SbVariant *vValue = (SbVariant *)Value.getValues(0);
		SoInput input;
		int nb_fields = Value.getNum();

		int val0;
		double val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vValue[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetValue( 
				(int) val0,
				(double) val1
			);
		}
	}

	// Get the LocatorPoint value
	if (addCalled == 1)
	{
		SbVariant *vLocatorPoint = (SbVariant *)LocatorPoint.getValues(0);
		SoInput input;
		int nb_fields = LocatorPoint.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vLocatorPoint[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			mObject->AddLocatorPoint( 
				(int) val0,
				(int) val1,
				(int) val2,
				(int) val3
			);
		}
	}

	// Get the ComputeScalars value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeScalars);

	// Get the ComputeGradients value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeGradients);

	// Get the ComputeNormals value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeNormals);

	// Get the InputMemoryLimit value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InputMemoryLimit);

	mObject->Update();
}
