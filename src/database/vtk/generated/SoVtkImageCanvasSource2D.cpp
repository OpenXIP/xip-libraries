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
 
 
# include "SoVtkImageCanvasSource2D.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageCanvasSource2D )

SoVtkImageCanvasSource2D::SoVtkImageCanvasSource2D()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageCanvasSource2D);

	mObject = vtkImageCanvasSource2D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageCanvasSource2D *aImageCanvasSource2D = vtkImageCanvasSource2D::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(DrawColor, (0,0,0,0));

	x = aImageCanvasSource2D->GetDrawColor();
	DrawColor.setValue(x[0],x[1],x[2],x[3]);

	SO_ENGINE_ADD_INPUT(NumberOfScalarComponents, (0));
	SO_ENGINE_ADD_INPUT(Ratio, (0,0,0));

	x = aImageCanvasSource2D->GetRatio();
	Ratio.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(DefaultZ, (0));
	DefaultZ.setValue(aImageCanvasSource2D->GetDefaultZ());

	SO_ENGINE_ADD_INPUT(ScalarType, (0));
	SO_ENGINE_ADD_INPUT(Extent, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageCanvasSource2D->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageCanvasSource2D::~SoVtkImageCanvasSource2D()
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

void SoVtkImageCanvasSource2D::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageCanvasSource2D, SoEngine, "Engine" );
}

void SoVtkImageCanvasSource2D::evaluate()
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


void SoVtkImageCanvasSource2D::inputChanged(SoField * f)
{
	// Get the DrawColor value
	if ( f == &DrawColor )
		SO_VTK_SET_FIELD_VEC4F( mObject, DrawColor);

	// Get the NumberOfScalarComponents value
	if ( f == &NumberOfScalarComponents )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfScalarComponents);

	// Get the Ratio value
	if ( f == &Ratio )
		SO_VTK_SET_FIELD_VEC3F( mObject, Ratio);

	// Get the DefaultZ value
	if ( f == &DefaultZ )
		SO_VTK_SET_FIELD_VALUE( mObject, DefaultZ);

	// Get the ScalarType value
	if ( f == &ScalarType )
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarType);

	// Get the Extent value
	if ( f == &Extent )
	{
		if ( Extent.getNum() >= 5)
		{
			SO_VTK_SET_FIELD_MFINT32( mObject, Extent);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 5 values." );
		}
	}

	mObject->Update();
}

void SoVtkImageCanvasSource2D::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageCanvasSource2D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the DrawColor value
	
		SO_VTK_SET_FIELD_VEC4F( mObject, DrawColor);

	// Get the NumberOfScalarComponents value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfScalarComponents);

	// Get the Ratio value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Ratio);

	// Get the DefaultZ value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DefaultZ);

	// Get the ScalarType value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarType);

	// Get the Extent value
	
	{
		if ( Extent.getNum() >= 5)
		{
			SO_VTK_SET_FIELD_MFINT32( mObject, Extent);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 5 values." );
		}
	}

	mObject->Update();
}
