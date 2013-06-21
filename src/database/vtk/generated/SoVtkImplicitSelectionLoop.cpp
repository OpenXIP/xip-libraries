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
 
 
# include "SoVtkImplicitSelectionLoop.h"
# include "SoVtkUtils.h"

# include "vtkPoints.h"


SO_ENGINE_SOURCE( SoVtkImplicitSelectionLoop )

SoVtkImplicitSelectionLoop::SoVtkImplicitSelectionLoop()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImplicitSelectionLoop);

	mObject = vtkImplicitSelectionLoop::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImplicitSelectionLoop *aImplicitSelectionLoop = vtkImplicitSelectionLoop::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(AutomaticNormalGeneration, (0));
	AutomaticNormalGeneration.setValue(aImplicitSelectionLoop->GetAutomaticNormalGeneration());

	SO_ENGINE_ADD_INPUT(Loop, (0));

	SO_ENGINE_ADD_INPUT(Normal, (0,0,0));

	x = aImplicitSelectionLoop->GetNormal();
	Normal.setValue(x[0],x[1],x[2]);

	aImplicitSelectionLoop->Delete();


	SO_ENGINE_ADD_OUTPUT( oLoop, SoSFVtkObject );
	mLoop = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkImplicitSelectionLoop::~SoVtkImplicitSelectionLoop()
{
	// Deletion of the objects if they exist
	if ( mLoop )
	{
	
		mLoop->unref();
		mLoop = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkImplicitSelectionLoop::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImplicitSelectionLoop, SoEngine, "Engine" );
}

void SoVtkImplicitSelectionLoop::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( mLoop )
		{
		
			mLoop->unref();
			mLoop = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetLoop();
		mLoop = new SoVtkObject();
		mLoop->ref();
		mLoop->setPointer( mObject->GetLoop() );

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oLoop, SoSFVtkObject, setValue( mLoop ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkImplicitSelectionLoop::inputChanged(SoField * f)
{
	// Get the AutomaticNormalGeneration value
	if ( f == &AutomaticNormalGeneration )
		SO_VTK_SET_FIELD_VALUE( mObject, AutomaticNormalGeneration);

	// Get the Loop value
	if ( f == &Loop )
		SO_VTK_SET_FIELD_DATA( mObject, Loop, vtkPoints);

	// Get the Normal value
	if ( f == &Normal )
		SO_VTK_SET_FIELD_VEC3F( mObject, Normal);

}

void SoVtkImplicitSelectionLoop::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImplicitSelectionLoop::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the AutomaticNormalGeneration value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AutomaticNormalGeneration);

	// Get the Loop value
	
		SO_VTK_SET_FIELD_DATA( mObject, Loop, vtkPoints);

	// Get the Normal value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Normal);

}
