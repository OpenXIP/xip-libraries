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
 
 
# include "SoVtkImageQuantizeRGBToIndex.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageQuantizeRGBToIndex )

SoVtkImageQuantizeRGBToIndex::SoVtkImageQuantizeRGBToIndex()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageQuantizeRGBToIndex);

	mObject = vtkImageQuantizeRGBToIndex::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageQuantizeRGBToIndex *aImageQuantizeRGBToIndex = vtkImageQuantizeRGBToIndex::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(InitializeExecuteTime, (0));
	InitializeExecuteTime.setValue(aImageQuantizeRGBToIndex->GetInitializeExecuteTime());

	SO_ENGINE_ADD_INPUT(NumberOfColors, (0));
	NumberOfColors.setValue(aImageQuantizeRGBToIndex->GetNumberOfColors());

	SO_ENGINE_ADD_INPUT(LookupIndexExecuteTime, (0));
	LookupIndexExecuteTime.setValue(aImageQuantizeRGBToIndex->GetLookupIndexExecuteTime());

	SO_ENGINE_ADD_INPUT(BuildTreeExecuteTime, (0));
	BuildTreeExecuteTime.setValue(aImageQuantizeRGBToIndex->GetBuildTreeExecuteTime());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageQuantizeRGBToIndex->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageQuantizeRGBToIndex::~SoVtkImageQuantizeRGBToIndex()
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

void SoVtkImageQuantizeRGBToIndex::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageQuantizeRGBToIndex, SoEngine, "Engine" );
}

void SoVtkImageQuantizeRGBToIndex::evaluate()
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


void SoVtkImageQuantizeRGBToIndex::inputChanged(SoField * f)
{
	// Get the InitializeExecuteTime value
	if ( f == &InitializeExecuteTime )
		SO_VTK_SET_FIELD_VALUE( mObject, InitializeExecuteTime);

	// Get the NumberOfColors value
	if ( f == &NumberOfColors )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfColors);

	// Get the LookupIndexExecuteTime value
	if ( f == &LookupIndexExecuteTime )
		SO_VTK_SET_FIELD_VALUE( mObject, LookupIndexExecuteTime);

	// Get the BuildTreeExecuteTime value
	if ( f == &BuildTreeExecuteTime )
		SO_VTK_SET_FIELD_VALUE( mObject, BuildTreeExecuteTime);

	mObject->Update();
}

void SoVtkImageQuantizeRGBToIndex::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageQuantizeRGBToIndex::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the InitializeExecuteTime value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InitializeExecuteTime);

	// Get the NumberOfColors value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfColors);

	// Get the LookupIndexExecuteTime value
	
		SO_VTK_SET_FIELD_VALUE( mObject, LookupIndexExecuteTime);

	// Get the BuildTreeExecuteTime value
	
		SO_VTK_SET_FIELD_VALUE( mObject, BuildTreeExecuteTime);

	mObject->Update();
}
