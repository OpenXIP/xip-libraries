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
 * \author Sylvain Jaume <sylvain.jaume@siemens.com>, Francois Huguet
 */
 
#include "SoVtkBlankStructuredGrid.h"
#include "SoVtkUtils.h"

#include "vtkAlgorithmOutput.h"
#include "vtkStructuredGrid.h"

SO_ENGINE_SOURCE( SoVtkBlankStructuredGrid )

SoVtkBlankStructuredGrid::SoVtkBlankStructuredGrid()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkBlankStructuredGrid);

	mObject = vtkBlankStructuredGrid::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkBlankStructuredGrid *aBlankStructuredGrid =
					vtkBlankStructuredGrid::New();

	SO_ENGINE_ADD_INPUT(ArrayName, (""));

	SO_ENGINE_ADD_INPUT(Component, (0));
	Component.setValue(aBlankStructuredGrid->GetComponent());

	SO_ENGINE_ADD_INPUT(ArrayId, (0));
	ArrayId.setValue(aBlankStructuredGrid->GetArrayId());

	SO_ENGINE_ADD_INPUT(MaxBlankingValue, (0));
	MaxBlankingValue.setValue(aBlankStructuredGrid->GetMaxBlankingValue());

	SO_ENGINE_ADD_INPUT(MinBlankingValue, (0));
	MinBlankingValue.setValue(aBlankStructuredGrid->GetMinBlankingValue());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aBlankStructuredGrid->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

	addCalled = 0;
}

SoVtkBlankStructuredGrid::~SoVtkBlankStructuredGrid()
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

void SoVtkBlankStructuredGrid::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkBlankStructuredGrid, SoEngine, "Engine" );
}

void SoVtkBlankStructuredGrid::evaluate()
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
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue(
												 mOutputPort ) );
}


void SoVtkBlankStructuredGrid::inputChanged(SoField * f)
{
	// Get the ArrayName value
	if ( f == &ArrayName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, ArrayName);

	// Get the Component value
	if ( f == &Component )
		SO_VTK_SET_FIELD_VALUE( mObject, Component);

	// Get the ArrayId value
	if ( f == &ArrayId )
		SO_VTK_SET_FIELD_VALUE( mObject, ArrayId);

	// Get the MaxBlankingValue value
	if ( f == &MaxBlankingValue )
		SO_VTK_SET_FIELD_VALUE( mObject, MaxBlankingValue);

	// Get the MinBlankingValue value
	if ( f == &MinBlankingValue )
		SO_VTK_SET_FIELD_VALUE( mObject, MinBlankingValue);

	mObject->Update();
}

void SoVtkBlankStructuredGrid::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkBlankStructuredGrid::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the ArrayName value
		SO_VTK_SET_FIELD_MFSTRING( mObject, ArrayName);

	// Get the Component value
		SO_VTK_SET_FIELD_VALUE( mObject, Component);

	// Get the ArrayId value
		SO_VTK_SET_FIELD_VALUE( mObject, ArrayId);

	// Get the MaxBlankingValue value
		SO_VTK_SET_FIELD_VALUE( mObject, MaxBlankingValue);

	// Get the MinBlankingValue value
		SO_VTK_SET_FIELD_VALUE( mObject, MinBlankingValue);

	mObject->Update();
}

