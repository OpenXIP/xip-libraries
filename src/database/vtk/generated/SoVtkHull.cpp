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
 
 
# include "SoVtkHull.h"
# include "SoVtkUtils.h"

# include "vtkPlanes.h"
# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkHull )

SoVtkHull::SoVtkHull()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkHull);

	mObject = vtkHull::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkHull *aHull = vtkHull::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Planes, (0));

	SO_ENGINE_ADD_INPUT(Plane, ());
	Plane.setFormat("double double double");

	SO_ENGINE_ADD_INPUT(RecursiveSpherePlanes, (0));
	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aHull->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkHull::~SoVtkHull()
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

void SoVtkHull::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkHull, SoEngine, "Engine" );
}

void SoVtkHull::evaluate()
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


void SoVtkHull::inputChanged(SoField * f)
{
	// Get the Planes value
	if ( f == &Planes )
		SO_VTK_SET_FIELD_DATA( mObject, Planes, vtkPlanes);

	// Get the Plane value
	if ( f == &Plane )
		addCalled = 1;

	// Get the RecursiveSpherePlanes value
	if ( f == &RecursiveSpherePlanes )
		addCalled = 1;
	mObject->Update();
}

void SoVtkHull::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkHull::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Planes value
	
		SO_VTK_SET_FIELD_DATA( mObject, Planes, vtkPlanes);

	// Get the Plane value
	if (addCalled == 1)
	{
		SbVariant *vPlane = (SbVariant *)Plane.getValues(0);
		SoInput input;
		int nb_fields = Plane.getNum();

		double val0;
		double val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vPlane[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->AddPlane( 
				(double) val0,
				(double) val1,
				(double) val2
			);
		}
	}

	// Get the RecursiveSpherePlanes value
	
		SO_VTK_ADD_FIELD_VALUE( mObject, RecursiveSpherePlanes);

	mObject->Update();
}
