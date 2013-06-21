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
 
 
# include "SoVtkImageEllipsoidSource.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageEllipsoidSource )

SoVtkImageEllipsoidSource::SoVtkImageEllipsoidSource()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageEllipsoidSource);

	mObject = vtkImageEllipsoidSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageEllipsoidSource *aImageEllipsoidSource = vtkImageEllipsoidSource::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Radius, (0,0,0));

	x = aImageEllipsoidSource->GetRadius();
	Radius.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(OutputScalarType, (0));
	OutputScalarType.setValue(aImageEllipsoidSource->GetOutputScalarType());

	SO_ENGINE_ADD_INPUT(OutValue, (0));
	OutValue.setValue(aImageEllipsoidSource->GetOutValue());

	SO_ENGINE_ADD_INPUT(InValue, (0));
	InValue.setValue(aImageEllipsoidSource->GetInValue());

	SO_ENGINE_ADD_INPUT(Center, (0,0,0));

	x = aImageEllipsoidSource->GetCenter();
	Center.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(WholeExtent, ());
	WholeExtent.setFormat("int int int int int int");

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageEllipsoidSource->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageEllipsoidSource::~SoVtkImageEllipsoidSource()
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

void SoVtkImageEllipsoidSource::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageEllipsoidSource, SoEngine, "Engine" );
}

void SoVtkImageEllipsoidSource::evaluate()
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


void SoVtkImageEllipsoidSource::inputChanged(SoField * f)
{
	// Get the Radius value
	if ( f == &Radius )
		SO_VTK_SET_FIELD_VEC3F( mObject, Radius);

	// Get the OutputScalarType value
	if ( f == &OutputScalarType )
		SO_VTK_SET_FIELD_VALUE( mObject, OutputScalarType);

	// Get the OutValue value
	if ( f == &OutValue )
		SO_VTK_SET_FIELD_VALUE( mObject, OutValue);

	// Get the InValue value
	if ( f == &InValue )
		SO_VTK_SET_FIELD_VALUE( mObject, InValue);

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

void SoVtkImageEllipsoidSource::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageEllipsoidSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Radius value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Radius);

	// Get the OutputScalarType value
	
		SO_VTK_SET_FIELD_VALUE( mObject, OutputScalarType);

	// Get the OutValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, OutValue);

	// Get the InValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InValue);

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
