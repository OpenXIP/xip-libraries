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

#include "SoVtkBooleanTexture.h"
#include "SoVtkUtils.h"

#include "vtkAlgorithmOutput.h"
#include "vtkImageData.h"

SO_ENGINE_SOURCE( SoVtkBooleanTexture )

SoVtkBooleanTexture::SoVtkBooleanTexture()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkBooleanTexture);

	mObject = vtkBooleanTexture::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkBooleanTexture *aBooleanTexture = vtkBooleanTexture::New();
	double x[3] = {0.0, 0.0, 0.0};

	SO_ENGINE_ADD_INPUT(OutIn, (0,0));
	OutIn.setValue(x[0],x[1]);

	SO_ENGINE_ADD_INPUT(XSize, (0));
	XSize.setValue(aBooleanTexture->GetXSize());

	SO_ENGINE_ADD_INPUT(OnOn, (0,0));
	OnOn.setValue(x[0],x[1]);

	SO_ENGINE_ADD_INPUT(OutOut, (0,0));
	OutOut.setValue(x[0],x[1]);

	SO_ENGINE_ADD_INPUT(InOn, (0,0));
	InOn.setValue(x[0],x[1]);

	SO_ENGINE_ADD_INPUT(Thickness, (0));
	Thickness.setValue(aBooleanTexture->GetThickness());

	SO_ENGINE_ADD_INPUT(YSize, (0));
	YSize.setValue(aBooleanTexture->GetYSize());

	SO_ENGINE_ADD_INPUT(OnIn, (0,0));
	OnIn.setValue(x[0],x[1]);

	SO_ENGINE_ADD_INPUT(OutOn, (0,0));
	OutOn.setValue(x[0],x[1]);

	SO_ENGINE_ADD_INPUT(InIn, (0,0));
	InIn.setValue(x[0],x[1]);

	SO_ENGINE_ADD_INPUT(InOut, (0,0));
	InOut.setValue(x[0],x[1]);

	SO_ENGINE_ADD_INPUT(OnOut, (0,0));
	OnOut.setValue(x[0],x[1]);

	SO_ENGINE_ADD_INPUT(InputConnection, (0));
	aBooleanTexture->Delete();

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

	addCalled = 0;
}

SoVtkBooleanTexture::~SoVtkBooleanTexture()
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

void SoVtkBooleanTexture::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkBooleanTexture, SoEngine, "Engine" );
}

void SoVtkBooleanTexture::evaluate()
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


void SoVtkBooleanTexture::inputChanged(SoField * f)
{
	// Get the OutIn value
	if ( f == &OutIn )
		SO_VTK_SET_FIELD_VEC2F( mObject, OutIn);

	// Get the XSize value
	if ( f == &XSize )
		SO_VTK_SET_FIELD_VALUE( mObject, XSize);

	// Get the OnOn value
	if ( f == &OnOn )
		SO_VTK_SET_FIELD_VEC2F( mObject, OnOn);

	// Get the OutOut value
	if ( f == &OutOut )
		SO_VTK_SET_FIELD_VEC2F( mObject, OutOut);

	// Get the InOn value
	if ( f == &InOn )
		SO_VTK_SET_FIELD_VEC2F( mObject, InOn);

	// Get the Thickness value
	if ( f == &Thickness )
		SO_VTK_SET_FIELD_VALUE( mObject, Thickness);

	// Get the YSize value
	if ( f == &YSize )
		SO_VTK_SET_FIELD_VALUE( mObject, YSize);

	// Get the OnIn value
	if ( f == &OnIn )
		SO_VTK_SET_FIELD_VEC2F( mObject, OnIn);

	// Get the OutOn value
	if ( f == &OutOn )
		SO_VTK_SET_FIELD_VEC2F( mObject, OutOn);

	// Get the InIn value
	if ( f == &InIn )
		SO_VTK_SET_FIELD_VEC2F( mObject, InIn);

	// Get the InOut value
	if ( f == &InOut )
		SO_VTK_SET_FIELD_VEC2F( mObject, InOut);

	// Get the OnOut value
	if ( f == &OnOut )
		SO_VTK_SET_FIELD_VEC2F( mObject, OnOut);

	mObject->Update();
}

void SoVtkBooleanTexture::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkBooleanTexture::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the OutIn value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, OutIn);

	// Get the XSize value
	
		SO_VTK_SET_FIELD_VALUE( mObject, XSize);

	// Get the OnOn value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, OnOn);

	// Get the OutOut value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, OutOut);

	// Get the InOn value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, InOn);

	// Get the Thickness value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Thickness);

	// Get the YSize value
	
		SO_VTK_SET_FIELD_VALUE( mObject, YSize);

	// Get the OnIn value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, OnIn);

	// Get the OutOn value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, OutOn);

	// Get the InIn value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, InIn);

	// Get the InOut value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, InOut);

	// Get the OnOut value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, OnOut);

	mObject->Update();
}

