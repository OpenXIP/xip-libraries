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

# include "SoVtkClipPolyData.h"
# include "SoVtkUtils.h"

# include "vtkPointLocator.h"
# include "vtkDataObject.h"
# include "vtkImplicitFunction.h"
# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkClipPolyData )

SoVtkClipPolyData::SoVtkClipPolyData()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkClipPolyData);

	mObject = vtkClipPolyData::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkClipPolyData *aClipPolyData = vtkClipPolyData::New();

	SO_ENGINE_ADD_INPUT(Value, (0));
	Value.setValue(aClipPolyData->GetValue());

	SO_ENGINE_ADD_INPUT(InsideOut, (0));
	InsideOut.setValue(aClipPolyData->GetInsideOut());

	SO_ENGINE_ADD_INPUT(GenerateClippedOutput, (0));
	GenerateClippedOutput.setValue(aClipPolyData->GetGenerateClippedOutput());

	SO_ENGINE_ADD_INPUT(Locator, (0));

	SO_ENGINE_ADD_INPUT(InputArrayToProcess, ());
	InputArrayToProcess.setFormat("int int int int char*");

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(GenerateClipScalars, (0));
	GenerateClipScalars.setValue(aClipPolyData->GetGenerateClipScalars());

	SO_ENGINE_ADD_INPUT(ClipFunction, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aClipPolyData->Delete();

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

	SO_ENGINE_ADD_OUTPUT( ClippedOutput, SoSFVtkObject );
	mClippedOutput = 0;
}

SoVtkClipPolyData::~SoVtkClipPolyData()
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
	
	if ( mClippedOutput )
	{
	
		mClippedOutput->unref();
		mClippedOutput = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkClipPolyData::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkClipPolyData, SoEngine, "Engine" );
}

void SoVtkClipPolyData::evaluate()
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
		
		if ( mClippedOutput )
		{
		
			mClippedOutput->unref();
			mClippedOutput = 0;
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

		mObject->GetClippedOutput()->Register(0);
		mClippedOutput = new SoVtkObject();
		mClippedOutput->ref();
		mClippedOutput->setPointer( mObject->GetClippedOutput() );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( ClippedOutput, SoSFVtkObject, setValue( mClippedOutput ) );
}


void SoVtkClipPolyData::inputChanged(SoField * f)
{
	// Get the Value value
	if ( f == &Value )
		SO_VTK_SET_FIELD_VALUE( mObject, Value);

	// Get the InsideOut value
	if ( f == &InsideOut )
		SO_VTK_SET_FIELD_VALUE( mObject, InsideOut);

	// Get the GenerateClippedOutput value
	if ( f == &GenerateClippedOutput )
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateClippedOutput);

	// Get the Locator value
	if ( f == &Locator )
		SO_VTK_SET_FIELD_DATA( mObject, Locator, vtkPointLocator);

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
	// Get the GenerateClipScalars value
	if ( f == &GenerateClipScalars )
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateClipScalars);

	// Get the ClipFunction value
	if ( f == &ClipFunction )
		SO_VTK_SET_FIELD_DATA( mObject, ClipFunction, vtkImplicitFunction);

	//mObject->Update();
	
}

