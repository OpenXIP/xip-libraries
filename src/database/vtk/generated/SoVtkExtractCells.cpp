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
 
 
# include "SoVtkExtractCells.h"
# include "SoVtkUtils.h"

# include "vtkIdList.h"
# include "vtkAlgorithmOutput.h"
# include "vtkUnstructuredGrid.h"


SO_ENGINE_SOURCE( SoVtkExtractCells )

SoVtkExtractCells::SoVtkExtractCells()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkExtractCells);

	mObject = vtkExtractCells::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkExtractCells *aExtractCells = vtkExtractCells::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(CellList, (0));

	SO_ENGINE_ADD_INPUT(CellRange, ());
	CellRange.setFormat("vtkIdType vtkIdType");

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aExtractCells->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkExtractCells::~SoVtkExtractCells()
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

void SoVtkExtractCells::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkExtractCells, SoEngine, "Engine" );
}

void SoVtkExtractCells::evaluate()
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


void SoVtkExtractCells::inputChanged(SoField * f)
{
	// Get the CellList value
	if ( f == &CellList )
		SO_VTK_SET_FIELD_DATA( mObject, CellList, vtkIdList);

	// Get the CellRange value
	if ( f == &CellRange )
		addCalled = 1;

	mObject->Update();
}

void SoVtkExtractCells::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkExtractCells::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the CellList value
	
		SO_VTK_SET_FIELD_DATA( mObject, CellList, vtkIdList);

	// Get the CellRange value
	if (addCalled == 1)
	{
		SbVariant *vCellRange = (SbVariant *)CellRange.getValues(0);
		SoInput input;
		int nb_fields = CellRange.getNum();

		vtkIdType val0;
		vtkIdType val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vCellRange[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->AddCellRange( 
				(vtkIdType) val0,
				(vtkIdType) val1
			);
		}
	}

	mObject->Update();
}
