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
 
 
# include "SoVtkCoordinate.h"
# include "SoVtkUtils.h"

# include "vtkViewport.h"
# include "vtkCoordinate.h"


SO_ENGINE_SOURCE( SoVtkCoordinate )

SoVtkCoordinate::SoVtkCoordinate()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkCoordinate);

	mObject = vtkCoordinate::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkCoordinate *aCoordinate = vtkCoordinate::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(CoordinateSystem, (0));
	CoordinateSystem.setValue(aCoordinate->GetCoordinateSystem());

	SO_ENGINE_ADD_INPUT(Value, (0,0,0));

	x = aCoordinate->GetValue();
	Value.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Viewport, (0));

	SO_ENGINE_ADD_INPUT(ReferenceCoordinate, (0));

	aCoordinate->Delete();


	SO_ENGINE_ADD_OUTPUT( oViewport, SoSFVtkObject );
	mViewport = 0;
	SO_ENGINE_ADD_OUTPUT( oReferenceCoordinate, SoSFVtkObject );
	mReferenceCoordinate = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkCoordinate::~SoVtkCoordinate()
{
	// Deletion of the objects if they exist
	if ( mViewport )
	{
	
		mViewport->unref();
		mViewport = 0;
	}
	
	if ( mReferenceCoordinate )
	{
	
		mReferenceCoordinate->unref();
		mReferenceCoordinate = 0;
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

void SoVtkCoordinate::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkCoordinate, SoEngine, "Engine" );
}

void SoVtkCoordinate::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( mViewport )
		{
		
			mViewport->unref();
			mViewport = 0;
		}
		
		if ( mReferenceCoordinate )
		{
		
			mReferenceCoordinate->unref();
			mReferenceCoordinate = 0;
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

		mObject->GetViewport();
		mViewport = new SoVtkObject();
		mViewport->ref();
		mViewport->setPointer( mObject->GetViewport() );

		mObject->GetReferenceCoordinate();
		mReferenceCoordinate = new SoVtkObject();
		mReferenceCoordinate->ref();
		mReferenceCoordinate->setPointer( mObject->GetReferenceCoordinate() );

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oViewport, SoSFVtkObject, setValue( mViewport ) );
	SO_ENGINE_OUTPUT( oReferenceCoordinate, SoSFVtkObject, setValue( mReferenceCoordinate ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkCoordinate::inputChanged(SoField * f)
{
	// Get the CoordinateSystem value
	if ( f == &CoordinateSystem )
		SO_VTK_SET_FIELD_VALUE( mObject, CoordinateSystem);

	// Get the Value value
	if ( f == &Value )
		SO_VTK_SET_FIELD_VEC3F( mObject, Value);

	// Get the Viewport value
	if ( f == &Viewport )
		SO_VTK_SET_FIELD_DATA( mObject, Viewport, vtkViewport);

	// Get the ReferenceCoordinate value
	if ( f == &ReferenceCoordinate )
		SO_VTK_SET_FIELD_DATA( mObject, ReferenceCoordinate, vtkCoordinate);

}

void SoVtkCoordinate::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkCoordinate::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the CoordinateSystem value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CoordinateSystem);

	// Get the Value value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Value);

	// Get the Viewport value
	
		SO_VTK_SET_FIELD_DATA( mObject, Viewport, vtkViewport);

	// Get the ReferenceCoordinate value
	
		SO_VTK_SET_FIELD_DATA( mObject, ReferenceCoordinate, vtkCoordinate);

}
