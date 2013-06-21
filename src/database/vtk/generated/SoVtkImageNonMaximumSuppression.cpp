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
 
 
# include "SoVtkImageNonMaximumSuppression.h"
# include "SoVtkUtils.h"

# include "vtkImageData.h"
# include "vtkAlgorithmOutput.h"


SO_ENGINE_SOURCE( SoVtkImageNonMaximumSuppression )

SoVtkImageNonMaximumSuppression::SoVtkImageNonMaximumSuppression()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageNonMaximumSuppression);

	mObject = vtkImageNonMaximumSuppression::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageNonMaximumSuppression *aImageNonMaximumSuppression = vtkImageNonMaximumSuppression::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Dimensionality, (0));
	Dimensionality.setValue(aImageNonMaximumSuppression->GetDimensionality());

	SO_ENGINE_ADD_INPUT(HandleBoundaries, (0));
	HandleBoundaries.setValue(aImageNonMaximumSuppression->GetHandleBoundaries());

	SO_ENGINE_ADD_INPUT(VectorInput, (0));

	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aImageNonMaximumSuppression->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(MagnitudeInput, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageNonMaximumSuppression->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageNonMaximumSuppression::~SoVtkImageNonMaximumSuppression()
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

void SoVtkImageNonMaximumSuppression::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageNonMaximumSuppression, SoEngine, "Engine" );
}

void SoVtkImageNonMaximumSuppression::evaluate()
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


void SoVtkImageNonMaximumSuppression::inputChanged(SoField * f)
{
	// Get the Dimensionality value
	if ( f == &Dimensionality )
		SO_VTK_SET_FIELD_VALUE( mObject, Dimensionality);

	// Get the HandleBoundaries value
	if ( f == &HandleBoundaries )
		SO_VTK_SET_FIELD_VALUE( mObject, HandleBoundaries);

	// Get the VectorInput value
	if ( f == &VectorInput )
		SO_VTK_SET_FIELD_DATA( mObject, VectorInput, vtkImageData);

	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the MagnitudeInput value
	if ( f == &MagnitudeInput )
		SO_VTK_SET_FIELD_DATA( mObject, MagnitudeInput, vtkImageData);

	mObject->Update();
}

void SoVtkImageNonMaximumSuppression::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageNonMaximumSuppression::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Dimensionality value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Dimensionality);

	// Get the HandleBoundaries value
	
		SO_VTK_SET_FIELD_VALUE( mObject, HandleBoundaries);

	// Get the VectorInput value
	
		SO_VTK_SET_FIELD_DATA( mObject, VectorInput, vtkImageData);

	// Get the NumberOfThreads value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the MagnitudeInput value
	
		SO_VTK_SET_FIELD_DATA( mObject, MagnitudeInput, vtkImageData);

	mObject->Update();
}
