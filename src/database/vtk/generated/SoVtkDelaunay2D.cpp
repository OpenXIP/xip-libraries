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
 
 
# include "SoVtkDelaunay2D.h"
# include "SoVtkUtils.h"

# include "vtkAbstractTransform.h"
# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkDelaunay2D )

SoVtkDelaunay2D::SoVtkDelaunay2D()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDelaunay2D);

	mObject = vtkDelaunay2D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkDelaunay2D *aDelaunay2D = vtkDelaunay2D::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Transform, (0));

	SO_ENGINE_ADD_INPUT(Offset, (0));
	Offset.setValue(aDelaunay2D->GetOffset());

	SO_ENGINE_ADD_INPUT(ProjectionPlaneMode, (0));
	ProjectionPlaneMode.setValue(aDelaunay2D->GetProjectionPlaneMode());

	SO_ENGINE_ADD_INPUT(SourceConnection, (0));

	SO_ENGINE_ADD_INPUT(BoundingTriangulation, (0));
	BoundingTriangulation.setValue(aDelaunay2D->GetBoundingTriangulation());

	SO_ENGINE_ADD_INPUT(Source, (0));

	SO_ENGINE_ADD_INPUT(Tolerance, (0));
	Tolerance.setValue(aDelaunay2D->GetTolerance());

	SO_ENGINE_ADD_INPUT(Alpha, (0));
	Alpha.setValue(aDelaunay2D->GetAlpha());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aDelaunay2D->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( oSource, SoSFVtkObject );
	mSource = 0;


	addCalled = 0;
}

SoVtkDelaunay2D::~SoVtkDelaunay2D()
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
	
	if ( mSource )
	{
	
		mSource->unref();
		mSource = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkDelaunay2D::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDelaunay2D, SoEngine, "Engine" );
}

void SoVtkDelaunay2D::evaluate()
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
		
		if ( mSource )
		{
		
			mSource->unref();
			mSource = 0;
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

		mObject->GetSource();
		mSource = new SoVtkObject();
		mSource->ref();
		mSource->setPointer( mObject->GetSource() );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( oSource, SoSFVtkObject, setValue( mSource ) );
}


void SoVtkDelaunay2D::inputChanged(SoField * f)
{
	// Get the Transform value
	if ( f == &Transform )
		SO_VTK_SET_FIELD_DATA( mObject, Transform, vtkAbstractTransform);

	// Get the Offset value
	if ( f == &Offset )
		SO_VTK_SET_FIELD_VALUE( mObject, Offset);

	// Get the ProjectionPlaneMode value
	if ( f == &ProjectionPlaneMode )
		SO_VTK_SET_FIELD_VALUE( mObject, ProjectionPlaneMode);

	// Get the SourceConnection value
	if ( f == &SourceConnection )
		SO_VTK_SET_FIELD_DATA( mObject, SourceConnection, vtkAlgorithmOutput);

	// Get the BoundingTriangulation value
	if ( f == &BoundingTriangulation )
		SO_VTK_SET_FIELD_VALUE( mObject, BoundingTriangulation);

	// Get the Source value
	if ( f == &Source )
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkPolyData);

	// Get the Tolerance value
	if ( f == &Tolerance )
		SO_VTK_SET_FIELD_VALUE( mObject, Tolerance);

	// Get the Alpha value
	if ( f == &Alpha )
		SO_VTK_SET_FIELD_VALUE( mObject, Alpha);

	mObject->Update();
}

void SoVtkDelaunay2D::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkDelaunay2D::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Transform value
	
		SO_VTK_SET_FIELD_DATA( mObject, Transform, vtkAbstractTransform);

	// Get the Offset value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Offset);

	// Get the ProjectionPlaneMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ProjectionPlaneMode);

	// Get the SourceConnection value
	
		SO_VTK_SET_FIELD_DATA( mObject, SourceConnection, vtkAlgorithmOutput);

	// Get the BoundingTriangulation value
	
		SO_VTK_SET_FIELD_VALUE( mObject, BoundingTriangulation);

	// Get the Source value
	
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkPolyData);

	// Get the Tolerance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Tolerance);

	// Get the Alpha value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Alpha);

	mObject->Update();
}
