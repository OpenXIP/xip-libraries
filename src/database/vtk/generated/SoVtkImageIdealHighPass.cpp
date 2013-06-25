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
 
 
# include "SoVtkImageIdealHighPass.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageIdealHighPass )

SoVtkImageIdealHighPass::SoVtkImageIdealHighPass()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageIdealHighPass);

	mObject = vtkImageIdealHighPass::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageIdealHighPass *aImageIdealHighPass = vtkImageIdealHighPass::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(YCutOff, (0));
	YCutOff.setValue(aImageIdealHighPass->GetYCutOff());

	SO_ENGINE_ADD_INPUT(CutOff, (0,0,0));

	x = aImageIdealHighPass->GetCutOff();
	CutOff.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aImageIdealHighPass->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(ZCutOff, (0));
	ZCutOff.setValue(aImageIdealHighPass->GetZCutOff());

	SO_ENGINE_ADD_INPUT(XCutOff, (0));
	XCutOff.setValue(aImageIdealHighPass->GetXCutOff());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageIdealHighPass->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageIdealHighPass::~SoVtkImageIdealHighPass()
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

void SoVtkImageIdealHighPass::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageIdealHighPass, SoEngine, "Engine" );
}

void SoVtkImageIdealHighPass::evaluate()
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


void SoVtkImageIdealHighPass::inputChanged(SoField * f)
{
	// Get the YCutOff value
	if ( f == &YCutOff )
		SO_VTK_SET_FIELD_VALUE( mObject, YCutOff);

	// Get the CutOff value
	if ( f == &CutOff )
		SO_VTK_SET_FIELD_VEC3F( mObject, CutOff);

	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the ZCutOff value
	if ( f == &ZCutOff )
		SO_VTK_SET_FIELD_VALUE( mObject, ZCutOff);

	// Get the XCutOff value
	if ( f == &XCutOff )
		SO_VTK_SET_FIELD_VALUE( mObject, XCutOff);

	mObject->Update();
}

void SoVtkImageIdealHighPass::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageIdealHighPass::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the YCutOff value
	
		SO_VTK_SET_FIELD_VALUE( mObject, YCutOff);

	// Get the CutOff value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, CutOff);

	// Get the NumberOfThreads value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the ZCutOff value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ZCutOff);

	// Get the XCutOff value
	
		SO_VTK_SET_FIELD_VALUE( mObject, XCutOff);

	mObject->Update();
}
