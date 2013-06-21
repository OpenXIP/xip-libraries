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
 
 
# include "SoVtkImageShrink3D.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageShrink3D )

SoVtkImageShrink3D::SoVtkImageShrink3D()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageShrink3D);

	mObject = vtkImageShrink3D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageShrink3D *aImageShrink3D = vtkImageShrink3D::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Maximum, (0));
	SO_ENGINE_ADD_INPUT(Mean, (0));
	SO_ENGINE_ADD_INPUT(Averaging, (0));
	Averaging.setValue(aImageShrink3D->GetAveraging());

	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aImageShrink3D->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(Shift, (0,0,0));

	y = (int *) aImageShrink3D->GetShift();
	Shift.setValue((float) y[0],(float) y[1],(float) y[2]);

	SO_ENGINE_ADD_INPUT(ShrinkFactors, (0,0,0));

	y = (int *) aImageShrink3D->GetShrinkFactors();
	ShrinkFactors.setValue((float) y[0],(float) y[1],(float) y[2]);

	SO_ENGINE_ADD_INPUT(Minimum, (0));
	SO_ENGINE_ADD_INPUT(Median, (0));
	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageShrink3D->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageShrink3D::~SoVtkImageShrink3D()
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

void SoVtkImageShrink3D::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageShrink3D, SoEngine, "Engine" );
}

void SoVtkImageShrink3D::evaluate()
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


void SoVtkImageShrink3D::inputChanged(SoField * f)
{
	// Get the Maximum value
	if ( f == &Maximum )
		SO_VTK_SET_FIELD_VALUE( mObject, Maximum);

	// Get the Mean value
	if ( f == &Mean )
		SO_VTK_SET_FIELD_VALUE( mObject, Mean);

	// Get the Averaging value
	if ( f == &Averaging )
		SO_VTK_SET_FIELD_VALUE( mObject, Averaging);

	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the Shift value
	if ( f == &Shift )
		SO_VTK_SET_FIELD_VEC3F( mObject, Shift);

	// Get the ShrinkFactors value
	if ( f == &ShrinkFactors )
		SO_VTK_SET_FIELD_VEC3F( mObject, ShrinkFactors);

	// Get the Minimum value
	if ( f == &Minimum )
		SO_VTK_SET_FIELD_VALUE( mObject, Minimum);

	// Get the Median value
	if ( f == &Median )
		SO_VTK_SET_FIELD_VALUE( mObject, Median);

	mObject->Update();
}

void SoVtkImageShrink3D::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageShrink3D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Maximum value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Maximum);

	// Get the Mean value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Mean);

	// Get the Averaging value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Averaging);

	// Get the NumberOfThreads value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the Shift value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Shift);

	// Get the ShrinkFactors value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, ShrinkFactors);

	// Get the Minimum value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Minimum);

	// Get the Median value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Median);

	mObject->Update();
}
