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
 
 
# include "SoVtkCardinalSpline.h"
# include "SoVtkUtils.h"



SO_ENGINE_SOURCE( SoVtkCardinalSpline )

SoVtkCardinalSpline::SoVtkCardinalSpline()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkCardinalSpline);

	mObject = vtkCardinalSpline::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkCardinalSpline *aCardinalSpline = vtkCardinalSpline::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(RightConstraint, (0));
	RightConstraint.setValue(aCardinalSpline->GetRightConstraint());

	SO_ENGINE_ADD_INPUT(ParametricRange, ());
	ParametricRange.setFormat("double double");

	SO_ENGINE_ADD_INPUT(RightValue, (0));
	RightValue.setValue(aCardinalSpline->GetRightValue());

	SO_ENGINE_ADD_INPUT(LeftValue, (0));
	LeftValue.setValue(aCardinalSpline->GetLeftValue());

	SO_ENGINE_ADD_INPUT(ClampValue, (0));
	ClampValue.setValue(aCardinalSpline->GetClampValue());

	SO_ENGINE_ADD_INPUT(Closed, (0));
	Closed.setValue(aCardinalSpline->GetClosed());

	SO_ENGINE_ADD_INPUT(LeftConstraint, (0));
	LeftConstraint.setValue(aCardinalSpline->GetLeftConstraint());

	SO_ENGINE_ADD_INPUT(Point, ());
	Point.setFormat("double double");

	aCardinalSpline->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkCardinalSpline::~SoVtkCardinalSpline()
{
	// Deletion of the objects if they exist
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkCardinalSpline::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkCardinalSpline, SoEngine, "Engine" );
}

void SoVtkCardinalSpline::evaluate()
{
	try
	{
		// Get the input type(s)
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


void SoVtkCardinalSpline::inputChanged(SoField * f)
{
	// Get the RightConstraint value
	if ( f == &RightConstraint )
		SO_VTK_SET_FIELD_VALUE( mObject, RightConstraint);

	// Get the ParametricRange value
	if ( f == &ParametricRange )
	{
		SbVariant *vParametricRange = (SbVariant *)ParametricRange.getValues(0);
		SoInput input;
		int nb_fields = ParametricRange.getNum();

		double val0;
		double val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vParametricRange[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetParametricRange( 
				(double) val0,
				(double) val1
			);
		}
	}

	// Get the RightValue value
	if ( f == &RightValue )
		SO_VTK_SET_FIELD_VALUE( mObject, RightValue);

	// Get the LeftValue value
	if ( f == &LeftValue )
		SO_VTK_SET_FIELD_VALUE( mObject, LeftValue);

	// Get the ClampValue value
	if ( f == &ClampValue )
		SO_VTK_SET_FIELD_VALUE( mObject, ClampValue);

	// Get the Closed value
	if ( f == &Closed )
		SO_VTK_SET_FIELD_VALUE( mObject, Closed);

	// Get the LeftConstraint value
	if ( f == &LeftConstraint )
		SO_VTK_SET_FIELD_VALUE( mObject, LeftConstraint);

	// Get the Point value
	if ( f == &Point )
		addCalled = 1;

}

void SoVtkCardinalSpline::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkCardinalSpline::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the RightConstraint value
	
		SO_VTK_SET_FIELD_VALUE( mObject, RightConstraint);

	// Get the ParametricRange value
	if (addCalled == 1)
	{
		SbVariant *vParametricRange = (SbVariant *)ParametricRange.getValues(0);
		SoInput input;
		int nb_fields = ParametricRange.getNum();

		double val0;
		double val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vParametricRange[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetParametricRange( 
				(double) val0,
				(double) val1
			);
		}
	}

	// Get the RightValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, RightValue);

	// Get the LeftValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, LeftValue);

	// Get the ClampValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ClampValue);

	// Get the Closed value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Closed);

	// Get the LeftConstraint value
	
		SO_VTK_SET_FIELD_VALUE( mObject, LeftConstraint);

	// Get the Point value
	if (addCalled == 1)
	{
		SbVariant *vPoint = (SbVariant *)Point.getValues(0);
		SoInput input;
		int nb_fields = Point.getNum();

		double val0;
		double val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vPoint[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->AddPoint( 
				(double) val0,
				(double) val1
			);
		}
	}

}
