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
 
 
# include "SoVtkImageMaskBits.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageMaskBits )

SoVtkImageMaskBits::SoVtkImageMaskBits()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageMaskBits);

	mObject = vtkImageMaskBits::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageMaskBits *aImageMaskBits = vtkImageMaskBits::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Masks, (0,0,0,0));

	y = (int *) aImageMaskBits->GetMasks();
	Masks.setValue((float) y[0],(float) y[1],(float) y[2],(float) y[3]);

	SO_ENGINE_ADD_INPUT(Mask, (0));
	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aImageMaskBits->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(Operation, (0));
	Operation.setValue(aImageMaskBits->GetOperation());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageMaskBits->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageMaskBits::~SoVtkImageMaskBits()
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

void SoVtkImageMaskBits::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageMaskBits, SoEngine, "Engine" );
}

void SoVtkImageMaskBits::evaluate()
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


void SoVtkImageMaskBits::inputChanged(SoField * f)
{
	// Get the Masks value
	if ( f == &Masks )
		SO_VTK_SET_FIELD_VEC4F( mObject, Masks);

	// Get the Mask value
	if ( f == &Mask )
		SO_VTK_SET_FIELD_VALUE( mObject, Mask);

	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the Operation value
	if ( f == &Operation )
		SO_VTK_SET_FIELD_VALUE( mObject, Operation);

	mObject->Update();
}

void SoVtkImageMaskBits::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageMaskBits::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Masks value
	
		SO_VTK_SET_FIELD_VEC4F( mObject, Masks);

	// Get the Mask value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Mask);

	// Get the NumberOfThreads value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the Operation value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Operation);

	mObject->Update();
}
