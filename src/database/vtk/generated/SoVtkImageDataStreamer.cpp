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
 
 
# include "SoVtkImageDataStreamer.h"
# include "SoVtkUtils.h"

# include "vtkExtentTranslator.h"
# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageDataStreamer )

SoVtkImageDataStreamer::SoVtkImageDataStreamer()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageDataStreamer);

	mObject = vtkImageDataStreamer::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageDataStreamer *aImageDataStreamer = vtkImageDataStreamer::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(ExtentTranslator, (0));

	SO_ENGINE_ADD_INPUT(NumberOfStreamDivisions, (0));
	NumberOfStreamDivisions.setValue(aImageDataStreamer->GetNumberOfStreamDivisions());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageDataStreamer->Delete();


	SO_ENGINE_ADD_OUTPUT( oExtentTranslator, SoSFVtkObject );
	mExtentTranslator = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageDataStreamer::~SoVtkImageDataStreamer()
{
	// Deletion of the objects if they exist
	if ( mExtentTranslator )
	{
	
		mExtentTranslator->unref();
		mExtentTranslator = 0;
	}
	
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

void SoVtkImageDataStreamer::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageDataStreamer, SoEngine, "Engine" );
}

void SoVtkImageDataStreamer::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mExtentTranslator )
		{
		
			mExtentTranslator->unref();
			mExtentTranslator = 0;
		}
		
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

		mObject->GetExtentTranslator();
		mExtentTranslator = new SoVtkObject();
		mExtentTranslator->ref();
		mExtentTranslator->setPointer( mObject->GetExtentTranslator() );

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
	SO_ENGINE_OUTPUT( oExtentTranslator, SoSFVtkObject, setValue( mExtentTranslator ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkImageDataStreamer::inputChanged(SoField * f)
{
	// Get the ExtentTranslator value
	if ( f == &ExtentTranslator )
		SO_VTK_SET_FIELD_DATA( mObject, ExtentTranslator, vtkExtentTranslator);

	// Get the NumberOfStreamDivisions value
	if ( f == &NumberOfStreamDivisions )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfStreamDivisions);

	mObject->Update();
}

void SoVtkImageDataStreamer::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageDataStreamer::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the ExtentTranslator value
	
		SO_VTK_SET_FIELD_DATA( mObject, ExtentTranslator, vtkExtentTranslator);

	// Get the NumberOfStreamDivisions value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfStreamDivisions);

	mObject->Update();
}
