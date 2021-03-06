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
 
 
# include "SoVtkImplicitModeller.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImplicitModeller )

SoVtkImplicitModeller::SoVtkImplicitModeller()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImplicitModeller);

	mObject = vtkImplicitModeller::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImplicitModeller *aImplicitModeller = vtkImplicitModeller::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(ModelBounds, (0));

	SO_ENGINE_ADD_INPUT(CapValue, (0));
	SO_ENGINE_ADD_INPUT(Capping, (0));
	Capping.setValue(aImplicitModeller->GetCapping());

	SO_ENGINE_ADD_INPUT(SampleDimensions, ());
	SampleDimensions.setFormat("int int int");

	SO_ENGINE_ADD_INPUT(OutputScalarType, (0));
	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aImplicitModeller->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(ProcessMode, (0));
	ProcessMode.setValue(aImplicitModeller->GetProcessMode());

	SO_ENGINE_ADD_INPUT(AdjustBounds, (0));
	AdjustBounds.setValue(aImplicitModeller->GetAdjustBounds());

	SO_ENGINE_ADD_INPUT(MaximumDistance, (0));
	MaximumDistance.setValue(aImplicitModeller->GetMaximumDistance());

	SO_ENGINE_ADD_INPUT(LocatorMaxLevel, (0));
	LocatorMaxLevel.setValue(aImplicitModeller->GetLocatorMaxLevel());

	SO_ENGINE_ADD_INPUT(ScaleToMaximumDistance, (0));
	ScaleToMaximumDistance.setValue(aImplicitModeller->GetScaleToMaximumDistance());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImplicitModeller->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImplicitModeller::~SoVtkImplicitModeller()
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

void SoVtkImplicitModeller::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImplicitModeller, SoEngine, "Engine" );
}

void SoVtkImplicitModeller::evaluate()
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


void SoVtkImplicitModeller::inputChanged(SoField * f)
{
	// Get the ModelBounds value
	if ( f == &ModelBounds )
	{
		if ( ModelBounds.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFDOUBLE( mObject, ModelBounds);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the CapValue value
	if ( f == &CapValue )
		SO_VTK_SET_FIELD_VALUE( mObject, CapValue);

	// Get the Capping value
	if ( f == &Capping )
		SO_VTK_SET_FIELD_VALUE( mObject, Capping);

	// Get the SampleDimensions value
	if ( f == &SampleDimensions )
	{
		SbVariant *vSampleDimensions = (SbVariant *)SampleDimensions.getValues(0);
		SoInput input;
		int nb_fields = SampleDimensions.getNum();

		int val0;
		int val1;
		int val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vSampleDimensions[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetSampleDimensions( 
				(int) val0,
				(int) val1,
				(int) val2
			);
		}
	}

	// Get the OutputScalarType value
	if ( f == &OutputScalarType )
		SO_VTK_SET_FIELD_VALUE( mObject, OutputScalarType);

	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the ProcessMode value
	if ( f == &ProcessMode )
		SO_VTK_SET_FIELD_VALUE( mObject, ProcessMode);

	// Get the AdjustBounds value
	if ( f == &AdjustBounds )
		SO_VTK_SET_FIELD_VALUE( mObject, AdjustBounds);

	// Get the MaximumDistance value
	if ( f == &MaximumDistance )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumDistance);

	// Get the LocatorMaxLevel value
	if ( f == &LocatorMaxLevel )
		SO_VTK_SET_FIELD_VALUE( mObject, LocatorMaxLevel);

	// Get the ScaleToMaximumDistance value
	if ( f == &ScaleToMaximumDistance )
		SO_VTK_SET_FIELD_VALUE( mObject, ScaleToMaximumDistance);

	mObject->Update();
}

void SoVtkImplicitModeller::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImplicitModeller::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the ModelBounds value
	
	{
		if ( ModelBounds.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFDOUBLE( mObject, ModelBounds);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the CapValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CapValue);

	// Get the Capping value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Capping);

	// Get the SampleDimensions value
	if (addCalled == 1)
	{
		SbVariant *vSampleDimensions = (SbVariant *)SampleDimensions.getValues(0);
		SoInput input;
		int nb_fields = SampleDimensions.getNum();

		int val0;
		int val1;
		int val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vSampleDimensions[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetSampleDimensions( 
				(int) val0,
				(int) val1,
				(int) val2
			);
		}
	}

	// Get the OutputScalarType value
	
		SO_VTK_SET_FIELD_VALUE( mObject, OutputScalarType);

	// Get the NumberOfThreads value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the ProcessMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ProcessMode);

	// Get the AdjustBounds value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AdjustBounds);

	// Get the MaximumDistance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumDistance);

	// Get the LocatorMaxLevel value
	
		SO_VTK_SET_FIELD_VALUE( mObject, LocatorMaxLevel);

	// Get the ScaleToMaximumDistance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ScaleToMaximumDistance);

	mObject->Update();
}
