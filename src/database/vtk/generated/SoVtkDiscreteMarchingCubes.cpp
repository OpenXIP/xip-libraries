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
 
 
# include "SoVtkDiscreteMarchingCubes.h"
# include "SoVtkUtils.h"

# include "vtkPointLocator.h"
# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkDiscreteMarchingCubes )

SoVtkDiscreteMarchingCubes::SoVtkDiscreteMarchingCubes()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDiscreteMarchingCubes);

	mObject = vtkDiscreteMarchingCubes::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkDiscreteMarchingCubes *aDiscreteMarchingCubes = vtkDiscreteMarchingCubes::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(NumberOfContours, (0));
	NumberOfContours.setValue(aDiscreteMarchingCubes->GetNumberOfContours());

	SO_ENGINE_ADD_INPUT(Value, ());
	Value.setFormat("int double");

	SO_ENGINE_ADD_INPUT(ComputeGradients, (0));
	ComputeGradients.setValue(aDiscreteMarchingCubes->GetComputeGradients());

	SO_ENGINE_ADD_INPUT(Locator, (0));

	SO_ENGINE_ADD_INPUT(ComputeScalars, (0));
	ComputeScalars.setValue(aDiscreteMarchingCubes->GetComputeScalars());

	SO_ENGINE_ADD_INPUT(ComputeNormals, (0));
	ComputeNormals.setValue(aDiscreteMarchingCubes->GetComputeNormals());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aDiscreteMarchingCubes->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oLocator, SoSFVtkObject );
	mLocator = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkDiscreteMarchingCubes::~SoVtkDiscreteMarchingCubes()
{
	// Deletion of the objects if they exist
	if ( mOutput )
	{
	
		mOutput->unref();
		mOutput = 0;
	}
	
	if ( mLocator )
	{
	
		mLocator->unref();
		mLocator = 0;
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

void SoVtkDiscreteMarchingCubes::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDiscreteMarchingCubes, SoEngine, "Engine" );
}

void SoVtkDiscreteMarchingCubes::evaluate()
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
		
		if ( mLocator )
		{
		
			mLocator->unref();
			mLocator = 0;
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

		mObject->GetLocator();
		mLocator = new SoVtkObject();
		mLocator->ref();
		mLocator->setPointer( mObject->GetLocator() );

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
	SO_ENGINE_OUTPUT( oLocator, SoSFVtkObject, setValue( mLocator ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkDiscreteMarchingCubes::inputChanged(SoField * f)
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

	// Get the ComputeGradients value
	if ( f == &ComputeGradients )
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeGradients);

	// Get the Locator value
	if ( f == &Locator )
		SO_VTK_SET_FIELD_DATA( mObject, Locator, vtkPointLocator);

	// Get the ComputeScalars value
	if ( f == &ComputeScalars )
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeScalars);

	// Get the ComputeNormals value
	if ( f == &ComputeNormals )
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeNormals);

	mObject->Update();
}

void SoVtkDiscreteMarchingCubes::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkDiscreteMarchingCubes::New();
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

	// Get the ComputeGradients value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeGradients);

	// Get the Locator value
	
		SO_VTK_SET_FIELD_DATA( mObject, Locator, vtkPointLocator);

	// Get the ComputeScalars value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeScalars);

	// Get the ComputeNormals value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeNormals);

	mObject->Update();
}
