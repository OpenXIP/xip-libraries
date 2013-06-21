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
 
 
 
# include "SoVtkAppendPolyData.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkAppendPolyData )

SoVtkAppendPolyData::SoVtkAppendPolyData()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkAppendPolyData);

	mObject = vtkAppendPolyData::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkAppendPolyData *aAppendPolyData = vtkAppendPolyData::New();

	SO_ENGINE_ADD_INPUT(UserManagedInputs, (0));
	UserManagedInputs.setValue(aAppendPolyData->GetUserManagedInputs());

	SO_ENGINE_ADD_INPUT(ParallelStreaming, (0));
	ParallelStreaming.setValue(aAppendPolyData->GetParallelStreaming());

	SO_ENGINE_ADD_INPUT(NumberOfInputs, (0));
	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aAppendPolyData->Delete();

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

	addCalled = 0;
}

SoVtkAppendPolyData::~SoVtkAppendPolyData()
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

void SoVtkAppendPolyData::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkAppendPolyData, SoEngine, "Engine" );
}

void SoVtkAppendPolyData::evaluate()
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


void SoVtkAppendPolyData::inputChanged(SoField * f)
{
	// Get the UserManagedInputs value
	if ( f == &UserManagedInputs )
		SO_VTK_SET_FIELD_VALUE( mObject, UserManagedInputs);

	// Get the ParallelStreaming value
	if ( f == &ParallelStreaming )
		SO_VTK_SET_FIELD_VALUE( mObject, ParallelStreaming);

	// Get the NumberOfInputs value
	if ( f == &NumberOfInputs )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfInputs);

	mObject->Update();
}

void SoVtkAppendPolyData::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkAppendPolyData::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the UserManagedInputs value
	
		SO_VTK_SET_FIELD_VALUE( mObject, UserManagedInputs);

	// Get the ParallelStreaming value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ParallelStreaming);

	// Get the NumberOfInputs value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfInputs);

	mObject->Update();
}

