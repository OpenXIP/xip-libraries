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
 
 
# include "SoVtkCylinderSource.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkCylinderSource )

SoVtkCylinderSource::SoVtkCylinderSource()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkCylinderSource);

	mObject = vtkCylinderSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkCylinderSource *aCylinderSource = vtkCylinderSource::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Resolution, (0));
	Resolution.setValue(aCylinderSource->GetResolution());

	SO_ENGINE_ADD_INPUT(Radius, (0));
	Radius.setValue(aCylinderSource->GetRadius());

	SO_ENGINE_ADD_INPUT(Height, (0));
	Height.setValue(aCylinderSource->GetHeight());

	SO_ENGINE_ADD_INPUT(Capping, (0));
	Capping.setValue(aCylinderSource->GetCapping());

	SO_ENGINE_ADD_INPUT(Center, (0,0,0));

	x = aCylinderSource->GetCenter();
	Center.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aCylinderSource->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkCylinderSource::~SoVtkCylinderSource()
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

void SoVtkCylinderSource::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkCylinderSource, SoEngine, "Engine" );
}

void SoVtkCylinderSource::evaluate()
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


void SoVtkCylinderSource::inputChanged(SoField * f)
{
	// Get the Resolution value
	if ( f == &Resolution )
		SO_VTK_SET_FIELD_VALUE( mObject, Resolution);

	// Get the Radius value
	if ( f == &Radius )
		SO_VTK_SET_FIELD_VALUE( mObject, Radius);

	// Get the Height value
	if ( f == &Height )
		SO_VTK_SET_FIELD_VALUE( mObject, Height);

	// Get the Capping value
	if ( f == &Capping )
		SO_VTK_SET_FIELD_VALUE( mObject, Capping);

	// Get the Center value
	if ( f == &Center )
		SO_VTK_SET_FIELD_VEC3F( mObject, Center);

	mObject->Update();
}

void SoVtkCylinderSource::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkCylinderSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Resolution value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Resolution);

	// Get the Radius value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Radius);

	// Get the Height value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Height);

	// Get the Capping value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Capping);

	// Get the Center value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Center);

	mObject->Update();
}
