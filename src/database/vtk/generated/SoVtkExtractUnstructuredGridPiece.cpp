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
 
 
# include "SoVtkExtractUnstructuredGridPiece.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkUnstructuredGrid.h"


SO_ENGINE_SOURCE( SoVtkExtractUnstructuredGridPiece )

SoVtkExtractUnstructuredGridPiece::SoVtkExtractUnstructuredGridPiece()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkExtractUnstructuredGridPiece);

	mObject = vtkExtractUnstructuredGridPiece::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkExtractUnstructuredGridPiece *aExtractUnstructuredGridPiece = vtkExtractUnstructuredGridPiece::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(CreateGhostCells, (0));
	CreateGhostCells.setValue(aExtractUnstructuredGridPiece->GetCreateGhostCells());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aExtractUnstructuredGridPiece->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkExtractUnstructuredGridPiece::~SoVtkExtractUnstructuredGridPiece()
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

void SoVtkExtractUnstructuredGridPiece::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkExtractUnstructuredGridPiece, SoEngine, "Engine" );
}

void SoVtkExtractUnstructuredGridPiece::evaluate()
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


void SoVtkExtractUnstructuredGridPiece::inputChanged(SoField * f)
{
	// Get the CreateGhostCells value
	if ( f == &CreateGhostCells )
		SO_VTK_SET_FIELD_VALUE( mObject, CreateGhostCells);

	mObject->Update();
}

void SoVtkExtractUnstructuredGridPiece::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkExtractUnstructuredGridPiece::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the CreateGhostCells value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CreateGhostCells);

	mObject->Update();
}
