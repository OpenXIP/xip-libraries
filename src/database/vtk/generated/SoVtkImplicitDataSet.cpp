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
 
 
# include "SoVtkImplicitDataSet.h"
# include "SoVtkUtils.h"

# include "vtkDataSet.h"


SO_ENGINE_SOURCE( SoVtkImplicitDataSet )

SoVtkImplicitDataSet::SoVtkImplicitDataSet()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImplicitDataSet);

	mObject = vtkImplicitDataSet::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImplicitDataSet *aImplicitDataSet = vtkImplicitDataSet::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(OutGradient, (0,0,0));

	x = aImplicitDataSet->GetOutGradient();
	OutGradient.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(DataSet, (0));

	SO_ENGINE_ADD_INPUT(OutValue, (0));
	OutValue.setValue(aImplicitDataSet->GetOutValue());

	aImplicitDataSet->Delete();


	SO_ENGINE_ADD_OUTPUT( oDataSet, SoSFVtkObject );
	mDataSet = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkImplicitDataSet::~SoVtkImplicitDataSet()
{
	// Deletion of the objects if they exist
	if ( mDataSet )
	{
	
		mDataSet->unref();
		mDataSet = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkImplicitDataSet::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImplicitDataSet, SoEngine, "Engine" );
}

void SoVtkImplicitDataSet::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( mDataSet )
		{
		
			mDataSet->unref();
			mDataSet = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetDataSet();
		mDataSet = new SoVtkObject();
		mDataSet->ref();
		mDataSet->setPointer( mObject->GetDataSet() );

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oDataSet, SoSFVtkObject, setValue( mDataSet ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkImplicitDataSet::inputChanged(SoField * f)
{
	// Get the OutGradient value
	if ( f == &OutGradient )
		SO_VTK_SET_FIELD_VEC3F( mObject, OutGradient);

	// Get the DataSet value
	if ( f == &DataSet )
		SO_VTK_SET_FIELD_DATA( mObject, DataSet, vtkDataSet);

	// Get the OutValue value
	if ( f == &OutValue )
		SO_VTK_SET_FIELD_VALUE( mObject, OutValue);

}

void SoVtkImplicitDataSet::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImplicitDataSet::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the OutGradient value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, OutGradient);

	// Get the DataSet value
	
		SO_VTK_SET_FIELD_DATA( mObject, DataSet, vtkDataSet);

	// Get the OutValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, OutValue);

}
