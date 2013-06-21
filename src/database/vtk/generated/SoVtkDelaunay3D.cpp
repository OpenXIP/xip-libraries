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
 
 
# include "SoVtkDelaunay3D.h"
# include "SoVtkUtils.h"

# include "vtkPointLocator.h"
# include "vtkAlgorithmOutput.h"
# include "vtkUnstructuredGrid.h"


SO_ENGINE_SOURCE( SoVtkDelaunay3D )

SoVtkDelaunay3D::SoVtkDelaunay3D()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDelaunay3D);

	mObject = vtkDelaunay3D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkDelaunay3D *aDelaunay3D = vtkDelaunay3D::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Offset, (0));
	Offset.setValue(aDelaunay3D->GetOffset());

	SO_ENGINE_ADD_INPUT(Locator, (0));

	SO_ENGINE_ADD_INPUT(Tolerance, (0));
	Tolerance.setValue(aDelaunay3D->GetTolerance());

	SO_ENGINE_ADD_INPUT(BoundingTriangulation, (0));
	BoundingTriangulation.setValue(aDelaunay3D->GetBoundingTriangulation());

	SO_ENGINE_ADD_INPUT(Alpha, (0));
	Alpha.setValue(aDelaunay3D->GetAlpha());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aDelaunay3D->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oLocator, SoSFVtkObject );
	mLocator = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkDelaunay3D::~SoVtkDelaunay3D()
{
	// Deletion of the objects if they exist
	if ( mOutput )
	{
	
		mOutput->unref();
		mOutput = 0;
	}
	
	if ( mLocator )
	{
	
		mLocator->unref();
		mLocator = 0;
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

void SoVtkDelaunay3D::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDelaunay3D, SoEngine, "Engine" );
}

void SoVtkDelaunay3D::evaluate()
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
		
		if ( mLocator )
		{
		
			mLocator->unref();
			mLocator = 0;
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

		mObject->GetLocator();
		mLocator = new SoVtkObject();
		mLocator->ref();
		mLocator->setPointer( mObject->GetLocator() );

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
	SO_ENGINE_OUTPUT( oLocator, SoSFVtkObject, setValue( mLocator ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkDelaunay3D::inputChanged(SoField * f)
{
	// Get the Offset value
	if ( f == &Offset )
		SO_VTK_SET_FIELD_VALUE( mObject, Offset);

	// Get the Locator value
	if ( f == &Locator )
		SO_VTK_SET_FIELD_DATA( mObject, Locator, vtkPointLocator);

	// Get the Tolerance value
	if ( f == &Tolerance )
		SO_VTK_SET_FIELD_VALUE( mObject, Tolerance);

	// Get the BoundingTriangulation value
	if ( f == &BoundingTriangulation )
		SO_VTK_SET_FIELD_VALUE( mObject, BoundingTriangulation);

	// Get the Alpha value
	if ( f == &Alpha )
		SO_VTK_SET_FIELD_VALUE( mObject, Alpha);

	mObject->Update();
}

void SoVtkDelaunay3D::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkDelaunay3D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Offset value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Offset);

	// Get the Locator value
	
		SO_VTK_SET_FIELD_DATA( mObject, Locator, vtkPointLocator);

	// Get the Tolerance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Tolerance);

	// Get the BoundingTriangulation value
	
		SO_VTK_SET_FIELD_VALUE( mObject, BoundingTriangulation);

	// Get the Alpha value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Alpha);

	mObject->Update();
}
