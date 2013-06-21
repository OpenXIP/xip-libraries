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
 
 
# include "SoVtkImageSinusoidSource.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageSinusoidSource )

SoVtkImageSinusoidSource::SoVtkImageSinusoidSource()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageSinusoidSource);

	mObject = vtkImageSinusoidSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageSinusoidSource *aImageSinusoidSource = vtkImageSinusoidSource::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Amplitude, (0));
	Amplitude.setValue(aImageSinusoidSource->GetAmplitude());

	SO_ENGINE_ADD_INPUT(Phase, (0));
	Phase.setValue(aImageSinusoidSource->GetPhase());

	SO_ENGINE_ADD_INPUT(Direction, ());
	Direction.setFormat("double double double");

	SO_ENGINE_ADD_INPUT(Period, (0));
	Period.setValue(aImageSinusoidSource->GetPeriod());

	SO_ENGINE_ADD_INPUT(WholeExtent, ());
	WholeExtent.setFormat("int int int int int int");

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageSinusoidSource->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageSinusoidSource::~SoVtkImageSinusoidSource()
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

void SoVtkImageSinusoidSource::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageSinusoidSource, SoEngine, "Engine" );
}

void SoVtkImageSinusoidSource::evaluate()
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


void SoVtkImageSinusoidSource::inputChanged(SoField * f)
{
	// Get the Amplitude value
	if ( f == &Amplitude )
		SO_VTK_SET_FIELD_VALUE( mObject, Amplitude);

	// Get the Phase value
	if ( f == &Phase )
		SO_VTK_SET_FIELD_VALUE( mObject, Phase);

	// Get the Direction value
	if ( f == &Direction )
	{
		SbVariant *vDirection = (SbVariant *)Direction.getValues(0);
		SoInput input;
		int nb_fields = Direction.getNum();

		double val0;
		double val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vDirection[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetDirection( 
				(double) val0,
				(double) val1,
				(double) val2
			);
		}
	}

	// Get the Period value
	if ( f == &Period )
		SO_VTK_SET_FIELD_VALUE( mObject, Period);

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

void SoVtkImageSinusoidSource::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageSinusoidSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Amplitude value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Amplitude);

	// Get the Phase value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Phase);

	// Get the Direction value
	if (addCalled == 1)
	{
		SbVariant *vDirection = (SbVariant *)Direction.getValues(0);
		SoInput input;
		int nb_fields = Direction.getNum();

		double val0;
		double val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vDirection[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetDirection( 
				(double) val0,
				(double) val1,
				(double) val2
			);
		}
	}

	// Get the Period value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Period);

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
