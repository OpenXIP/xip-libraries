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
 
 
# include "SoVtkConnectivityFilter.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkUnstructuredGrid.h"


SO_ENGINE_SOURCE( SoVtkConnectivityFilter )

SoVtkConnectivityFilter::SoVtkConnectivityFilter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkConnectivityFilter);

	mObject = vtkConnectivityFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkConnectivityFilter *aConnectivityFilter = vtkConnectivityFilter::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(ScalarRange, (0,0));

	x = aConnectivityFilter->GetScalarRange();
	ScalarRange.setValue(x[0],x[1]);

	SO_ENGINE_ADD_INPUT(ColorRegions, (0));
	ColorRegions.setValue(aConnectivityFilter->GetColorRegions());

	SO_ENGINE_ADD_INPUT(ExtractionMode, (0));
	ExtractionMode.setValue(aConnectivityFilter->GetExtractionMode());

	SO_ENGINE_ADD_INPUT(ClosestPoint, (0,0,0));

	x = aConnectivityFilter->GetClosestPoint();
	ClosestPoint.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(SpecifiedRegion, (0));
	SO_ENGINE_ADD_INPUT(ScalarConnectivity, (0));
	ScalarConnectivity.setValue(aConnectivityFilter->GetScalarConnectivity());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aConnectivityFilter->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkConnectivityFilter::~SoVtkConnectivityFilter()
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

void SoVtkConnectivityFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkConnectivityFilter, SoEngine, "Engine" );
}

void SoVtkConnectivityFilter::evaluate()
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


void SoVtkConnectivityFilter::inputChanged(SoField * f)
{
	// Get the ScalarRange value
	if ( f == &ScalarRange )
		SO_VTK_SET_FIELD_VEC2F( mObject, ScalarRange);

	// Get the ColorRegions value
	if ( f == &ColorRegions )
		SO_VTK_SET_FIELD_VALUE( mObject, ColorRegions);

	// Get the ExtractionMode value
	if ( f == &ExtractionMode )
		SO_VTK_SET_FIELD_VALUE( mObject, ExtractionMode);

	// Get the ClosestPoint value
	if ( f == &ClosestPoint )
		SO_VTK_SET_FIELD_VEC3F( mObject, ClosestPoint);

	// Get the SpecifiedRegion value
	if ( f == &SpecifiedRegion )
		addCalled = 1;
	// Get the ScalarConnectivity value
	if ( f == &ScalarConnectivity )
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarConnectivity);

	mObject->Update();
}

void SoVtkConnectivityFilter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkConnectivityFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the ScalarRange value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, ScalarRange);

	// Get the ColorRegions value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ColorRegions);

	// Get the ExtractionMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ExtractionMode);

	// Get the ClosestPoint value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, ClosestPoint);

	// Get the SpecifiedRegion value
	
		SO_VTK_ADD_FIELD_VALUE( mObject, SpecifiedRegion);

	// Get the ScalarConnectivity value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarConnectivity);

	mObject->Update();
}
