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
 
 
# include "SoVtkImageCursor3D.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageCursor3D )

SoVtkImageCursor3D::SoVtkImageCursor3D()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageCursor3D);

	mObject = vtkImageCursor3D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageCursor3D *aImageCursor3D = vtkImageCursor3D::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(CursorRadius, (0));
	CursorRadius.setValue(aImageCursor3D->GetCursorRadius());

	SO_ENGINE_ADD_INPUT(CursorPosition, (0,0,0));

	x = aImageCursor3D->GetCursorPosition();
	CursorPosition.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(CursorValue, (0));
	CursorValue.setValue(aImageCursor3D->GetCursorValue());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageCursor3D->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageCursor3D::~SoVtkImageCursor3D()
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

void SoVtkImageCursor3D::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageCursor3D, SoEngine, "Engine" );
}

void SoVtkImageCursor3D::evaluate()
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


void SoVtkImageCursor3D::inputChanged(SoField * f)
{
	// Get the CursorRadius value
	if ( f == &CursorRadius )
		SO_VTK_SET_FIELD_VALUE( mObject, CursorRadius);

	// Get the CursorPosition value
	if ( f == &CursorPosition )
		SO_VTK_SET_FIELD_VEC3F( mObject, CursorPosition);

	// Get the CursorValue value
	if ( f == &CursorValue )
		SO_VTK_SET_FIELD_VALUE( mObject, CursorValue);

	mObject->Update();
}

void SoVtkImageCursor3D::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageCursor3D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the CursorRadius value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CursorRadius);

	// Get the CursorPosition value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, CursorPosition);

	// Get the CursorValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CursorValue);

	mObject->Update();
}
