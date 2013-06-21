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
 
 
# include "SoVtkGaussianSplatter.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkGaussianSplatter )

SoVtkGaussianSplatter::SoVtkGaussianSplatter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkGaussianSplatter);

	mObject = vtkGaussianSplatter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkGaussianSplatter *aGaussianSplatter = vtkGaussianSplatter::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(ExponentFactor, (0));
	ExponentFactor.setValue(aGaussianSplatter->GetExponentFactor());

	SO_ENGINE_ADD_INPUT(ModelBounds, (0));

	SO_ENGINE_ADD_INPUT(Eccentricity, (0));
	Eccentricity.setValue(aGaussianSplatter->GetEccentricity());

	SO_ENGINE_ADD_INPUT(Radius, (0));
	Radius.setValue(aGaussianSplatter->GetRadius());

	SO_ENGINE_ADD_INPUT(CapValue, (0));
	CapValue.setValue(aGaussianSplatter->GetCapValue());

	SO_ENGINE_ADD_INPUT(Capping, (0));
	Capping.setValue(aGaussianSplatter->GetCapping());

	SO_ENGINE_ADD_INPUT(SampleDimensions, ());
	SampleDimensions.setFormat("int int int");

	SO_ENGINE_ADD_INPUT(AccumulationMode, (0));
	AccumulationMode.setValue(aGaussianSplatter->GetAccumulationMode());

	SO_ENGINE_ADD_INPUT(NullValue, (0));
	NullValue.setValue(aGaussianSplatter->GetNullValue());

	SO_ENGINE_ADD_INPUT(NormalWarping, (0));
	NormalWarping.setValue(aGaussianSplatter->GetNormalWarping());

	SO_ENGINE_ADD_INPUT(ScalarWarping, (0));
	ScalarWarping.setValue(aGaussianSplatter->GetScalarWarping());

	SO_ENGINE_ADD_INPUT(ScaleFactor, (0));
	ScaleFactor.setValue(aGaussianSplatter->GetScaleFactor());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aGaussianSplatter->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkGaussianSplatter::~SoVtkGaussianSplatter()
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

void SoVtkGaussianSplatter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkGaussianSplatter, SoEngine, "Engine" );
}

void SoVtkGaussianSplatter::evaluate()
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


void SoVtkGaussianSplatter::inputChanged(SoField * f)
{
	// Get the ExponentFactor value
	if ( f == &ExponentFactor )
		SO_VTK_SET_FIELD_VALUE( mObject, ExponentFactor);

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

	// Get the Eccentricity value
	if ( f == &Eccentricity )
		SO_VTK_SET_FIELD_VALUE( mObject, Eccentricity);

	// Get the Radius value
	if ( f == &Radius )
		SO_VTK_SET_FIELD_VALUE( mObject, Radius);

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

	// Get the AccumulationMode value
	if ( f == &AccumulationMode )
		SO_VTK_SET_FIELD_VALUE( mObject, AccumulationMode);

	// Get the NullValue value
	if ( f == &NullValue )
		SO_VTK_SET_FIELD_VALUE( mObject, NullValue);

	// Get the NormalWarping value
	if ( f == &NormalWarping )
		SO_VTK_SET_FIELD_VALUE( mObject, NormalWarping);

	// Get the ScalarWarping value
	if ( f == &ScalarWarping )
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarWarping);

	// Get the ScaleFactor value
	if ( f == &ScaleFactor )
		SO_VTK_SET_FIELD_VALUE( mObject, ScaleFactor);

	mObject->Update();
}

void SoVtkGaussianSplatter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkGaussianSplatter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the ExponentFactor value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ExponentFactor);

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

	// Get the Eccentricity value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Eccentricity);

	// Get the Radius value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Radius);

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

	// Get the AccumulationMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AccumulationMode);

	// Get the NullValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NullValue);

	// Get the NormalWarping value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NormalWarping);

	// Get the ScalarWarping value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarWarping);

	// Get the ScaleFactor value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ScaleFactor);

	mObject->Update();
}
