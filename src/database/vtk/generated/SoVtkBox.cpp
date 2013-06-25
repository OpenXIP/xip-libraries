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
 * \author Sylvain Jaume <sylvain.jaume@siemens.com>, Francois Huguet
 */

#include "SoVtkBox.h"
#include "SoVtkUtils.h"

SO_ENGINE_SOURCE( SoVtkBox )

SoVtkBox::SoVtkBox()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkBox);

	mObject = vtkBox::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkBox *aBox = vtkBox::New();
	double x[3] = {0.0, 0.0, 0.0};

	SO_ENGINE_ADD_INPUT(Bounds, ());
	Bounds.setFormat("double double double double double double");

	SO_ENGINE_ADD_INPUT(XMin, (0,0,0));

	aBox->GetXMin(x);
	XMin.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(XMax, (0,0,0));

	aBox->GetXMax(x);
	XMax.setValue(x[0],x[1],x[2]);

	aBox->Delete();

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	addCalled = 0;
}

SoVtkBox::~SoVtkBox()
{
	// Deletion of the objects if they exist
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
}

void SoVtkBox::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkBox, SoEngine, "Engine" );
}

void SoVtkBox::evaluate()
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


void SoVtkBox::inputChanged(SoField * f)
{
	// Get the Bounds value
	if ( f == &Bounds )
	{
		SbVariant *vBounds = (SbVariant *)Bounds.getValues(0);
		SoInput input;
		int nb_fields = Bounds.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vBounds[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetBounds( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5
			);
		}
	}

	// Get the XMin value
	if ( f == &XMin )
		SO_VTK_SET_FIELD_VEC3F( mObject, XMin);

	// Get the XMax value
	if ( f == &XMax )
		SO_VTK_SET_FIELD_VEC3F( mObject, XMax);

}

void SoVtkBox::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkBox::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the Bounds value
	if (addCalled == 1)
	{
		SbVariant *vBounds = (SbVariant *)Bounds.getValues(0);
		SoInput input;
		int nb_fields = Bounds.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vBounds[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetBounds( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5
			);
		}
	}

	// Get the XMin value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, XMin);

	// Get the XMax value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, XMax);

}

