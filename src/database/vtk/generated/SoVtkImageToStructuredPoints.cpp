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
 
 
# include "SoVtkImageToStructuredPoints.h"
# include "SoVtkUtils.h"

# include "vtkImageData.h"
# include "vtkAlgorithmOutput.h"


SO_ENGINE_SOURCE( SoVtkImageToStructuredPoints )

SoVtkImageToStructuredPoints::SoVtkImageToStructuredPoints()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageToStructuredPoints);

	mObject = vtkImageToStructuredPoints::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageToStructuredPoints *aImageToStructuredPoints = vtkImageToStructuredPoints::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(VectorInput, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageToStructuredPoints->Delete();


	SO_ENGINE_ADD_OUTPUT( oVectorInput, SoSFVtkObject );
	mVectorInput = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageToStructuredPoints::~SoVtkImageToStructuredPoints()
{
	// Deletion of the objects if they exist
	if ( mVectorInput )
	{
	
		mVectorInput->unref();
		mVectorInput = 0;
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

void SoVtkImageToStructuredPoints::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageToStructuredPoints, SoEngine, "Engine" );
}

void SoVtkImageToStructuredPoints::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mVectorInput )
		{
		
			mVectorInput->unref();
			mVectorInput = 0;
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

		mObject->GetVectorInput();
		mVectorInput = new SoVtkObject();
		mVectorInput->ref();
		mVectorInput->setPointer( mObject->GetVectorInput() );

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
	SO_ENGINE_OUTPUT( oVectorInput, SoSFVtkObject, setValue( mVectorInput ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkImageToStructuredPoints::inputChanged(SoField * f)
{
	// Get the VectorInput value
	if ( f == &VectorInput )
		SO_VTK_SET_FIELD_DATA( mObject, VectorInput, vtkImageData);

	mObject->Update();
}

void SoVtkImageToStructuredPoints::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageToStructuredPoints::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the VectorInput value
	
		SO_VTK_SET_FIELD_DATA( mObject, VectorInput, vtkImageData);

	mObject->Update();
}
