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
 
 
# include "SoVtkGlyphSource2D.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkGlyphSource2D )

SoVtkGlyphSource2D::SoVtkGlyphSource2D()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkGlyphSource2D);

	mObject = vtkGlyphSource2D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkGlyphSource2D *aGlyphSource2D = vtkGlyphSource2D::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(GlyphType, (0));
	GlyphType.setValue(aGlyphSource2D->GetGlyphType());

	SO_ENGINE_ADD_INPUT(Scale2, (0));
	Scale2.setValue(aGlyphSource2D->GetScale2());

	SO_ENGINE_ADD_INPUT(RotationAngle, (0));
	RotationAngle.setValue(aGlyphSource2D->GetRotationAngle());

	SO_ENGINE_ADD_INPUT(Filled, (0));
	Filled.setValue(aGlyphSource2D->GetFilled());

	SO_ENGINE_ADD_INPUT(Center, (0,0,0));

	x = aGlyphSource2D->GetCenter();
	Center.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Scale, (0));
	Scale.setValue(aGlyphSource2D->GetScale());

	SO_ENGINE_ADD_INPUT(Color, (0,0,0));

	x = aGlyphSource2D->GetColor();
	Color.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Cross, (0));
	Cross.setValue(aGlyphSource2D->GetCross());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(Dash, (0));
	Dash.setValue(aGlyphSource2D->GetDash());

	aGlyphSource2D->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkGlyphSource2D::~SoVtkGlyphSource2D()
{
	// Deletion of the objects if they exist
	if ( mOutput )
	{
	
		mOutput->unref();
		mOutput = 0;
	}
	
	if ( mOutputPort )
	{
	
		mOutputPort->unref();
		mOutputPort = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkGlyphSource2D::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkGlyphSource2D, SoEngine, "Engine" );
}

void SoVtkGlyphSource2D::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mOutput )
		{
		
			mOutput->unref();
			mOutput = 0;
		}
		
		if ( mOutputPort )
		{
		
			mOutputPort->unref();
			mOutputPort = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetOutput()->Register(0);
		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject->GetOutput() );

		if ( mObject->GetNumberOfOutputPorts() > 0 )
		{
			mObject->GetOutputPort()->Register(0);
			mOutputPort = new SoVtkAlgorithmOutput();
			mOutputPort->ref();
			mOutputPort->setPointer( mObject->GetOutputPort() );
		}

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkGlyphSource2D::inputChanged(SoField * f)
{
	// Get the GlyphType value
	if ( f == &GlyphType )
		SO_VTK_SET_FIELD_VALUE( mObject, GlyphType);

	// Get the Scale2 value
	if ( f == &Scale2 )
		SO_VTK_SET_FIELD_VALUE( mObject, Scale2);

	// Get the RotationAngle value
	if ( f == &RotationAngle )
		SO_VTK_SET_FIELD_VALUE( mObject, RotationAngle);

	// Get the Filled value
	if ( f == &Filled )
		SO_VTK_SET_FIELD_VALUE( mObject, Filled);

	// Get the Center value
	if ( f == &Center )
		SO_VTK_SET_FIELD_VEC3F( mObject, Center);

	// Get the Scale value
	if ( f == &Scale )
		SO_VTK_SET_FIELD_VALUE( mObject, Scale);

	// Get the Color value
	if ( f == &Color )
		SO_VTK_SET_FIELD_VEC3F( mObject, Color);

	// Get the Cross value
	if ( f == &Cross )
		SO_VTK_SET_FIELD_VALUE( mObject, Cross);

	// Get the Dash value
	if ( f == &Dash )
		SO_VTK_SET_FIELD_VALUE( mObject, Dash);

	mObject->Update();
}

void SoVtkGlyphSource2D::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkGlyphSource2D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the GlyphType value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GlyphType);

	// Get the Scale2 value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Scale2);

	// Get the RotationAngle value
	
		SO_VTK_SET_FIELD_VALUE( mObject, RotationAngle);

	// Get the Filled value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Filled);

	// Get the Center value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Center);

	// Get the Scale value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Scale);

	// Get the Color value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Color);

	// Get the Cross value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Cross);

	// Get the Dash value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Dash);

	mObject->Update();
}
