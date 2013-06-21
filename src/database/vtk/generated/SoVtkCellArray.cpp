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
 
 
# include "SoVtkCellArray.h"
# include "SoVtkUtils.h"



SO_ENGINE_SOURCE( SoVtkCellArray )

SoVtkCellArray::SoVtkCellArray()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkCellArray);

	mObject = vtkCellArray::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkCellArray *aCellArray = vtkCellArray::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	aCellArray->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkCellArray::~SoVtkCellArray()
{
	// Deletion of the objects if they exist
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkCellArray::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkCellArray, SoEngine, "Engine" );
}

void SoVtkCellArray::evaluate()
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


void SoVtkCellArray::inputChanged(SoField * f)
{
}

void SoVtkCellArray::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkCellArray::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
}
