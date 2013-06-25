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
 
 
# include "SoVtkGridTransform.h"
# include "SoVtkUtils.h"

# include "vtkImageData.h"
# include "vtkAbstractTransform.h"


SO_ENGINE_SOURCE( SoVtkGridTransform )

SoVtkGridTransform::SoVtkGridTransform()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkGridTransform);

	mObject = vtkGridTransform::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkGridTransform *aGridTransform = vtkGridTransform::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(DisplacementScale, (0));
	DisplacementScale.setValue(aGridTransform->GetDisplacementScale());

	SO_ENGINE_ADD_INPUT(DisplacementGrid, (0));

	SO_ENGINE_ADD_INPUT(InverseIterations, (0));
	InverseIterations.setValue(aGridTransform->GetInverseIterations());

	SO_ENGINE_ADD_INPUT(DisplacementShift, (0));
	DisplacementShift.setValue(aGridTransform->GetDisplacementShift());

	SO_ENGINE_ADD_INPUT(InverseTolerance, (0));
	InverseTolerance.setValue(aGridTransform->GetInverseTolerance());

	SO_ENGINE_ADD_INPUT(Inverse, (0));

	SO_ENGINE_ADD_INPUT(InterpolationMode, (0));
	aGridTransform->Delete();


	SO_ENGINE_ADD_OUTPUT( oDisplacementGrid, SoSFVtkObject );
	mDisplacementGrid = 0;
	SO_ENGINE_ADD_OUTPUT( oInverse, SoSFVtkObject );
	mInverse = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkGridTransform::~SoVtkGridTransform()
{
	// Deletion of the objects if they exist
	if ( mDisplacementGrid )
	{
	
		mDisplacementGrid->unref();
		mDisplacementGrid = 0;
	}
	
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

void SoVtkGridTransform::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkGridTransform, SoEngine, "Engine" );
}

void SoVtkGridTransform::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( mDisplacementGrid )
		{
		
			mDisplacementGrid->unref();
			mDisplacementGrid = 0;
		}
		
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

		mObject->GetDisplacementGrid();
		mDisplacementGrid = new SoVtkObject();
		mDisplacementGrid->ref();
		mDisplacementGrid->setPointer( mObject->GetDisplacementGrid() );

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
	SO_ENGINE_OUTPUT( oDisplacementGrid, SoSFVtkObject, setValue( mDisplacementGrid ) );
	SO_ENGINE_OUTPUT( oInverse, SoSFVtkObject, setValue( mInverse ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkGridTransform::inputChanged(SoField * f)
{
	// Get the DisplacementScale value
	if ( f == &DisplacementScale )
		SO_VTK_SET_FIELD_VALUE( mObject, DisplacementScale);

	// Get the DisplacementGrid value
	if ( f == &DisplacementGrid )
		SO_VTK_SET_FIELD_DATA( mObject, DisplacementGrid, vtkImageData);

	// Get the InverseIterations value
	if ( f == &InverseIterations )
		SO_VTK_SET_FIELD_VALUE( mObject, InverseIterations);

	// Get the DisplacementShift value
	if ( f == &DisplacementShift )
		SO_VTK_SET_FIELD_VALUE( mObject, DisplacementShift);

	// Get the InverseTolerance value
	if ( f == &InverseTolerance )
		SO_VTK_SET_FIELD_VALUE( mObject, InverseTolerance);

	// Get the Inverse value
	if ( f == &Inverse )
		SO_VTK_SET_FIELD_DATA( mObject, Inverse, vtkAbstractTransform);

	// Get the InterpolationMode value
	if ( f == &InterpolationMode )
		SO_VTK_SET_FIELD_VALUE( mObject, InterpolationMode);

}

void SoVtkGridTransform::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkGridTransform::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the DisplacementScale value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DisplacementScale);

	// Get the DisplacementGrid value
	
		SO_VTK_SET_FIELD_DATA( mObject, DisplacementGrid, vtkImageData);

	// Get the InverseIterations value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InverseIterations);

	// Get the DisplacementShift value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DisplacementShift);

	// Get the InverseTolerance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InverseTolerance);

	// Get the Inverse value
	
		SO_VTK_SET_FIELD_DATA( mObject, Inverse, vtkAbstractTransform);

	// Get the InterpolationMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InterpolationMode);

}
