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
 
 
# include "SoVtkGreedyTerrainDecimation.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkGreedyTerrainDecimation )

SoVtkGreedyTerrainDecimation::SoVtkGreedyTerrainDecimation()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkGreedyTerrainDecimation);

	mObject = vtkGreedyTerrainDecimation::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkGreedyTerrainDecimation *aGreedyTerrainDecimation = vtkGreedyTerrainDecimation::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(AbsoluteError, (0));
	AbsoluteError.setValue(aGreedyTerrainDecimation->GetAbsoluteError());

	SO_ENGINE_ADD_INPUT(ErrorMeasure, (0));
	ErrorMeasure.setValue(aGreedyTerrainDecimation->GetErrorMeasure());

	SO_ENGINE_ADD_INPUT(RelativeError, (0));
	RelativeError.setValue(aGreedyTerrainDecimation->GetRelativeError());

	SO_ENGINE_ADD_INPUT(Reduction, (0));
	Reduction.setValue(aGreedyTerrainDecimation->GetReduction());

	SO_ENGINE_ADD_INPUT(BoundaryVertexDeletion, (0));
	BoundaryVertexDeletion.setValue(aGreedyTerrainDecimation->GetBoundaryVertexDeletion());

	SO_ENGINE_ADD_INPUT(ComputeNormals, (0));
	ComputeNormals.setValue(aGreedyTerrainDecimation->GetComputeNormals());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aGreedyTerrainDecimation->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkGreedyTerrainDecimation::~SoVtkGreedyTerrainDecimation()
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

void SoVtkGreedyTerrainDecimation::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkGreedyTerrainDecimation, SoEngine, "Engine" );
}

void SoVtkGreedyTerrainDecimation::evaluate()
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


void SoVtkGreedyTerrainDecimation::inputChanged(SoField * f)
{
	// Get the AbsoluteError value
	if ( f == &AbsoluteError )
		SO_VTK_SET_FIELD_VALUE( mObject, AbsoluteError);

	// Get the ErrorMeasure value
	if ( f == &ErrorMeasure )
		SO_VTK_SET_FIELD_VALUE( mObject, ErrorMeasure);

	// Get the RelativeError value
	if ( f == &RelativeError )
		SO_VTK_SET_FIELD_VALUE( mObject, RelativeError);

	// Get the Reduction value
	if ( f == &Reduction )
		SO_VTK_SET_FIELD_VALUE( mObject, Reduction);

	// Get the BoundaryVertexDeletion value
	if ( f == &BoundaryVertexDeletion )
		SO_VTK_SET_FIELD_VALUE( mObject, BoundaryVertexDeletion);

	// Get the ComputeNormals value
	if ( f == &ComputeNormals )
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeNormals);

	mObject->Update();
}

void SoVtkGreedyTerrainDecimation::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkGreedyTerrainDecimation::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the AbsoluteError value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AbsoluteError);

	// Get the ErrorMeasure value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ErrorMeasure);

	// Get the RelativeError value
	
		SO_VTK_SET_FIELD_VALUE( mObject, RelativeError);

	// Get the Reduction value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Reduction);

	// Get the BoundaryVertexDeletion value
	
		SO_VTK_SET_FIELD_VALUE( mObject, BoundaryVertexDeletion);

	// Get the ComputeNormals value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeNormals);

	mObject->Update();
}
