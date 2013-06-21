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
 
 
# include "SoVtkCutMaterial.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkCutMaterial )

SoVtkCutMaterial::SoVtkCutMaterial()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkCutMaterial);

	mObject = vtkCutMaterial::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkCutMaterial *aCutMaterial = vtkCutMaterial::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(ArrayName, (""));

	SO_ENGINE_ADD_INPUT(Material, (0));
	Material.setValue(aCutMaterial->GetMaterial());

	SO_ENGINE_ADD_INPUT(MaterialArrayName, (""));

	SO_ENGINE_ADD_INPUT(UpVector, (0,0,0));

	x = aCutMaterial->GetUpVector();
	UpVector.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aCutMaterial->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkCutMaterial::~SoVtkCutMaterial()
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

void SoVtkCutMaterial::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkCutMaterial, SoEngine, "Engine" );
}

void SoVtkCutMaterial::evaluate()
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


void SoVtkCutMaterial::inputChanged(SoField * f)
{
	// Get the ArrayName value
	if ( f == &ArrayName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, ArrayName);

	// Get the Material value
	if ( f == &Material )
		SO_VTK_SET_FIELD_VALUE( mObject, Material);

	// Get the MaterialArrayName value
	if ( f == &MaterialArrayName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, MaterialArrayName);

	// Get the UpVector value
	if ( f == &UpVector )
		SO_VTK_SET_FIELD_VEC3F( mObject, UpVector);

	mObject->Update();
}

void SoVtkCutMaterial::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkCutMaterial::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the ArrayName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, ArrayName);

	// Get the Material value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Material);

	// Get the MaterialArrayName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, MaterialArrayName);

	// Get the UpVector value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, UpVector);

	mObject->Update();
}
