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

#include "SoVtkBoxClipDataSet.h"
#include "SoVtkUtils.h"

#include "vtkPointLocator.h"
#include "vtkAlgorithmOutput.h"
#include "vtkUnstructuredGrid.h"

SO_ENGINE_SOURCE( SoVtkBoxClipDataSet )

SoVtkBoxClipDataSet::SoVtkBoxClipDataSet()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkBoxClipDataSet);

	mObject = vtkBoxClipDataSet::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkBoxClipDataSet *aBoxClipDataSet = vtkBoxClipDataSet::New();

	SO_ENGINE_ADD_INPUT(Orientation, (0));
	Orientation.setValue(aBoxClipDataSet->GetOrientation());

	SO_ENGINE_ADD_INPUT(BoxClip, ());
	BoxClip.setFormat("double double double double double double");

	SO_ENGINE_ADD_INPUT(GenerateClippedOutput, (0));
	GenerateClippedOutput.setValue(aBoxClipDataSet->
									GetGenerateClippedOutput());

	SO_ENGINE_ADD_INPUT(Locator, (0));

	SO_ENGINE_ADD_INPUT(GenerateClipScalars, (0));
	GenerateClipScalars.setValue(aBoxClipDataSet->
									GetGenerateClipScalars());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aBoxClipDataSet->Delete();

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	SO_ENGINE_ADD_OUTPUT( oLocator, SoSFVtkObject );
	mLocator = 0;

	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

	SO_ENGINE_ADD_OUTPUT( oClippedOutput, SoSFVtkObject );
	mClippedOutput = 0;

	addCalled = 0;
}

SoVtkBoxClipDataSet::~SoVtkBoxClipDataSet()
{
	// Deletion of the objects if they exist
	if ( mOutput )
	{
		mOutput->unref();
		mOutput = 0;
	}
	
	if ( mLocator )
	{
		mLocator->unref();
		mLocator = 0;
	}
	
	if ( mOutputPort )
	{
		mOutputPort->unref();
		mOutputPort = 0;
	}
	
	if ( mClippedOutput )
	{
		mClippedOutput->unref();
		mClippedOutput = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
}

void SoVtkBoxClipDataSet::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkBoxClipDataSet, SoEngine, "Engine" );
}

void SoVtkBoxClipDataSet::evaluate()
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
		
		if ( mLocator )
		{
		
			mLocator->unref();
			mLocator = 0;
		}
		
		if ( mOutputPort )
		{
		
			mOutputPort->unref();
			mOutputPort = 0;
		}
		
		if ( mClippedOutput )
		{
		
			mClippedOutput->unref();
			mClippedOutput = 0;
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

		mObject->GetLocator();
		mLocator = new SoVtkObject();
		mLocator->ref();
		mLocator->setPointer( mObject->GetLocator() );

		if ( mObject->GetNumberOfOutputPorts() > 0 )
		{
			mObject->GetOutputPort()->Register(0);
			mOutputPort = new SoVtkAlgorithmOutput();
			mOutputPort->ref();
			mOutputPort->setPointer( mObject->GetOutputPort() );
		}

		mObject->GetClippedOutput();
		mClippedOutput = new SoVtkObject();
		mClippedOutput->ref();
		mClippedOutput->setPointer( mObject->GetClippedOutput() );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( oLocator, SoSFVtkObject, setValue( mLocator ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( oClippedOutput, SoSFVtkObject, setValue( mClippedOutput ) );
}


void SoVtkBoxClipDataSet::inputChanged(SoField * f)
{
	// Get the Orientation value
	if ( f == &Orientation )
		SO_VTK_SET_FIELD_VALUE( mObject, Orientation);

	// Get the BoxClip value
	if ( f == &BoxClip )
	{
		SbVariant *vBoxClip = (SbVariant *)BoxClip.getValues(0);
		SoInput input;
		int nb_fields = BoxClip.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vBoxClip[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetBoxClip( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5
			);
		}
	}

	// Get the GenerateClippedOutput value
	if ( f == &GenerateClippedOutput )
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateClippedOutput);

	// Get the Locator value
	if ( f == &Locator )
		SO_VTK_SET_FIELD_DATA( mObject, Locator, vtkPointLocator);

	// Get the GenerateClipScalars value
	if ( f == &GenerateClipScalars )
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateClipScalars);

	mObject->Update();
}

void SoVtkBoxClipDataSet::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkBoxClipDataSet::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Orientation value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Orientation);

	// Get the BoxClip value
	if (addCalled == 1)
	{
		SbVariant *vBoxClip = (SbVariant *)BoxClip.getValues(0);
		SoInput input;
		int nb_fields = BoxClip.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vBoxClip[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetBoxClip( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5
			);
		}
	}

	// Get the GenerateClippedOutput value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateClippedOutput);

	// Get the Locator value
	
		SO_VTK_SET_FIELD_DATA( mObject, Locator, vtkPointLocator);

	// Get the GenerateClipScalars value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateClipScalars);

	mObject->Update();
}

