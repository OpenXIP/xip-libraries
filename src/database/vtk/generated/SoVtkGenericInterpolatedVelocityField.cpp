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
 
 
# include "SoVtkGenericInterpolatedVelocityField.h"
# include "SoVtkUtils.h"

# include "vtkGenericAdaptorCell.h"


SO_ENGINE_SOURCE( SoVtkGenericInterpolatedVelocityField )

SoVtkGenericInterpolatedVelocityField::SoVtkGenericInterpolatedVelocityField()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkGenericInterpolatedVelocityField);

	mObject = vtkGenericInterpolatedVelocityField::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkGenericInterpolatedVelocityField *aGenericInterpolatedVelocityField = vtkGenericInterpolatedVelocityField::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Caching, (0));
	Caching.setValue(aGenericInterpolatedVelocityField->GetCaching());

	aGenericInterpolatedVelocityField->Delete();


	SO_ENGINE_ADD_OUTPUT( oLastCell, SoSFVtkObject );
	mLastCell = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkGenericInterpolatedVelocityField::~SoVtkGenericInterpolatedVelocityField()
{
	// Deletion of the objects if they exist
	if ( mLastCell )
	{
	
		mLastCell->unref();
		mLastCell = 0;
	}
	
	if ( mOutput )
	{
	
		mOutput->unref();
		mOutput = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkGenericInterpolatedVelocityField::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkGenericInterpolatedVelocityField, SoEngine, "Engine" );
}

void SoVtkGenericInterpolatedVelocityField::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( mLastCell )
		{
		
			mLastCell->unref();
			mLastCell = 0;
		}
		
		if ( mOutput )
		{
		
			mOutput->unref();
			mOutput = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetLastCell();
		mLastCell = new SoVtkObject();
		mLastCell->ref();
		mLastCell->setPointer( mObject->GetLastCell() );

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oLastCell, SoSFVtkObject, setValue( mLastCell ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkGenericInterpolatedVelocityField::inputChanged(SoField * f)
{
	// Get the Caching value
	if ( f == &Caching )
		SO_VTK_SET_FIELD_VALUE( mObject, Caching);

}

void SoVtkGenericInterpolatedVelocityField::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkGenericInterpolatedVelocityField::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the Caching value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Caching);

}
