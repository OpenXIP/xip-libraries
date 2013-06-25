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
 
 
# include "SoVtkCurvatures.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkCurvatures )

SoVtkCurvatures::SoVtkCurvatures()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkCurvatures);

	mObject = vtkCurvatures::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkCurvatures *aCurvatures = vtkCurvatures::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(CurvatureType, (0));
	CurvatureType.setValue(aCurvatures->GetCurvatureType());

	SO_ENGINE_ADD_INPUT(InvertMeanCurvature, (0));
	InvertMeanCurvature.setValue(aCurvatures->GetInvertMeanCurvature());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aCurvatures->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkCurvatures::~SoVtkCurvatures()
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

void SoVtkCurvatures::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkCurvatures, SoEngine, "Engine" );
}

void SoVtkCurvatures::evaluate()
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


void SoVtkCurvatures::inputChanged(SoField * f)
{
	// Get the CurvatureType value
	if ( f == &CurvatureType )
		SO_VTK_SET_FIELD_VALUE( mObject, CurvatureType);

	// Get the InvertMeanCurvature value
	if ( f == &InvertMeanCurvature )
		SO_VTK_SET_FIELD_VALUE( mObject, InvertMeanCurvature);

	mObject->Update();
}

void SoVtkCurvatures::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkCurvatures::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the CurvatureType value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CurvatureType);

	// Get the InvertMeanCurvature value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InvertMeanCurvature);

	mObject->Update();
}
