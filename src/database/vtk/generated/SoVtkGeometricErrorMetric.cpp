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
 
 
# include "SoVtkGeometricErrorMetric.h"
# include "SoVtkUtils.h"

# include "vtkGenericAdaptorCell.h"
# include "vtkGenericDataSet.h"


SO_ENGINE_SOURCE( SoVtkGeometricErrorMetric )

SoVtkGeometricErrorMetric::SoVtkGeometricErrorMetric()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkGeometricErrorMetric);

	mObject = vtkGeometricErrorMetric::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkGeometricErrorMetric *aGeometricErrorMetric = vtkGeometricErrorMetric::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(GenericCell, (0));

	SO_ENGINE_ADD_INPUT(DataSet, (0));

	SO_ENGINE_ADD_INPUT(AbsoluteGeometricTolerance, (0));
	aGeometricErrorMetric->Delete();


	SO_ENGINE_ADD_OUTPUT( oGenericCell, SoSFVtkObject );
	mGenericCell = 0;
	SO_ENGINE_ADD_OUTPUT( oDataSet, SoSFVtkObject );
	mDataSet = 0;


	addCalled = 0;
}

SoVtkGeometricErrorMetric::~SoVtkGeometricErrorMetric()
{
	// Deletion of the objects if they exist
	if ( mGenericCell )
	{
	
		mGenericCell->unref();
		mGenericCell = 0;
	}
	
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

void SoVtkGeometricErrorMetric::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkGeometricErrorMetric, SoEngine, "Engine" );
}

void SoVtkGeometricErrorMetric::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( mGenericCell )
		{
		
			mGenericCell->unref();
			mGenericCell = 0;
		}
		
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

		mObject->GetGenericCell();
		mGenericCell = new SoVtkObject();
		mGenericCell->ref();
		mGenericCell->setPointer( mObject->GetGenericCell() );

		mObject->GetDataSet();
		mDataSet = new SoVtkObject();
		mDataSet->ref();
		mDataSet->setPointer( mObject->GetDataSet() );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oGenericCell, SoSFVtkObject, setValue( mGenericCell ) );
	SO_ENGINE_OUTPUT( oDataSet, SoSFVtkObject, setValue( mDataSet ) );
}


void SoVtkGeometricErrorMetric::inputChanged(SoField * f)
{
	// Get the GenericCell value
	if ( f == &GenericCell )
		SO_VTK_SET_FIELD_DATA( mObject, GenericCell, vtkGenericAdaptorCell);

	// Get the DataSet value
	if ( f == &DataSet )
		SO_VTK_SET_FIELD_DATA( mObject, DataSet, vtkGenericDataSet);

	// Get the AbsoluteGeometricTolerance value
	if ( f == &AbsoluteGeometricTolerance )
		SO_VTK_SET_FIELD_VALUE( mObject, AbsoluteGeometricTolerance);

}

void SoVtkGeometricErrorMetric::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkGeometricErrorMetric::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the GenericCell value
	
		SO_VTK_SET_FIELD_DATA( mObject, GenericCell, vtkGenericAdaptorCell);

	// Get the DataSet value
	
		SO_VTK_SET_FIELD_DATA( mObject, DataSet, vtkGenericDataSet);

	// Get the AbsoluteGeometricTolerance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AbsoluteGeometricTolerance);

}
