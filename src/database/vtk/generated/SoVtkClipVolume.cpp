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
 
 
# include "SoVtkClipVolume.h"
# include "SoVtkUtils.h"

# include "vtkPointLocator.h"
# include "vtkImplicitFunction.h"
# include "vtkAlgorithmOutput.h"
# include "vtkUnstructuredGrid.h"


SO_ENGINE_SOURCE( SoVtkClipVolume )

SoVtkClipVolume::SoVtkClipVolume()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkClipVolume);

	mObject = vtkClipVolume::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkClipVolume *aClipVolume = vtkClipVolume::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Value, (0));
	Value.setValue(aClipVolume->GetValue());

	SO_ENGINE_ADD_INPUT(InsideOut, (0));
	InsideOut.setValue(aClipVolume->GetInsideOut());

	SO_ENGINE_ADD_INPUT(Mixed3DCellGeneration, (0));
	Mixed3DCellGeneration.setValue(aClipVolume->GetMixed3DCellGeneration());

	SO_ENGINE_ADD_INPUT(GenerateClippedOutput, (0));
	GenerateClippedOutput.setValue(aClipVolume->GetGenerateClippedOutput());

	SO_ENGINE_ADD_INPUT(Locator, (0));

	SO_ENGINE_ADD_INPUT(GenerateClipScalars, (0));
	GenerateClipScalars.setValue(aClipVolume->GetGenerateClipScalars());

	SO_ENGINE_ADD_INPUT(ClipFunction, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(MergeTolerance, (0));
	MergeTolerance.setValue(aClipVolume->GetMergeTolerance());

	aClipVolume->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oLocator, SoSFVtkObject );
	mLocator = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( oClipFunction, SoSFVtkObject );
	mClipFunction = 0;
	SO_ENGINE_ADD_OUTPUT( oClippedOutput, SoSFVtkObject );
	mClippedOutput = 0;


	addCalled = 0;
}

SoVtkClipVolume::~SoVtkClipVolume()
{
	// Deletion of the objects if they exist
	if ( mOutput )
	{
	
		mOutput->unref();
		mOutput = 0;
	}
	
	if ( mLocator )
	{
	
		mLocator->unref();
		mLocator = 0;
	}
	
	if ( mOutputPort )
	{
	
		mOutputPort->unref();
		mOutputPort = 0;
	}
	
	if ( mClipFunction )
	{
	
		mClipFunction->unref();
		mClipFunction = 0;
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

void SoVtkClipVolume::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkClipVolume, SoEngine, "Engine" );
}

void SoVtkClipVolume::evaluate()
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
		
		if ( mLocator )
		{
		
			mLocator->unref();
			mLocator = 0;
		}
		
		if ( mOutputPort )
		{
		
			mOutputPort->unref();
			mOutputPort = 0;
		}
		
		if ( mClipFunction )
		{
		
			mClipFunction->unref();
			mClipFunction = 0;
		}
		
		if ( mClippedOutput )
		{
		
			mClippedOutput->unref();
			mClippedOutput = 0;
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

		mObject->GetLocator();
		mLocator = new SoVtkObject();
		mLocator->ref();
		mLocator->setPointer( mObject->GetLocator() );

		if ( mObject->GetNumberOfOutputPorts() > 0 )
		{
			mObject->GetOutputPort()->Register(0);
			mOutputPort = new SoVtkAlgorithmOutput();
			mOutputPort->ref();
			mOutputPort->setPointer( mObject->GetOutputPort() );
		}

		mObject->GetClipFunction();
		mClipFunction = new SoVtkObject();
		mClipFunction->ref();
		mClipFunction->setPointer( mObject->GetClipFunction() );

		mObject->GetClippedOutput();
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
	SO_ENGINE_OUTPUT( oLocator, SoSFVtkObject, setValue( mLocator ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( oClipFunction, SoSFVtkObject, setValue( mClipFunction ) );
	SO_ENGINE_OUTPUT( oClippedOutput, SoSFVtkObject, setValue( mClippedOutput ) );
}


void SoVtkClipVolume::inputChanged(SoField * f)
{
	// Get the Value value
	if ( f == &Value )
		SO_VTK_SET_FIELD_VALUE( mObject, Value);

	// Get the InsideOut value
	if ( f == &InsideOut )
		SO_VTK_SET_FIELD_VALUE( mObject, InsideOut);

	// Get the Mixed3DCellGeneration value
	if ( f == &Mixed3DCellGeneration )
		SO_VTK_SET_FIELD_VALUE( mObject, Mixed3DCellGeneration);

	// Get the GenerateClippedOutput value
	if ( f == &GenerateClippedOutput )
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateClippedOutput);

	// Get the Locator value
	if ( f == &Locator )
		SO_VTK_SET_FIELD_DATA( mObject, Locator, vtkPointLocator);

	// Get the GenerateClipScalars value
	if ( f == &GenerateClipScalars )
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateClipScalars);

	// Get the ClipFunction value
	if ( f == &ClipFunction )
		SO_VTK_SET_FIELD_DATA( mObject, ClipFunction, vtkImplicitFunction);

	// Get the MergeTolerance value
	if ( f == &MergeTolerance )
		SO_VTK_SET_FIELD_VALUE( mObject, MergeTolerance);

	mObject->Update();
}

void SoVtkClipVolume::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkClipVolume::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Value value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Value);

	// Get the InsideOut value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InsideOut);

	// Get the Mixed3DCellGeneration value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Mixed3DCellGeneration);

	// Get the GenerateClippedOutput value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateClippedOutput);

	// Get the Locator value
	
		SO_VTK_SET_FIELD_DATA( mObject, Locator, vtkPointLocator);

	// Get the GenerateClipScalars value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateClipScalars);

	// Get the ClipFunction value
	
		SO_VTK_SET_FIELD_DATA( mObject, ClipFunction, vtkImplicitFunction);

	// Get the MergeTolerance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MergeTolerance);

	mObject->Update();
}
