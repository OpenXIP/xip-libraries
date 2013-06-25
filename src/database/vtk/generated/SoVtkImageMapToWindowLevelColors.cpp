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
 
 
# include "SoVtkImageMapToWindowLevelColors.h"
# include "SoVtkUtils.h"

# include "vtkScalarsToColors.h"
# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageMapToWindowLevelColors )

SoVtkImageMapToWindowLevelColors::SoVtkImageMapToWindowLevelColors()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageMapToWindowLevelColors);

	mObject = vtkImageMapToWindowLevelColors::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageMapToWindowLevelColors *aImageMapToWindowLevelColors = vtkImageMapToWindowLevelColors::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(OutputFormat, (0));
	OutputFormat.setValue(aImageMapToWindowLevelColors->GetOutputFormat());

	SO_ENGINE_ADD_INPUT(PassAlphaToOutput, (0));
	PassAlphaToOutput.setValue(aImageMapToWindowLevelColors->GetPassAlphaToOutput());

	SO_ENGINE_ADD_INPUT(Level, (0));
	Level.setValue(aImageMapToWindowLevelColors->GetLevel());

	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aImageMapToWindowLevelColors->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(LookupTable, (0));

	SO_ENGINE_ADD_INPUT(Window, (0));
	Window.setValue(aImageMapToWindowLevelColors->GetWindow());

	SO_ENGINE_ADD_INPUT(ActiveComponent, (0));
	ActiveComponent.setValue(aImageMapToWindowLevelColors->GetActiveComponent());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageMapToWindowLevelColors->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( oLookupTable, SoSFVtkObject );
	mLookupTable = 0;


	addCalled = 0;
}

SoVtkImageMapToWindowLevelColors::~SoVtkImageMapToWindowLevelColors()
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
	
	if ( mLookupTable )
	{
	
		mLookupTable->unref();
		mLookupTable = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkImageMapToWindowLevelColors::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageMapToWindowLevelColors, SoEngine, "Engine" );
}

void SoVtkImageMapToWindowLevelColors::evaluate()
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
		
		if ( mLookupTable )
		{
		
			mLookupTable->unref();
			mLookupTable = 0;
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

		mObject->GetLookupTable();
		mLookupTable = new SoVtkObject();
		mLookupTable->ref();
		mLookupTable->setPointer( mObject->GetLookupTable() );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( oLookupTable, SoSFVtkObject, setValue( mLookupTable ) );
}


void SoVtkImageMapToWindowLevelColors::inputChanged(SoField * f)
{
	// Get the OutputFormat value
	if ( f == &OutputFormat )
		SO_VTK_SET_FIELD_VALUE( mObject, OutputFormat);

	// Get the PassAlphaToOutput value
	if ( f == &PassAlphaToOutput )
		SO_VTK_SET_FIELD_VALUE( mObject, PassAlphaToOutput);

	// Get the Level value
	if ( f == &Level )
		SO_VTK_SET_FIELD_VALUE( mObject, Level);

	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the LookupTable value
	if ( f == &LookupTable )
		SO_VTK_SET_FIELD_DATA( mObject, LookupTable, vtkScalarsToColors);

	// Get the Window value
	if ( f == &Window )
		SO_VTK_SET_FIELD_VALUE( mObject, Window);

	// Get the ActiveComponent value
	if ( f == &ActiveComponent )
		SO_VTK_SET_FIELD_VALUE( mObject, ActiveComponent);

	mObject->Update();
}

void SoVtkImageMapToWindowLevelColors::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageMapToWindowLevelColors::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the OutputFormat value
	
		SO_VTK_SET_FIELD_VALUE( mObject, OutputFormat);

	// Get the PassAlphaToOutput value
	
		SO_VTK_SET_FIELD_VALUE( mObject, PassAlphaToOutput);

	// Get the Level value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Level);

	// Get the NumberOfThreads value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the LookupTable value
	
		SO_VTK_SET_FIELD_DATA( mObject, LookupTable, vtkScalarsToColors);

	// Get the Window value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Window);

	// Get the ActiveComponent value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ActiveComponent);

	mObject->Update();
}
