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
 
 
# include "SoVtkDuplicatePolyData.h"
# include "SoVtkUtils.h"

# include "vtkMultiProcessController.h"
# include "vtkSocketController.h"
# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkDuplicatePolyData )

SoVtkDuplicatePolyData::SoVtkDuplicatePolyData()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDuplicatePolyData);

	mObject = vtkDuplicatePolyData::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkDuplicatePolyData *aDuplicatePolyData = vtkDuplicatePolyData::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Synchronous, (0));
	Synchronous.setValue(aDuplicatePolyData->GetSynchronous());

	SO_ENGINE_ADD_INPUT(Controller, (0));

	SO_ENGINE_ADD_INPUT(SocketController, (0));

	SO_ENGINE_ADD_INPUT(ClientFlag, (0));
	ClientFlag.setValue(aDuplicatePolyData->GetClientFlag());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aDuplicatePolyData->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkDuplicatePolyData::~SoVtkDuplicatePolyData()
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

void SoVtkDuplicatePolyData::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDuplicatePolyData, SoEngine, "Engine" );
}

void SoVtkDuplicatePolyData::evaluate()
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


void SoVtkDuplicatePolyData::inputChanged(SoField * f)
{
	// Get the Synchronous value
	if ( f == &Synchronous )
		SO_VTK_SET_FIELD_VALUE( mObject, Synchronous);

	// Get the Controller value
	if ( f == &Controller )
		SO_VTK_SET_FIELD_DATA( mObject, Controller, vtkMultiProcessController);

	// Get the SocketController value
	if ( f == &SocketController )
		SO_VTK_SET_FIELD_DATA( mObject, SocketController, vtkSocketController);

	// Get the ClientFlag value
	if ( f == &ClientFlag )
		SO_VTK_SET_FIELD_VALUE( mObject, ClientFlag);

	mObject->Update();
}

void SoVtkDuplicatePolyData::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkDuplicatePolyData::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Synchronous value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Synchronous);

	// Get the Controller value
	
		SO_VTK_SET_FIELD_DATA( mObject, Controller, vtkMultiProcessController);

	// Get the SocketController value
	
		SO_VTK_SET_FIELD_DATA( mObject, SocketController, vtkSocketController);

	// Get the ClientFlag value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ClientFlag);

	mObject->Update();
}
