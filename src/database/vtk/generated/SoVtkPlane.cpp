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

# include "SoVtkPlane.h"
# include "SoVtkUtils.h"

# include "vtkAbstractTransform.h"


SO_ENGINE_SOURCE( SoVtkPlane )

SoVtkPlane::SoVtkPlane()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkPlane);

	mObject = vtkPlane::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkPlane *aPlane = vtkPlane::New();
	double *x;

	SO_ENGINE_ADD_INPUT(Transform, (0));

	SO_ENGINE_ADD_INPUT(Origin, (0,0,0));

	x= aPlane->GetOrigin();
	Origin.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Normal, (0,0,0));

	x= aPlane->GetNormal();
	Normal.setValue(x[0],x[1],x[2]);

	aPlane->Delete();


	SO_ENGINE_ADD_OUTPUT(Output, SoSFVtkObject );
	mOutput = 0;

}

SoVtkPlane::~SoVtkPlane()
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

void SoVtkPlane::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkPlane, SoEngine, "Engine" );
}

void SoVtkPlane::evaluate()
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


void SoVtkPlane::inputChanged(SoField * f)
{
	// Get the Transform value
	if ( f == &Transform )
		SO_VTK_SET_FIELD_DATA( mObject, Transform, vtkAbstractTransform);

	// Get the Origin value
	if ( f == &Origin )
		SO_VTK_SET_FIELD_VEC3F( mObject, Origin);

	// Get the Normal value
	if ( f == &Normal )
		SO_VTK_SET_FIELD_VEC3F( mObject, Normal);

	
}

