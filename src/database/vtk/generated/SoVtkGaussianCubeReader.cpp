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
 
 
# include "SoVtkGaussianCubeReader.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkTransform.h"
# include "vtkPolyData.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkGaussianCubeReader )

SoVtkGaussianCubeReader::SoVtkGaussianCubeReader()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkGaussianCubeReader);

	mObject = vtkGaussianCubeReader::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkGaussianCubeReader *aGaussianCubeReader = vtkGaussianCubeReader::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(HBScale, (0));
	HBScale.setValue(aGaussianCubeReader->GetHBScale());

	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(BScale, (0));
	BScale.setValue(aGaussianCubeReader->GetBScale());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aGaussianCubeReader->Delete();


	SO_ENGINE_ADD_OUTPUT( oTransform, SoSFVtkObject );
	mTransform = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( oGridOutput, SoSFVtkObject );
	mGridOutput = 0;


	addCalled = 0;
}

SoVtkGaussianCubeReader::~SoVtkGaussianCubeReader()
{
	// Deletion of the objects if they exist
	if ( mTransform )
	{
	
		mTransform->unref();
		mTransform = 0;
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
	
	if ( mGridOutput )
	{
	
		mGridOutput->unref();
		mGridOutput = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkGaussianCubeReader::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkGaussianCubeReader, SoEngine, "Engine" );
}

void SoVtkGaussianCubeReader::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mTransform )
		{
		
			mTransform->unref();
			mTransform = 0;
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
		
		if ( mGridOutput )
		{
		
			mGridOutput->unref();
			mGridOutput = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetTransform();
		mTransform = new SoVtkObject();
		mTransform->ref();
		mTransform->setPointer( mObject->GetTransform() );

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

		mObject->GetGridOutput();
		mGridOutput = new SoVtkObject();
		mGridOutput->ref();
		mGridOutput->setPointer( mObject->GetGridOutput() );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oTransform, SoSFVtkObject, setValue( mTransform ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( oGridOutput, SoSFVtkObject, setValue( mGridOutput ) );
}


void SoVtkGaussianCubeReader::inputChanged(SoField * f)
{
	// Get the HBScale value
	if ( f == &HBScale )
		SO_VTK_SET_FIELD_VALUE( mObject, HBScale);

	// Get the FileName value
	if ( f == &FileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the BScale value
	if ( f == &BScale )
		SO_VTK_SET_FIELD_VALUE( mObject, BScale);

	mObject->Update();
}

void SoVtkGaussianCubeReader::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkGaussianCubeReader::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the HBScale value
	
		SO_VTK_SET_FIELD_VALUE( mObject, HBScale);

	// Get the FileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the BScale value
	
		SO_VTK_SET_FIELD_VALUE( mObject, BScale);

	mObject->Update();
}
