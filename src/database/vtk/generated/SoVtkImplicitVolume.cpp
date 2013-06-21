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
 
 
# include "SoVtkImplicitVolume.h"
# include "SoVtkUtils.h"

# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImplicitVolume )

SoVtkImplicitVolume::SoVtkImplicitVolume()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImplicitVolume);

	mObject = vtkImplicitVolume::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImplicitVolume *aImplicitVolume = vtkImplicitVolume::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(OutGradient, (0,0,0));

	x = aImplicitVolume->GetOutGradient();
	OutGradient.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Volume, (0));

	SO_ENGINE_ADD_INPUT(OutValue, (0));
	OutValue.setValue(aImplicitVolume->GetOutValue());

	aImplicitVolume->Delete();


	SO_ENGINE_ADD_OUTPUT( oVolume, SoSFVtkObject );
	mVolume = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkImplicitVolume::~SoVtkImplicitVolume()
{
	// Deletion of the objects if they exist
	if ( mVolume )
	{
	
		mVolume->unref();
		mVolume = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkImplicitVolume::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImplicitVolume, SoEngine, "Engine" );
}

void SoVtkImplicitVolume::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( mVolume )
		{
		
			mVolume->unref();
			mVolume = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetVolume();
		mVolume = new SoVtkObject();
		mVolume->ref();
		mVolume->setPointer( mObject->GetVolume() );

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oVolume, SoSFVtkObject, setValue( mVolume ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkImplicitVolume::inputChanged(SoField * f)
{
	// Get the OutGradient value
	if ( f == &OutGradient )
		SO_VTK_SET_FIELD_VEC3F( mObject, OutGradient);

	// Get the Volume value
	if ( f == &Volume )
		SO_VTK_SET_FIELD_DATA( mObject, Volume, vtkImageData);

	// Get the OutValue value
	if ( f == &OutValue )
		SO_VTK_SET_FIELD_VALUE( mObject, OutValue);

}

void SoVtkImplicitVolume::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImplicitVolume::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the OutGradient value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, OutGradient);

	// Get the Volume value
	
		SO_VTK_SET_FIELD_DATA( mObject, Volume, vtkImageData);

	// Get the OutValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, OutValue);

}
