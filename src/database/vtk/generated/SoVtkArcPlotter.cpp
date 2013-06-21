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
 
 
 
# include "SoVtkArcPlotter.h"
# include "SoVtkUtils.h"

# include "vtkCamera.h"
# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkArcPlotter )

SoVtkArcPlotter::SoVtkArcPlotter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkArcPlotter);

	mObject = vtkArcPlotter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkArcPlotter *aArcPlotter = vtkArcPlotter::New();

	SO_ENGINE_ADD_INPUT(Camera, (0));

	SO_ENGINE_ADD_INPUT(DefaultNormal, (0,0,0));

	float x[3] = {0.0, 0.0, 0.0};
	aArcPlotter->GetDefaultNormal(x);
	DefaultNormal.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Offset, (0));
	Offset.setValue(aArcPlotter->GetOffset());

	SO_ENGINE_ADD_INPUT(UseDefaultNormal, (0));
	UseDefaultNormal.setValue(aArcPlotter->GetUseDefaultNormal());

	SO_ENGINE_ADD_INPUT(Radius, (0));
	Radius.setValue(aArcPlotter->GetRadius());

	SO_ENGINE_ADD_INPUT(Height, (0));
	Height.setValue(aArcPlotter->GetHeight());

	SO_ENGINE_ADD_INPUT(PlotMode, (0));
	PlotMode.setValue(aArcPlotter->GetPlotMode());

	SO_ENGINE_ADD_INPUT(FieldDataArray, (0));
	FieldDataArray.setValue(aArcPlotter->GetFieldDataArray());

	SO_ENGINE_ADD_INPUT(PlotComponent, (0));
	PlotComponent.setValue(aArcPlotter->GetPlotComponent());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aArcPlotter->Delete();

	SO_ENGINE_ADD_OUTPUT( oCamera, SoSFVtkObject );
	mCamera = 0;

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

	addCalled = 0;
}

SoVtkArcPlotter::~SoVtkArcPlotter()
{
	// Deletion of the objects if they exist
	if ( mCamera )
	{
	
		mCamera->unref();
		mCamera = 0;
	}
	
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

void SoVtkArcPlotter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkArcPlotter, SoEngine, "Engine" );
}

void SoVtkArcPlotter::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mCamera )
		{
		
			mCamera->unref();
			mCamera = 0;
		}
		
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

		mObject->GetCamera();
		mCamera = new SoVtkObject();
		mCamera->ref();
		mCamera->setPointer( mObject->GetCamera() );

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
	SO_ENGINE_OUTPUT( oCamera, SoSFVtkObject, setValue( mCamera ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkArcPlotter::inputChanged(SoField * f)
{
	// Get the Camera value
	if ( f == &Camera )
		SO_VTK_SET_FIELD_DATA( mObject, Camera, vtkCamera);

	// Get the DefaultNormal value
	if ( f == &DefaultNormal )
		SO_VTK_SET_FIELD_VEC3F( mObject, DefaultNormal);

	// Get the Offset value
	if ( f == &Offset )
		SO_VTK_SET_FIELD_VALUE( mObject, Offset);

	// Get the UseDefaultNormal value
	if ( f == &UseDefaultNormal )
		SO_VTK_SET_FIELD_VALUE( mObject, UseDefaultNormal);

	// Get the Radius value
	if ( f == &Radius )
		SO_VTK_SET_FIELD_VALUE( mObject, Radius);

	// Get the Height value
	if ( f == &Height )
		SO_VTK_SET_FIELD_VALUE( mObject, Height);

	// Get the PlotMode value
	if ( f == &PlotMode )
		SO_VTK_SET_FIELD_VALUE( mObject, PlotMode);

	// Get the FieldDataArray value
	if ( f == &FieldDataArray )
		SO_VTK_SET_FIELD_VALUE( mObject, FieldDataArray);

	// Get the PlotComponent value
	if ( f == &PlotComponent )
		SO_VTK_SET_FIELD_VALUE( mObject, PlotComponent);

	mObject->Update();
}

void SoVtkArcPlotter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkArcPlotter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Camera value
	
		SO_VTK_SET_FIELD_DATA( mObject, Camera, vtkCamera);

	// Get the DefaultNormal value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, DefaultNormal);

	// Get the Offset value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Offset);

	// Get the UseDefaultNormal value
	
		SO_VTK_SET_FIELD_VALUE( mObject, UseDefaultNormal);

	// Get the Radius value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Radius);

	// Get the Height value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Height);

	// Get the PlotMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, PlotMode);

	// Get the FieldDataArray value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FieldDataArray);

	// Get the PlotComponent value
	
		SO_VTK_SET_FIELD_VALUE( mObject, PlotComponent);

	mObject->Update();
}

