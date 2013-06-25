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
 
 
# include "SoVtkCubeSource.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkCubeSource )

SoVtkCubeSource::SoVtkCubeSource()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkCubeSource);

	mObject = vtkCubeSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkCubeSource *aCubeSource = vtkCubeSource::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Bounds, ());
	Bounds.setFormat("double double double double double double");

	SO_ENGINE_ADD_INPUT(XLength, (0));
	XLength.setValue(aCubeSource->GetXLength());

	SO_ENGINE_ADD_INPUT(Center, (0,0,0));

	x = aCubeSource->GetCenter();
	Center.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(YLength, (0));
	YLength.setValue(aCubeSource->GetYLength());

	SO_ENGINE_ADD_INPUT(ZLength, (0));
	ZLength.setValue(aCubeSource->GetZLength());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aCubeSource->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkCubeSource::~SoVtkCubeSource()
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

void SoVtkCubeSource::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkCubeSource, SoEngine, "Engine" );
}

void SoVtkCubeSource::evaluate()
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


void SoVtkCubeSource::inputChanged(SoField * f)
{
	// Get the Bounds value
	if ( f == &Bounds )
	{
		SbVariant *vBounds = (SbVariant *)Bounds.getValues(0);
		SoInput input;
		int nb_fields = Bounds.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vBounds[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetBounds( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5
			);
		}
	}

	// Get the XLength value
	if ( f == &XLength )
		SO_VTK_SET_FIELD_VALUE( mObject, XLength);

	// Get the Center value
	if ( f == &Center )
		SO_VTK_SET_FIELD_VEC3F( mObject, Center);

	// Get the YLength value
	if ( f == &YLength )
		SO_VTK_SET_FIELD_VALUE( mObject, YLength);

	// Get the ZLength value
	if ( f == &ZLength )
		SO_VTK_SET_FIELD_VALUE( mObject, ZLength);

	mObject->Update();
}

void SoVtkCubeSource::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkCubeSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Bounds value
	if (addCalled == 1)
	{
		SbVariant *vBounds = (SbVariant *)Bounds.getValues(0);
		SoInput input;
		int nb_fields = Bounds.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vBounds[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetBounds( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5
			);
		}
	}

	// Get the XLength value
	
		SO_VTK_SET_FIELD_VALUE( mObject, XLength);

	// Get the Center value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Center);

	// Get the YLength value
	
		SO_VTK_SET_FIELD_VALUE( mObject, YLength);

	// Get the ZLength value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ZLength);

	mObject->Update();
}
