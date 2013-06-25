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
/*
 * \brief
 * \author Sylvain Jaume, Francois Huguet
 */

#include "SoVtkExtractCTHPart.h"
#include "SoVtkUtils.h"

#include "vtkMultiProcessController.h"
#include "vtkPlane.h"
#include "vtkAlgorithmOutput.h"
#include "vtkPolyData.h"
#include "vtkMultiBlockDataSet.h"

SO_ENGINE_SOURCE( SoVtkExtractCTHPart )

SoVtkExtractCTHPart::SoVtkExtractCTHPart()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkExtractCTHPart);

	mObject = vtkExtractCTHPart::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkExtractCTHPart *aExtractCTHPart = vtkExtractCTHPart::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Controller, (0));

	SO_ENGINE_ADD_INPUT(VolumeArrayName, (""));

	SO_ENGINE_ADD_INPUT(ClipPlane, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aExtractCTHPart->Delete();


	SO_ENGINE_ADD_OUTPUT( oController, SoSFVtkObject );
	mController = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkExtractCTHPart::~SoVtkExtractCTHPart()
{
	// Deletion of the objects if they exist
	if ( mController )
	{
	
		mController->unref();
		mController = 0;
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

void SoVtkExtractCTHPart::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkExtractCTHPart, SoEngine, "Engine" );
}

void SoVtkExtractCTHPart::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mController )
		{
		
			mController->unref();
			mController = 0;
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

		mObject->GetController();
		mController = new SoVtkObject();
		mController->ref();
		mController->setPointer( mObject->GetController() );

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
	SO_ENGINE_OUTPUT( oController, SoSFVtkObject, setValue( mController ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkExtractCTHPart::inputChanged(SoField * f)
{
	// Get the Controller value
	if ( f == &Controller )
		SO_VTK_SET_FIELD_DATA( mObject, Controller, vtkMultiProcessController);

	// Get the VolumeArrayName value
	if ( f == &VolumeArrayName )
		addCalled = 1;
	// Get the ClipPlane value
	if ( f == &ClipPlane )
		SO_VTK_SET_FIELD_DATA( mObject, ClipPlane, vtkPlane);

	mObject->Update();
}

void SoVtkExtractCTHPart::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkExtractCTHPart::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Controller value
	
		SO_VTK_SET_FIELD_DATA( mObject, Controller, vtkMultiProcessController);

	// Get the VolumeArrayName value
	
		SO_VTK_ADD_FIELD_MFSTRING( mObject, VolumeArrayName);

	// Get the ClipPlane value
	
		SO_VTK_SET_FIELD_DATA( mObject, ClipPlane, vtkPlane);

	mObject->Update();
}

