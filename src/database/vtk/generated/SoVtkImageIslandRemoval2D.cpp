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
 
 
# include "SoVtkImageIslandRemoval2D.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageIslandRemoval2D )

SoVtkImageIslandRemoval2D::SoVtkImageIslandRemoval2D()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageIslandRemoval2D);

	mObject = vtkImageIslandRemoval2D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageIslandRemoval2D *aImageIslandRemoval2D = vtkImageIslandRemoval2D::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(SquareNeighborhood, (0));
	SquareNeighborhood.setValue(aImageIslandRemoval2D->GetSquareNeighborhood());

	SO_ENGINE_ADD_INPUT(IslandValue, (0));
	IslandValue.setValue(aImageIslandRemoval2D->GetIslandValue());

	SO_ENGINE_ADD_INPUT(ReplaceValue, (0));
	ReplaceValue.setValue(aImageIslandRemoval2D->GetReplaceValue());

	SO_ENGINE_ADD_INPUT(AreaThreshold, (0));
	AreaThreshold.setValue(aImageIslandRemoval2D->GetAreaThreshold());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageIslandRemoval2D->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageIslandRemoval2D::~SoVtkImageIslandRemoval2D()
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

void SoVtkImageIslandRemoval2D::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageIslandRemoval2D, SoEngine, "Engine" );
}

void SoVtkImageIslandRemoval2D::evaluate()
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


void SoVtkImageIslandRemoval2D::inputChanged(SoField * f)
{
	// Get the SquareNeighborhood value
	if ( f == &SquareNeighborhood )
		SO_VTK_SET_FIELD_VALUE( mObject, SquareNeighborhood);

	// Get the IslandValue value
	if ( f == &IslandValue )
		SO_VTK_SET_FIELD_VALUE( mObject, IslandValue);

	// Get the ReplaceValue value
	if ( f == &ReplaceValue )
		SO_VTK_SET_FIELD_VALUE( mObject, ReplaceValue);

	// Get the AreaThreshold value
	if ( f == &AreaThreshold )
		SO_VTK_SET_FIELD_VALUE( mObject, AreaThreshold);

	mObject->Update();
}

void SoVtkImageIslandRemoval2D::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageIslandRemoval2D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the SquareNeighborhood value
	
		SO_VTK_SET_FIELD_VALUE( mObject, SquareNeighborhood);

	// Get the IslandValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, IslandValue);

	// Get the ReplaceValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ReplaceValue);

	// Get the AreaThreshold value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AreaThreshold);

	mObject->Update();
}
