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
 
 
# include "SoVtkCellCenterDepthSort.h"
# include "SoVtkUtils.h"

# include "vtkCamera.h"
# include "vtkMatrix4x4.h"
# include "vtkDataSet.h"


SO_ENGINE_SOURCE( SoVtkCellCenterDepthSort )

SoVtkCellCenterDepthSort::SoVtkCellCenterDepthSort()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkCellCenterDepthSort);

	mObject = vtkCellCenterDepthSort::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkCellCenterDepthSort *aCellCenterDepthSort = vtkCellCenterDepthSort::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Camera, (0));

	SO_ENGINE_ADD_INPUT(ModelTransform, (0));

	SO_ENGINE_ADD_INPUT(MaxCellsReturned, (0));
	MaxCellsReturned.setValue(aCellCenterDepthSort->GetMaxCellsReturned());

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(Direction, (0));
	Direction.setValue(aCellCenterDepthSort->GetDirection());

	aCellCenterDepthSort->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkCellCenterDepthSort::~SoVtkCellCenterDepthSort()
{
	// Deletion of the objects if they exist
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkCellCenterDepthSort::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkCellCenterDepthSort, SoEngine, "Engine" );
}

void SoVtkCellCenterDepthSort::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkObject *inputPtr = Input.getValue();
		
		if (inputPtr && inputPtr->getPointer()->IsA("vtkDataSet"))
			mObject->SetInput(vtkDataSet::SafeDownCast(inputPtr->getPointer()));

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


void SoVtkCellCenterDepthSort::inputChanged(SoField * f)
{
	// Get the Camera value
	if ( f == &Camera )
		SO_VTK_SET_FIELD_DATA( mObject, Camera, vtkCamera);

	// Get the ModelTransform value
	if ( f == &ModelTransform )
		SO_VTK_SET_FIELD_DATA( mObject, ModelTransform, vtkMatrix4x4);

	// Get the MaxCellsReturned value
	if ( f == &MaxCellsReturned )
		SO_VTK_SET_FIELD_VALUE( mObject, MaxCellsReturned);

	// Get the Direction value
	if ( f == &Direction )
		SO_VTK_SET_FIELD_VALUE( mObject, Direction);

}

void SoVtkCellCenterDepthSort::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkCellCenterDepthSort::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkObject *inputPtr = Input.getValue();
	
	if (inputPtr && inputPtr->getPointer()->IsA("vtkDataSet"))
		mObject->SetInput(vtkDataSet::SafeDownCast(inputPtr->getPointer()));

	// Get the Camera value
	
		SO_VTK_SET_FIELD_DATA( mObject, Camera, vtkCamera);

	// Get the ModelTransform value
	
		SO_VTK_SET_FIELD_DATA( mObject, ModelTransform, vtkMatrix4x4);

	// Get the MaxCellsReturned value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaxCellsReturned);

	// Get the Direction value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Direction);

}
