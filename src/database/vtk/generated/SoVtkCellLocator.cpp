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
 
 
# include "SoVtkCellLocator.h"
# include "SoVtkUtils.h"

# include "vtkDataSet.h"


SO_ENGINE_SOURCE( SoVtkCellLocator )

SoVtkCellLocator::SoVtkCellLocator()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkCellLocator);

	mObject = vtkCellLocator::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkCellLocator *aCellLocator = vtkCellLocator::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(DataSet, (0));

	SO_ENGINE_ADD_INPUT(RetainCellLists, (0));
	RetainCellLists.setValue(aCellLocator->GetRetainCellLists());

	SO_ENGINE_ADD_INPUT(CacheCellBounds, (0));
	CacheCellBounds.setValue(aCellLocator->GetCacheCellBounds());

	SO_ENGINE_ADD_INPUT(NumberOfCellsPerBucket, (0));
	NumberOfCellsPerBucket.setValue(aCellLocator->GetNumberOfCellsPerBucket());

	SO_ENGINE_ADD_INPUT(Automatic, (0));
	Automatic.setValue(aCellLocator->GetAutomatic());

	SO_ENGINE_ADD_INPUT(MaxLevel, (0));
	MaxLevel.setValue(aCellLocator->GetMaxLevel());

	SO_ENGINE_ADD_INPUT(Tolerance, (0));
	Tolerance.setValue(aCellLocator->GetTolerance());

	aCellLocator->Delete();


	SO_ENGINE_ADD_OUTPUT( oDataSet, SoSFVtkObject );
	mDataSet = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkCellLocator::~SoVtkCellLocator()
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

void SoVtkCellLocator::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkCellLocator, SoEngine, "Engine" );
}

void SoVtkCellLocator::evaluate()
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


void SoVtkCellLocator::inputChanged(SoField * f)
{
	// Get the DataSet value
	if ( f == &DataSet )
		SO_VTK_SET_FIELD_DATA( mObject, DataSet, vtkDataSet);

	// Get the RetainCellLists value
	if ( f == &RetainCellLists )
		SO_VTK_SET_FIELD_VALUE( mObject, RetainCellLists);

	// Get the CacheCellBounds value
	if ( f == &CacheCellBounds )
		SO_VTK_SET_FIELD_VALUE( mObject, CacheCellBounds);

	// Get the NumberOfCellsPerBucket value
	if ( f == &NumberOfCellsPerBucket )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfCellsPerBucket);

	// Get the Automatic value
	if ( f == &Automatic )
		SO_VTK_SET_FIELD_VALUE( mObject, Automatic);

	// Get the MaxLevel value
	if ( f == &MaxLevel )
		SO_VTK_SET_FIELD_VALUE( mObject, MaxLevel);

	// Get the Tolerance value
	if ( f == &Tolerance )
		SO_VTK_SET_FIELD_VALUE( mObject, Tolerance);

	mObject->Update();
}

void SoVtkCellLocator::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkCellLocator::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the DataSet value
	
		SO_VTK_SET_FIELD_DATA( mObject, DataSet, vtkDataSet);

	// Get the RetainCellLists value
	
		SO_VTK_SET_FIELD_VALUE( mObject, RetainCellLists);

	// Get the CacheCellBounds value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CacheCellBounds);

	// Get the NumberOfCellsPerBucket value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfCellsPerBucket);

	// Get the Automatic value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Automatic);

	// Get the MaxLevel value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaxLevel);

	// Get the Tolerance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Tolerance);

	mObject->Update();
}
