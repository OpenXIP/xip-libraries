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
 
 
# include "SoVtkImageSpatialFilter.h"
# include "SoVtkUtils.h"

# include "vtkImageData.h"
# include "vtkAlgorithmOutput.h"


SO_ENGINE_SOURCE( SoVtkImageSpatialFilter )

SoVtkImageSpatialFilter::SoVtkImageSpatialFilter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageSpatialFilter);

	mObject = vtkImageSpatialFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageSpatialFilter *aImageSpatialFilter = vtkImageSpatialFilter::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aImageSpatialFilter->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(InputMemoryLimit, (0));
	InputMemoryLimit.setValue(aImageSpatialFilter->GetInputMemoryLimit());

	SO_ENGINE_ADD_INPUT(NumberOfInputConnections, ());
	NumberOfInputConnections.setFormat("int int");

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageSpatialFilter->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageSpatialFilter::~SoVtkImageSpatialFilter()
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

void SoVtkImageSpatialFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageSpatialFilter, SoEngine, "Engine" );
}

void SoVtkImageSpatialFilter::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkObject *inputPtr = Input.getValue();
		
		if (inputPtr && inputPtr->getPointer()->IsA("vtkImageData"))
			mObject->SetInput(vtkImageData::SafeDownCast(inputPtr->getPointer()));

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


void SoVtkImageSpatialFilter::inputChanged(SoField * f)
{
	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the InputMemoryLimit value
	if ( f == &InputMemoryLimit )
		SO_VTK_SET_FIELD_VALUE( mObject, InputMemoryLimit);

	// Get the NumberOfInputConnections value
	if ( f == &NumberOfInputConnections )
	{
		SbVariant *vNumberOfInputConnections = (SbVariant *)NumberOfInputConnections.getValues(0);
		SoInput input;
		int nb_fields = NumberOfInputConnections.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vNumberOfInputConnections[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetNumberOfInputConnections( 
				(int) val0,
				(int) val1
			);
		}
	}

	mObject->Update();
}

void SoVtkImageSpatialFilter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageSpatialFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkObject *inputPtr = Input.getValue();
	
	if (inputPtr && inputPtr->getPointer()->IsA("vtkImageData"))
		mObject->SetInput(vtkImageData::SafeDownCast(inputPtr->getPointer()));

	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the NumberOfThreads value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the InputMemoryLimit value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InputMemoryLimit);

	// Get the NumberOfInputConnections value
	if (addCalled == 1)
	{
		SbVariant *vNumberOfInputConnections = (SbVariant *)NumberOfInputConnections.getValues(0);
		SoInput input;
		int nb_fields = NumberOfInputConnections.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vNumberOfInputConnections[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetNumberOfInputConnections( 
				(int) val0,
				(int) val1
			);
		}
	}

	mObject->Update();
}
