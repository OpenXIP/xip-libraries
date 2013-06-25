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
 
 
# include "SoVtkImageStencil.h"
# include "SoVtkUtils.h"

# include "vtkImageStencilData.h"
# include "vtkImageData.h"
# include "vtkAlgorithmOutput.h"


SO_ENGINE_SOURCE( SoVtkImageStencil )

SoVtkImageStencil::SoVtkImageStencil()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageStencil);

	mObject = vtkImageStencil::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageStencil *aImageStencil = vtkImageStencil::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(ReverseStencil, (0));
	ReverseStencil.setValue(aImageStencil->GetReverseStencil());

	SO_ENGINE_ADD_INPUT(Stencil, (0));

	SO_ENGINE_ADD_INPUT(BackgroundColor, (0,0,0,0));

	x = aImageStencil->GetBackgroundColor();
	BackgroundColor.setValue(x[0],x[1],x[2],x[3]);

	SO_ENGINE_ADD_INPUT(BackgroundInput, (0));

	SO_ENGINE_ADD_INPUT(BackgroundValue, (0));
	BackgroundValue.setValue(aImageStencil->GetBackgroundValue());

	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aImageStencil->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageStencil->Delete();


	SO_ENGINE_ADD_OUTPUT( oStencil, SoSFVtkObject );
	mStencil = 0;
	SO_ENGINE_ADD_OUTPUT( oBackgroundInput, SoSFVtkObject );
	mBackgroundInput = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageStencil::~SoVtkImageStencil()
{
	// Deletion of the objects if they exist
	if ( mStencil )
	{
	
		mStencil->unref();
		mStencil = 0;
	}
	
	if ( mBackgroundInput )
	{
	
		mBackgroundInput->unref();
		mBackgroundInput = 0;
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

void SoVtkImageStencil::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageStencil, SoEngine, "Engine" );
}

void SoVtkImageStencil::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mStencil )
		{
		
			mStencil->unref();
			mStencil = 0;
		}
		
		if ( mBackgroundInput )
		{
		
			mBackgroundInput->unref();
			mBackgroundInput = 0;
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

		mObject->GetStencil();
		mStencil = new SoVtkObject();
		mStencil->ref();
		mStencil->setPointer( mObject->GetStencil() );

		mObject->GetBackgroundInput();
		mBackgroundInput = new SoVtkObject();
		mBackgroundInput->ref();
		mBackgroundInput->setPointer( mObject->GetBackgroundInput() );

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
	SO_ENGINE_OUTPUT( oStencil, SoSFVtkObject, setValue( mStencil ) );
	SO_ENGINE_OUTPUT( oBackgroundInput, SoSFVtkObject, setValue( mBackgroundInput ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkImageStencil::inputChanged(SoField * f)
{
	// Get the ReverseStencil value
	if ( f == &ReverseStencil )
		SO_VTK_SET_FIELD_VALUE( mObject, ReverseStencil);

	// Get the Stencil value
	if ( f == &Stencil )
		SO_VTK_SET_FIELD_DATA( mObject, Stencil, vtkImageStencilData);

	// Get the BackgroundColor value
	if ( f == &BackgroundColor )
		SO_VTK_SET_FIELD_VEC4F( mObject, BackgroundColor);

	// Get the BackgroundInput value
	if ( f == &BackgroundInput )
		SO_VTK_SET_FIELD_DATA( mObject, BackgroundInput, vtkImageData);

	// Get the BackgroundValue value
	if ( f == &BackgroundValue )
		SO_VTK_SET_FIELD_VALUE( mObject, BackgroundValue);

	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	mObject->Update();
}

void SoVtkImageStencil::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageStencil::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the ReverseStencil value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ReverseStencil);

	// Get the Stencil value
	
		SO_VTK_SET_FIELD_DATA( mObject, Stencil, vtkImageStencilData);

	// Get the BackgroundColor value
	
		SO_VTK_SET_FIELD_VEC4F( mObject, BackgroundColor);

	// Get the BackgroundInput value
	
		SO_VTK_SET_FIELD_DATA( mObject, BackgroundInput, vtkImageData);

	// Get the BackgroundValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, BackgroundValue);

	// Get the NumberOfThreads value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	mObject->Update();
}
