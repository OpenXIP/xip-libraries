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
 
 
# include "SoVtkInformation.h"
# include "SoVtkUtils.h"

# include "vtkInformationRequestKey.h"


SO_ENGINE_SOURCE( SoVtkInformation )

SoVtkInformation::SoVtkInformation()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkInformation);

	mObject = vtkInformation::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkInformation *aInformation = vtkInformation::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Request, (0));

	aInformation->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkInformation::~SoVtkInformation()
{
	// Deletion of the objects if they exist
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkInformation::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkInformation, SoEngine, "Engine" );
}

void SoVtkInformation::evaluate()
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


void SoVtkInformation::inputChanged(SoField * f)
{
	// Get the Request value
	if ( f == &Request )
		SO_VTK_SET_FIELD_DATA( mObject, Request, vtkInformationRequestKey);

}

void SoVtkInformation::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkInformation::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the Request value
	
		SO_VTK_SET_FIELD_DATA( mObject, Request, vtkInformationRequestKey);

}
