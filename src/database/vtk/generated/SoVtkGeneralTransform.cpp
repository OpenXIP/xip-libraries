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
 
 
# include "SoVtkGeneralTransform.h"
# include "SoVtkUtils.h"

# include "vtkAbstractTransform.h"


SO_ENGINE_SOURCE( SoVtkGeneralTransform )

SoVtkGeneralTransform::SoVtkGeneralTransform()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkGeneralTransform);

	mObject = vtkGeneralTransform::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkGeneralTransform *aGeneralTransform = vtkGeneralTransform::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Inverse, (0));

	aGeneralTransform->Delete();


	SO_ENGINE_ADD_OUTPUT( oInverse, SoSFVtkObject );
	mInverse = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkGeneralTransform::~SoVtkGeneralTransform()
{
	// Deletion of the objects if they exist
	if ( mInverse )
	{
	
		mInverse->unref();
		mInverse = 0;
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

void SoVtkGeneralTransform::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkGeneralTransform, SoEngine, "Engine" );
}

void SoVtkGeneralTransform::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( mInverse )
		{
		
			mInverse->unref();
			mInverse = 0;
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

		mObject->GetInverse();
		mInverse = new SoVtkObject();
		mInverse->ref();
		mInverse->setPointer( mObject->GetInverse() );

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oInverse, SoSFVtkObject, setValue( mInverse ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkGeneralTransform::inputChanged(SoField * f)
{
	// Get the Inverse value
	if ( f == &Inverse )
		SO_VTK_SET_FIELD_DATA( mObject, Inverse, vtkAbstractTransform);

}

void SoVtkGeneralTransform::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkGeneralTransform::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the Inverse value
	
		SO_VTK_SET_FIELD_DATA( mObject, Inverse, vtkAbstractTransform);

}
