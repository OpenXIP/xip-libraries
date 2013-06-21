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
 
 
# include "SoVtkFieldData.h"
# include "SoVtkUtils.h"



SO_ENGINE_SOURCE( SoVtkFieldData )

SoVtkFieldData::SoVtkFieldData()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkFieldData);

	mObject = vtkFieldData::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkFieldData *aFieldData = vtkFieldData::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Component, ());
	Component.setFormat("const vtkIdType const int const double");

	aFieldData->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkFieldData::~SoVtkFieldData()
{
	// Deletion of the objects if they exist
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkFieldData::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkFieldData, SoEngine, "Engine" );
}

void SoVtkFieldData::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkFieldData::inputChanged(SoField * f)
{
	// Get the Component value
	if ( f == &Component )
	{
		SbVariant *vComponent = (SbVariant *)Component.getValues(0);
		SoInput input;
		int nb_fields = Component.getNum();

		vtkIdType val0;
		int val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vComponent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetComponent( 
				(const vtkIdType) val0,
				(const int) val1,
				(const double) val2
			);
		}
	}

}

void SoVtkFieldData::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkFieldData::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the Component value
	if (addCalled == 1)
	{
		SbVariant *vComponent = (SbVariant *)Component.getValues(0);
		SoInput input;
		int nb_fields = Component.getNum();

		vtkIdType val0;
		int val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vComponent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetComponent( 
				(const vtkIdType) val0,
				(const int) val1,
				(const double) val2
			);
		}
	}

}
