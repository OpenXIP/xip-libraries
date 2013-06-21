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
 
 
# include "SoVtkImageThreshold.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageThreshold )

SoVtkImageThreshold::SoVtkImageThreshold()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageThreshold);

	mObject = vtkImageThreshold::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageThreshold *aImageThreshold = vtkImageThreshold::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(ReplaceIn, (0));
	ReplaceIn.setValue(aImageThreshold->GetReplaceIn());

	SO_ENGINE_ADD_INPUT(ReplaceOut, (0));
	ReplaceOut.setValue(aImageThreshold->GetReplaceOut());

	SO_ENGINE_ADD_INPUT(OutValue, (0));
	SO_ENGINE_ADD_INPUT(InValue, (0));
	SO_ENGINE_ADD_INPUT(OutputScalarType, (0));
	OutputScalarType.setValue(aImageThreshold->GetOutputScalarType());

	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aImageThreshold->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageThreshold->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageThreshold::~SoVtkImageThreshold()
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

void SoVtkImageThreshold::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageThreshold, SoEngine, "Engine" );
}

void SoVtkImageThreshold::evaluate()
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


void SoVtkImageThreshold::inputChanged(SoField * f)
{
	// Get the ReplaceIn value
	if ( f == &ReplaceIn )
		SO_VTK_SET_FIELD_VALUE( mObject, ReplaceIn);

	// Get the ReplaceOut value
	if ( f == &ReplaceOut )
		SO_VTK_SET_FIELD_VALUE( mObject, ReplaceOut);

	// Get the OutValue value
	if ( f == &OutValue )
		SO_VTK_SET_FIELD_VALUE( mObject, OutValue);

	// Get the InValue value
	if ( f == &InValue )
		SO_VTK_SET_FIELD_VALUE( mObject, InValue);

	// Get the OutputScalarType value
	if ( f == &OutputScalarType )
		SO_VTK_SET_FIELD_VALUE( mObject, OutputScalarType);

	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	mObject->Update();
}

void SoVtkImageThreshold::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageThreshold::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the ReplaceIn value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ReplaceIn);

	// Get the ReplaceOut value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ReplaceOut);

	// Get the OutValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, OutValue);

	// Get the InValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InValue);

	// Get the OutputScalarType value
	
		SO_VTK_SET_FIELD_VALUE( mObject, OutputScalarType);

	// Get the NumberOfThreads value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	mObject->Update();
}
