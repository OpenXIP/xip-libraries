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

# include "SoVtkVolumeRayCastMIPFunction.h"
# include "SoVtkUtils.h"



SO_ENGINE_SOURCE( SoVtkVolumeRayCastMIPFunction )

SoVtkVolumeRayCastMIPFunction::SoVtkVolumeRayCastMIPFunction()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkVolumeRayCastMIPFunction);

	mObject = vtkVolumeRayCastMIPFunction::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkVolumeRayCastMIPFunction *aVolumeRayCastMIPFunction = vtkVolumeRayCastMIPFunction::New();

	SO_ENGINE_ADD_INPUT(MaximizeMethod, (0));
	MaximizeMethod.setValue(aVolumeRayCastMIPFunction->GetMaximizeMethod());

	aVolumeRayCastMIPFunction->Delete();


	SO_ENGINE_ADD_OUTPUT(Output, SoSFVtkObject );
	mOutput = 0;

}

SoVtkVolumeRayCastMIPFunction::~SoVtkVolumeRayCastMIPFunction()
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

void SoVtkVolumeRayCastMIPFunction::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkVolumeRayCastMIPFunction, SoEngine, "Engine" );
}

void SoVtkVolumeRayCastMIPFunction::evaluate()
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


void SoVtkVolumeRayCastMIPFunction::inputChanged(SoField * f)
{
	// Get the MaximizeMethod value
	if ( f == &MaximizeMethod )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximizeMethod);

	
}

