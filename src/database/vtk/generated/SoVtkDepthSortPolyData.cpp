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
 
 
# include "SoVtkDepthSortPolyData.h"
# include "SoVtkUtils.h"

# include "vtkCamera.h"
# include "vtkProp3D.h"
# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkDepthSortPolyData )

SoVtkDepthSortPolyData::SoVtkDepthSortPolyData()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDepthSortPolyData);

	mObject = vtkDepthSortPolyData::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkDepthSortPolyData *aDepthSortPolyData = vtkDepthSortPolyData::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Camera, (0));

	SO_ENGINE_ADD_INPUT(Vector, (0,0,0));

	x = aDepthSortPolyData->GetVector();
	Vector.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Direction, (0));
	Direction.setValue(aDepthSortPolyData->GetDirection());

	SO_ENGINE_ADD_INPUT(DepthSortMode, (0));
	DepthSortMode.setValue(aDepthSortPolyData->GetDepthSortMode());

	SO_ENGINE_ADD_INPUT(Origin, (0,0,0));

	x = aDepthSortPolyData->GetOrigin();
	Origin.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Prop3D, (0));

	SO_ENGINE_ADD_INPUT(SortScalars, (0));
	SortScalars.setValue(aDepthSortPolyData->GetSortScalars());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aDepthSortPolyData->Delete();


	SO_ENGINE_ADD_OUTPUT( oCamera, SoSFVtkObject );
	mCamera = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( oProp3D, SoSFVtkObject );
	mProp3D = 0;


	addCalled = 0;
}

SoVtkDepthSortPolyData::~SoVtkDepthSortPolyData()
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
	
	if ( mProp3D )
	{
	
		mProp3D->unref();
		mProp3D = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkDepthSortPolyData::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDepthSortPolyData, SoEngine, "Engine" );
}

void SoVtkDepthSortPolyData::evaluate()
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
		
		if ( mProp3D )
		{
		
			mProp3D->unref();
			mProp3D = 0;
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

		mObject->GetProp3D();
		mProp3D = new SoVtkObject();
		mProp3D->ref();
		mProp3D->setPointer( mObject->GetProp3D() );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oCamera, SoSFVtkObject, setValue( mCamera ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( oProp3D, SoSFVtkObject, setValue( mProp3D ) );
}


void SoVtkDepthSortPolyData::inputChanged(SoField * f)
{
	// Get the Camera value
	if ( f == &Camera )
		SO_VTK_SET_FIELD_DATA( mObject, Camera, vtkCamera);

	// Get the Vector value
	if ( f == &Vector )
		SO_VTK_SET_FIELD_VEC3F( mObject, Vector);

	// Get the Direction value
	if ( f == &Direction )
		SO_VTK_SET_FIELD_VALUE( mObject, Direction);

	// Get the DepthSortMode value
	if ( f == &DepthSortMode )
		SO_VTK_SET_FIELD_VALUE( mObject, DepthSortMode);

	// Get the Origin value
	if ( f == &Origin )
		SO_VTK_SET_FIELD_VEC3F( mObject, Origin);

	// Get the Prop3D value
	if ( f == &Prop3D )
		SO_VTK_SET_FIELD_DATA( mObject, Prop3D, vtkProp3D);

	// Get the SortScalars value
	if ( f == &SortScalars )
		SO_VTK_SET_FIELD_VALUE( mObject, SortScalars);

	mObject->Update();
}

void SoVtkDepthSortPolyData::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkDepthSortPolyData::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Camera value
	
		SO_VTK_SET_FIELD_DATA( mObject, Camera, vtkCamera);

	// Get the Vector value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Vector);

	// Get the Direction value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Direction);

	// Get the DepthSortMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DepthSortMode);

	// Get the Origin value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Origin);

	// Get the Prop3D value
	
		SO_VTK_SET_FIELD_DATA( mObject, Prop3D, vtkProp3D);

	// Get the SortScalars value
	
		SO_VTK_SET_FIELD_VALUE( mObject, SortScalars);

	mObject->Update();
}
