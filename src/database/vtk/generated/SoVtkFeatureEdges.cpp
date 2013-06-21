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
 
 
# include "SoVtkFeatureEdges.h"
# include "SoVtkUtils.h"

# include "vtkPointLocator.h"
# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkFeatureEdges )

SoVtkFeatureEdges::SoVtkFeatureEdges()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkFeatureEdges);

	mObject = vtkFeatureEdges::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkFeatureEdges *aFeatureEdges = vtkFeatureEdges::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(NonManifoldEdges, (0));
	NonManifoldEdges.setValue(aFeatureEdges->GetNonManifoldEdges());

	SO_ENGINE_ADD_INPUT(FeatureEdges, (0));
	FeatureEdges.setValue(aFeatureEdges->GetFeatureEdges());

	SO_ENGINE_ADD_INPUT(BoundaryEdges, (0));
	BoundaryEdges.setValue(aFeatureEdges->GetBoundaryEdges());

	SO_ENGINE_ADD_INPUT(Locator, (0));

	SO_ENGINE_ADD_INPUT(ManifoldEdges, (0));
	ManifoldEdges.setValue(aFeatureEdges->GetManifoldEdges());

	SO_ENGINE_ADD_INPUT(FeatureAngle, (0));
	FeatureAngle.setValue(aFeatureEdges->GetFeatureAngle());

	SO_ENGINE_ADD_INPUT(Coloring, (0));
	Coloring.setValue(aFeatureEdges->GetColoring());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aFeatureEdges->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oLocator, SoSFVtkObject );
	mLocator = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkFeatureEdges::~SoVtkFeatureEdges()
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

void SoVtkFeatureEdges::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkFeatureEdges, SoEngine, "Engine" );
}

void SoVtkFeatureEdges::evaluate()
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


void SoVtkFeatureEdges::inputChanged(SoField * f)
{
	// Get the NonManifoldEdges value
	if ( f == &NonManifoldEdges )
		SO_VTK_SET_FIELD_VALUE( mObject, NonManifoldEdges);

	// Get the FeatureEdges value
	if ( f == &FeatureEdges )
		SO_VTK_SET_FIELD_VALUE( mObject, FeatureEdges);

	// Get the BoundaryEdges value
	if ( f == &BoundaryEdges )
		SO_VTK_SET_FIELD_VALUE( mObject, BoundaryEdges);

	// Get the Locator value
	if ( f == &Locator )
		SO_VTK_SET_FIELD_DATA( mObject, Locator, vtkPointLocator);

	// Get the ManifoldEdges value
	if ( f == &ManifoldEdges )
		SO_VTK_SET_FIELD_VALUE( mObject, ManifoldEdges);

	// Get the FeatureAngle value
	if ( f == &FeatureAngle )
		SO_VTK_SET_FIELD_VALUE( mObject, FeatureAngle);

	// Get the Coloring value
	if ( f == &Coloring )
		SO_VTK_SET_FIELD_VALUE( mObject, Coloring);

	mObject->Update();
}

void SoVtkFeatureEdges::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkFeatureEdges::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the NonManifoldEdges value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NonManifoldEdges);

	// Get the FeatureEdges value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FeatureEdges);

	// Get the BoundaryEdges value
	
		SO_VTK_SET_FIELD_VALUE( mObject, BoundaryEdges);

	// Get the Locator value
	
		SO_VTK_SET_FIELD_DATA( mObject, Locator, vtkPointLocator);

	// Get the ManifoldEdges value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ManifoldEdges);

	// Get the FeatureAngle value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FeatureAngle);

	// Get the Coloring value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Coloring);

	mObject->Update();
}
