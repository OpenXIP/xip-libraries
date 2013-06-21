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

#include "SoVtkArrowSource.h"
#include "SoVtkUtils.h"

#include "vtkAlgorithmOutput.h"
#include "vtkPolyData.h"

SO_ENGINE_SOURCE( SoVtkArrowSource )

SoVtkArrowSource::SoVtkArrowSource()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkArrowSource);

	mObject = vtkArrowSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkArrowSource *aArrowSource = vtkArrowSource::New();

	SO_ENGINE_ADD_INPUT(TipRadius, (0));
	TipRadius.setValue(aArrowSource->GetTipRadius());

	SO_ENGINE_ADD_INPUT(ShaftResolution, (0));
	ShaftResolution.setValue(aArrowSource->GetShaftResolution());

	SO_ENGINE_ADD_INPUT(TipResolution, (0));
	TipResolution.setValue(aArrowSource->GetTipResolution());

	SO_ENGINE_ADD_INPUT(TipLength, (0));
	TipLength.setValue(aArrowSource->GetTipLength());

	SO_ENGINE_ADD_INPUT(ShaftRadius, (0));
	ShaftRadius.setValue(aArrowSource->GetShaftRadius());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aArrowSource->Delete();

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

	addCalled = 0;
}

SoVtkArrowSource::~SoVtkArrowSource()
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

void SoVtkArrowSource::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkArrowSource, SoEngine, "Engine" );
}

void SoVtkArrowSource::evaluate()
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


void SoVtkArrowSource::inputChanged(SoField * f)
{
	// Get the TipRadius value
	if ( f == &TipRadius )
		SO_VTK_SET_FIELD_VALUE( mObject, TipRadius);

	// Get the ShaftResolution value
	if ( f == &ShaftResolution )
		SO_VTK_SET_FIELD_VALUE( mObject, ShaftResolution);

	// Get the TipResolution value
	if ( f == &TipResolution )
		SO_VTK_SET_FIELD_VALUE( mObject, TipResolution);

	// Get the TipLength value
	if ( f == &TipLength )
		SO_VTK_SET_FIELD_VALUE( mObject, TipLength);

	// Get the ShaftRadius value
	if ( f == &ShaftRadius )
		SO_VTK_SET_FIELD_VALUE( mObject, ShaftRadius);

	mObject->Update();
}

void SoVtkArrowSource::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkArrowSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the TipRadius value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TipRadius);

	// Get the ShaftResolution value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ShaftResolution);

	// Get the TipResolution value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TipResolution);

	// Get the TipLength value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TipLength);

	// Get the ShaftRadius value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ShaftRadius);

	mObject->Update();
}

