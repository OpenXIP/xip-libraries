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
/*
 * \brief
 * \author Sylvain Jaume, Francois Huguet
 */

# include "SoVtkTransform.h"
# include "SoVtkUtils.h"

# include "vtkMatrix4x4.h"
# include "vtkLinearTransform.h"
# include "vtkAbstractTransform.h"


SO_ENGINE_SOURCE( SoVtkTransform )

SoVtkTransform::SoVtkTransform()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkTransform);

	mObject = vtkTransform::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkTransform *aTransform = vtkTransform::New();

	SO_ENGINE_ADD_INPUT(Matrix, (0));

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(Inverse, (0));

	aTransform->Delete();


	SO_ENGINE_ADD_OUTPUT(Output, SoSFVtkObject );
	mOutput = 0;

}

SoVtkTransform::~SoVtkTransform()
{
	// Deletion of the objects if they exist
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

void SoVtkTransform::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkTransform, SoEngine, "Engine" );
}

void SoVtkTransform::evaluate()
{
	try
	{
		// Deletion of the objects if they exist
		if ( mOutput )
		{
		
			mOutput->unref();
			mOutput = 0;
		}
		
		// Get the input type(s)
		SoVtkObject *inputPtr = Input.getValue();
		
		if (inputPtr && inputPtr->getPointer()->IsA("vtkLinearTransform"))
			mObject->SetInput(vtkLinearTransform::SafeDownCast(inputPtr->getPointer()));

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


void SoVtkTransform::inputChanged(SoField * f)
{
	// Get the Matrix value
	if ( f == &Matrix )
		SO_VTK_SET_FIELD_DATA( mObject, Matrix, vtkMatrix4x4);

	// Get the Inverse value
	if ( f == &Inverse )
		SO_VTK_SET_FIELD_DATA( mObject, Inverse, vtkAbstractTransform);

	
}

