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
 
 
# include "SoVtkExtractPolyDataGeometry.h"
# include "SoVtkUtils.h"

# include "vtkImplicitFunction.h"
# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkExtractPolyDataGeometry )

SoVtkExtractPolyDataGeometry::SoVtkExtractPolyDataGeometry()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkExtractPolyDataGeometry);

	mObject = vtkExtractPolyDataGeometry::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkExtractPolyDataGeometry *aExtractPolyDataGeometry = vtkExtractPolyDataGeometry::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(ExtractInside, (0));
	ExtractInside.setValue(aExtractPolyDataGeometry->GetExtractInside());

	SO_ENGINE_ADD_INPUT(ImplicitFunction, (0));

	SO_ENGINE_ADD_INPUT(ExtractBoundaryCells, (0));
	ExtractBoundaryCells.setValue(aExtractPolyDataGeometry->GetExtractBoundaryCells());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aExtractPolyDataGeometry->Delete();


	SO_ENGINE_ADD_OUTPUT( oImplicitFunction, SoSFVtkObject );
	mImplicitFunction = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkExtractPolyDataGeometry::~SoVtkExtractPolyDataGeometry()
{
	// Deletion of the objects if they exist
	if ( mImplicitFunction )
	{
	
		mImplicitFunction->unref();
		mImplicitFunction = 0;
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

void SoVtkExtractPolyDataGeometry::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkExtractPolyDataGeometry, SoEngine, "Engine" );
}

void SoVtkExtractPolyDataGeometry::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mImplicitFunction )
		{
		
			mImplicitFunction->unref();
			mImplicitFunction = 0;
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

		mObject->GetImplicitFunction();
		mImplicitFunction = new SoVtkObject();
		mImplicitFunction->ref();
		mImplicitFunction->setPointer( mObject->GetImplicitFunction() );

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
	SO_ENGINE_OUTPUT( oImplicitFunction, SoSFVtkObject, setValue( mImplicitFunction ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkExtractPolyDataGeometry::inputChanged(SoField * f)
{
	// Get the ExtractInside value
	if ( f == &ExtractInside )
		SO_VTK_SET_FIELD_VALUE( mObject, ExtractInside);

	// Get the ImplicitFunction value
	if ( f == &ImplicitFunction )
		SO_VTK_SET_FIELD_DATA( mObject, ImplicitFunction, vtkImplicitFunction);

	// Get the ExtractBoundaryCells value
	if ( f == &ExtractBoundaryCells )
		SO_VTK_SET_FIELD_VALUE( mObject, ExtractBoundaryCells);

	mObject->Update();
}

void SoVtkExtractPolyDataGeometry::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkExtractPolyDataGeometry::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the ExtractInside value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ExtractInside);

	// Get the ImplicitFunction value
	
		SO_VTK_SET_FIELD_DATA( mObject, ImplicitFunction, vtkImplicitFunction);

	// Get the ExtractBoundaryCells value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ExtractBoundaryCells);

	mObject->Update();
}
