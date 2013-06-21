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
 
 
# include "SoVtkImageToImageStencil.h"
# include "SoVtkUtils.h"

# include "vtkImageData.h"
# include "vtkAlgorithmOutput.h"
# include "vtkImageStencilData.h"


SO_ENGINE_SOURCE( SoVtkImageToImageStencil )

SoVtkImageToImageStencil::SoVtkImageToImageStencil()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageToImageStencil);

	mObject = vtkImageToImageStencil::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageToImageStencil *aImageToImageStencil = vtkImageToImageStencil::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(LowerThreshold, (0));
	LowerThreshold.setValue(aImageToImageStencil->GetLowerThreshold());

	SO_ENGINE_ADD_INPUT(UpperThreshold, (0));
	UpperThreshold.setValue(aImageToImageStencil->GetUpperThreshold());

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageToImageStencil->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageToImageStencil::~SoVtkImageToImageStencil()
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

void SoVtkImageToImageStencil::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageToImageStencil, SoEngine, "Engine" );
}

void SoVtkImageToImageStencil::evaluate()
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


void SoVtkImageToImageStencil::inputChanged(SoField * f)
{
	// Get the LowerThreshold value
	if ( f == &LowerThreshold )
		SO_VTK_SET_FIELD_VALUE( mObject, LowerThreshold);

	// Get the UpperThreshold value
	if ( f == &UpperThreshold )
		SO_VTK_SET_FIELD_VALUE( mObject, UpperThreshold);

	mObject->Update();
}

void SoVtkImageToImageStencil::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageToImageStencil::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkObject *inputPtr = Input.getValue();
	
	if (inputPtr && inputPtr->getPointer()->IsA("vtkImageData"))
		mObject->SetInput(vtkImageData::SafeDownCast(inputPtr->getPointer()));

	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the LowerThreshold value
	
		SO_VTK_SET_FIELD_VALUE( mObject, LowerThreshold);

	// Get the UpperThreshold value
	
		SO_VTK_SET_FIELD_VALUE( mObject, UpperThreshold);

	mObject->Update();
}
