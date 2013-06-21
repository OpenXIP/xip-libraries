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
 
#include "SoVtkBlankStructuredGridWithImage.h"
#include "SoVtkUtils.h"

#include "vtkImageData.h"
#include "vtkAlgorithmOutput.h"
#include "vtkStructuredGrid.h"

SO_ENGINE_SOURCE( SoVtkBlankStructuredGridWithImage )

SoVtkBlankStructuredGridWithImage::SoVtkBlankStructuredGridWithImage()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkBlankStructuredGridWithImage);

	mObject = vtkBlankStructuredGridWithImage::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkBlankStructuredGridWithImage *aBlankStructuredGridWithImage =
				 vtkBlankStructuredGridWithImage::New();

	SO_ENGINE_ADD_INPUT(BlankingInput, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aBlankStructuredGridWithImage->Delete();

	SO_ENGINE_ADD_OUTPUT( oBlankingInput, SoSFVtkObject );
	mBlankingInput = 0;

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

	addCalled = 0;
}

SoVtkBlankStructuredGridWithImage::~SoVtkBlankStructuredGridWithImage()
{
	// Deletion of the objects if they exist
	if ( mBlankingInput )
	{
		mBlankingInput->unref();
		mBlankingInput = 0;
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

void SoVtkBlankStructuredGridWithImage::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkBlankStructuredGridWithImage, SoEngine,
								 "Engine" );
}

void SoVtkBlankStructuredGridWithImage::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mBlankingInput )
		{
			mBlankingInput->unref();
			mBlankingInput = 0;
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

		mObject->GetBlankingInput();
		mBlankingInput = new SoVtkObject();
		mBlankingInput->ref();
		mBlankingInput->setPointer( mObject->GetBlankingInput() );

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

	SO_ENGINE_OUTPUT( oBlankingInput, SoSFVtkObject, setValue( mBlankingInput ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkBlankStructuredGridWithImage::inputChanged(SoField * f)
{
	// Get the BlankingInput value
	if ( f == &BlankingInput )
		SO_VTK_SET_FIELD_DATA( mObject, BlankingInput, vtkImageData);

	mObject->Update();
}

void SoVtkBlankStructuredGridWithImage::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkBlankStructuredGridWithImage::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the BlankingInput value
	
		SO_VTK_SET_FIELD_DATA( mObject, BlankingInput, vtkImageData);

	mObject->Update();
}

