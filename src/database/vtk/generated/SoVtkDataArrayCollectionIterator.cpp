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
 
 
# include "SoVtkDataArrayCollectionIterator.h"
# include "SoVtkUtils.h"

# include "vtkCollection.h"
# include "vtkDataArray.h"
# include "vtkObject.h"


SO_ENGINE_SOURCE( SoVtkDataArrayCollectionIterator )

SoVtkDataArrayCollectionIterator::SoVtkDataArrayCollectionIterator()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDataArrayCollectionIterator);

	mObject = vtkDataArrayCollectionIterator::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkDataArrayCollectionIterator *aDataArrayCollectionIterator = vtkDataArrayCollectionIterator::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Collection, (0));

	aDataArrayCollectionIterator->Delete();


	SO_ENGINE_ADD_OUTPUT( oDataArray, SoSFVtkObject );
	mDataArray = 0;
	SO_ENGINE_ADD_OUTPUT( oCurrentObject, SoSFVtkObject );
	mCurrentObject = 0;


	addCalled = 0;
}

SoVtkDataArrayCollectionIterator::~SoVtkDataArrayCollectionIterator()
{
	// Deletion of the objects if they exist
	if ( mDataArray )
	{
	
		mDataArray->unref();
		mDataArray = 0;
	}
	
	if ( mCurrentObject )
	{
	
		mCurrentObject->unref();
		mCurrentObject = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkDataArrayCollectionIterator::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDataArrayCollectionIterator, SoEngine, "Engine" );
}

void SoVtkDataArrayCollectionIterator::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( mDataArray )
		{
		
			mDataArray->unref();
			mDataArray = 0;
		}
		
		if ( mCurrentObject )
		{
		
			mCurrentObject->unref();
			mCurrentObject = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetDataArray();
		mDataArray = new SoVtkObject();
		mDataArray->ref();
		mDataArray->setPointer( mObject->GetDataArray() );

		mObject->GetCurrentObject();
		mCurrentObject = new SoVtkObject();
		mCurrentObject->ref();
		mCurrentObject->setPointer( mObject->GetCurrentObject() );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oDataArray, SoSFVtkObject, setValue( mDataArray ) );
	SO_ENGINE_OUTPUT( oCurrentObject, SoSFVtkObject, setValue( mCurrentObject ) );
}


void SoVtkDataArrayCollectionIterator::inputChanged(SoField * f)
{
	// Get the Collection value
	if ( f == &Collection )
		SO_VTK_SET_FIELD_DATA( mObject, Collection, vtkCollection);

}

void SoVtkDataArrayCollectionIterator::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkDataArrayCollectionIterator::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the Collection value
	
		SO_VTK_SET_FIELD_DATA( mObject, Collection, vtkCollection);

}
