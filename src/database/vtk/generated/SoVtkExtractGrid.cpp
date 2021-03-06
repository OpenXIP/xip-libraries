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

# include "SoVtkExtractGrid.h"
# include "SoVtkUtils.h"

# include "vtkDataObject.h"
# include "vtkAlgorithmOutput.h"
# include "vtkStructuredGrid.h"


SO_ENGINE_SOURCE( SoVtkExtractGrid )

SoVtkExtractGrid::SoVtkExtractGrid()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkExtractGrid);

	mObject = vtkExtractGrid::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkExtractGrid *aExtractGrid = vtkExtractGrid::New();
	int *y;

	SO_ENGINE_ADD_INPUT(VOI, (0));

	SO_ENGINE_ADD_INPUT(SampleRate, (0,0,0));

	y= aExtractGrid->GetSampleRate();
	SampleRate.setValue((float) y[0],(float) y[1],(float) y[2]);

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(InputArrayToProcess, ());
	InputArrayToProcess.setFormat("int int int int char*");

	SO_ENGINE_ADD_INPUT(IncludeBoundary, (0));
	IncludeBoundary.setValue(aExtractGrid->GetIncludeBoundary());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aExtractGrid->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

}

SoVtkExtractGrid::~SoVtkExtractGrid()
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

void SoVtkExtractGrid::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkExtractGrid, SoEngine, "Engine" );
}

void SoVtkExtractGrid::evaluate()
{
	try
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
		
		// Get the input type(s)
		SoVtkObject *inputPtr = Input.getValue();
		
		if (inputPtr && inputPtr->getPointer()->IsA("vtkDataObject"))
			mObject->SetInput(vtkDataObject::SafeDownCast(inputPtr->getPointer()));

		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

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


void SoVtkExtractGrid::inputChanged(SoField * f)
{
	// Get the VOI value
	if ( f == &VOI )
	{
		if ( VOI.getNum() >= 6)
		{
			SO_VTK_SET_FIELD_MFINT32( mObject, VOI);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the SampleRate value
	if ( f == &SampleRate )
		SO_VTK_SET_FIELD_VEC3F( mObject, SampleRate);

	// Get the InputArrayToProcess value
	if ( f == &InputArrayToProcess )
	{
		SbVariant vInputArrayToProcess = (SbVariant)InputArrayToProcess.getValue();
		SoInput input;
		int val0;
		int val1;
		int val2;
		int val3;
		SbString val4;
	
		input.setBuffer((void *)vInputArrayToProcess.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		input.read(val2);
		input.read(val3);
		input.read(val4);
		mObject->SetInputArrayToProcess( 
			(int) val0,
			(int) val1,
			(int) val2,
			(int) val3,
			val4.getString()
		);
	}
	// Get the IncludeBoundary value
	if ( f == &IncludeBoundary )
		SO_VTK_SET_FIELD_VALUE( mObject, IncludeBoundary);

	//mObject->Update();
	
}

