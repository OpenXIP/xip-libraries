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
 
 
# include "SoVtkImageChangeInformation.h"
# include "SoVtkUtils.h"

# include "vtkImageData.h"
# include "vtkAlgorithmOutput.h"


SO_ENGINE_SOURCE( SoVtkImageChangeInformation )

SoVtkImageChangeInformation::SoVtkImageChangeInformation()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageChangeInformation);

	mObject = vtkImageChangeInformation::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageChangeInformation *aImageChangeInformation = vtkImageChangeInformation::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(ExtentTranslation, (0,0,0));

	y = (int *) aImageChangeInformation->GetExtentTranslation();
	ExtentTranslation.setValue((float) y[0],(float) y[1],(float) y[2]);

	SO_ENGINE_ADD_INPUT(OutputExtentStart, (0,0,0));

	y = (int *) aImageChangeInformation->GetOutputExtentStart();
	OutputExtentStart.setValue((float) y[0],(float) y[1],(float) y[2]);

	SO_ENGINE_ADD_INPUT(OutputOrigin, (0,0,0));

	x = aImageChangeInformation->GetOutputOrigin();
	OutputOrigin.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(OutputSpacing, (0,0,0));

	x = aImageChangeInformation->GetOutputSpacing();
	OutputSpacing.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(OriginScale, (0,0,0));

	x = aImageChangeInformation->GetOriginScale();
	OriginScale.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(InformationInput, (0));

	SO_ENGINE_ADD_INPUT(OriginTranslation, (0,0,0));

	x = aImageChangeInformation->GetOriginTranslation();
	OriginTranslation.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(CenterImage, (0));
	CenterImage.setValue(aImageChangeInformation->GetCenterImage());

	SO_ENGINE_ADD_INPUT(SpacingScale, (0,0,0));

	x = aImageChangeInformation->GetSpacingScale();
	SpacingScale.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageChangeInformation->Delete();


	SO_ENGINE_ADD_OUTPUT( oInformationInput, SoSFVtkObject );
	mInformationInput = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageChangeInformation::~SoVtkImageChangeInformation()
{
	// Deletion of the objects if they exist
	if ( mInformationInput )
	{
	
		mInformationInput->unref();
		mInformationInput = 0;
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

void SoVtkImageChangeInformation::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageChangeInformation, SoEngine, "Engine" );
}

void SoVtkImageChangeInformation::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mInformationInput )
		{
		
			mInformationInput->unref();
			mInformationInput = 0;
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

		mObject->GetInformationInput();
		mInformationInput = new SoVtkObject();
		mInformationInput->ref();
		mInformationInput->setPointer( mObject->GetInformationInput() );

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
	SO_ENGINE_OUTPUT( oInformationInput, SoSFVtkObject, setValue( mInformationInput ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkImageChangeInformation::inputChanged(SoField * f)
{
	// Get the ExtentTranslation value
	if ( f == &ExtentTranslation )
		SO_VTK_SET_FIELD_VEC3F( mObject, ExtentTranslation);

	// Get the OutputExtentStart value
	if ( f == &OutputExtentStart )
		SO_VTK_SET_FIELD_VEC3F( mObject, OutputExtentStart);

	// Get the OutputOrigin value
	if ( f == &OutputOrigin )
		SO_VTK_SET_FIELD_VEC3F( mObject, OutputOrigin);

	// Get the OutputSpacing value
	if ( f == &OutputSpacing )
		SO_VTK_SET_FIELD_VEC3F( mObject, OutputSpacing);

	// Get the OriginScale value
	if ( f == &OriginScale )
		SO_VTK_SET_FIELD_VEC3F( mObject, OriginScale);

	// Get the InformationInput value
	if ( f == &InformationInput )
		SO_VTK_SET_FIELD_DATA( mObject, InformationInput, vtkImageData);

	// Get the OriginTranslation value
	if ( f == &OriginTranslation )
		SO_VTK_SET_FIELD_VEC3F( mObject, OriginTranslation);

	// Get the CenterImage value
	if ( f == &CenterImage )
		SO_VTK_SET_FIELD_VALUE( mObject, CenterImage);

	// Get the SpacingScale value
	if ( f == &SpacingScale )
		SO_VTK_SET_FIELD_VEC3F( mObject, SpacingScale);

	mObject->Update();
}

void SoVtkImageChangeInformation::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageChangeInformation::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the ExtentTranslation value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, ExtentTranslation);

	// Get the OutputExtentStart value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, OutputExtentStart);

	// Get the OutputOrigin value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, OutputOrigin);

	// Get the OutputSpacing value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, OutputSpacing);

	// Get the OriginScale value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, OriginScale);

	// Get the InformationInput value
	
		SO_VTK_SET_FIELD_DATA( mObject, InformationInput, vtkImageData);

	// Get the OriginTranslation value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, OriginTranslation);

	// Get the CenterImage value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CenterImage);

	// Get the SpacingScale value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, SpacingScale);

	mObject->Update();
}
