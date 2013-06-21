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

# include "SoVtkSphereSource.h"
# include "SoVtkUtils.h"

# include "vtkDataObject.h"
# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkSphereSource )

SoVtkSphereSource::SoVtkSphereSource()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkSphereSource);

	mObject = vtkSphereSource::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkSphereSource *aSphereSource = vtkSphereSource::New();
	double *x;

	SO_ENGINE_ADD_INPUT(Radius, (0));
	Radius.setValue(aSphereSource->GetRadius());

	SO_ENGINE_ADD_INPUT(PhiResolution, (0));
	PhiResolution.setValue(aSphereSource->GetPhiResolution());

	SO_ENGINE_ADD_INPUT(Center, (0,0,0));

	x= aSphereSource->GetCenter();
	Center.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(ThetaResolution, (0));
	ThetaResolution.setValue(aSphereSource->GetThetaResolution());

	SO_ENGINE_ADD_INPUT(InputArrayToProcess, ());
	InputArrayToProcess.setFormat("int int int int char*");

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aSphereSource->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

}

SoVtkSphereSource::~SoVtkSphereSource()
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

void SoVtkSphereSource::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkSphereSource, SoEngine, "Engine" );
}

void SoVtkSphereSource::evaluate()
{
	try
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
		
		// Get the input type(s)
		SoVtkObject *inputPtr = Input.getValue();
		
		if (inputPtr && inputPtr->getPointer()->IsA("vtkDataObject"))
			mObject->SetInput(vtkDataObject::SafeDownCast(inputPtr->getPointer()));

		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

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


void SoVtkSphereSource::inputChanged(SoField * f)
{
	// Get the Radius value
	if ( f == &Radius )
		SO_VTK_SET_FIELD_VALUE( mObject, Radius);

	// Get the Center value
	if ( f == &Center )
		SO_VTK_SET_FIELD_VEC3F( mObject, Center);

	// Get the ThetaResolution value
	if ( f == &ThetaResolution )
		SO_VTK_SET_FIELD_VALUE( mObject, ThetaResolution);

	// Get the PhiResolution value
	if ( f == &PhiResolution )
		SO_VTK_SET_FIELD_VALUE( mObject, PhiResolution);

	// Get the InputArrayToProcess value
	if ( f == &InputArrayToProcess )
	{
		SbVariant vInputArrayToProcess = (SbVariant)InputArrayToProcess.getValue();
		SoInput input;
		int val0;
		int val1;
		int val2;
		int val3;
		SbString val4;
	
		input.setBuffer((void *)vInputArrayToProcess.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		input.read(val2);
		input.read(val3);
		input.read(val4);
		mObject->SetInputArrayToProcess( 
			(int) val0,
			(int) val1,
			(int) val2,
			(int) val3,
			val4.getString()
		);
	}
	//mObject->Update();
	
}
