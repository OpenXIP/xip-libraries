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
 
 
# include "SoVtkImageGaussianSource.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageGaussianSource )

SoVtkImageGaussianSource::SoVtkImageGaussianSource()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageGaussianSource);

	mObject = vtkImageGaussianSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageGaussianSource *aImageGaussianSource = vtkImageGaussianSource::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Maximum, (0));
	Maximum.setValue(aImageGaussianSource->GetMaximum());

	SO_ENGINE_ADD_INPUT(StandardDeviation, (0));
	StandardDeviation.setValue(aImageGaussianSource->GetStandardDeviation());

	SO_ENGINE_ADD_INPUT(Center, (0,0,0));

	x = aImageGaussianSource->GetCenter();
	Center.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(WholeExtent, ());
	WholeExtent.setFormat("int int int int int int");

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageGaussianSource->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageGaussianSource::~SoVtkImageGaussianSource()
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

void SoVtkImageGaussianSource::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageGaussianSource, SoEngine, "Engine" );
}

void SoVtkImageGaussianSource::evaluate()
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


void SoVtkImageGaussianSource::inputChanged(SoField * f)
{
	// Get the Maximum value
	if ( f == &Maximum )
		SO_VTK_SET_FIELD_VALUE( mObject, Maximum);

	// Get the StandardDeviation value
	if ( f == &StandardDeviation )
		SO_VTK_SET_FIELD_VALUE( mObject, StandardDeviation);

	// Get the Center value
	if ( f == &Center )
		SO_VTK_SET_FIELD_VEC3F( mObject, Center);

	// Get the WholeExtent value
	if ( f == &WholeExtent )
	{
		SbVariant *vWholeExtent = (SbVariant *)WholeExtent.getValues(0);
		SoInput input;
		int nb_fields = WholeExtent.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		int val4;
		int val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vWholeExtent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetWholeExtent( 
				(int) val0,
				(int) val1,
				(int) val2,
				(int) val3,
				(int) val4,
				(int) val5
			);
		}
	}

	mObject->Update();
}

void SoVtkImageGaussianSource::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageGaussianSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Maximum value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Maximum);

	// Get the StandardDeviation value
	
		SO_VTK_SET_FIELD_VALUE( mObject, StandardDeviation);

	// Get the Center value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Center);

	// Get the WholeExtent value
	if (addCalled == 1)
	{
		SbVariant *vWholeExtent = (SbVariant *)WholeExtent.getValues(0);
		SoInput input;
		int nb_fields = WholeExtent.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		int val4;
		int val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vWholeExtent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetWholeExtent( 
				(int) val0,
				(int) val1,
				(int) val2,
				(int) val3,
				(int) val4,
				(int) val5
			);
		}
	}

	mObject->Update();
}
