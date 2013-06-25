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
 
 
# include "SoVtkDecimatePro.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkDecimatePro )

SoVtkDecimatePro::SoVtkDecimatePro()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDecimatePro);

	mObject = vtkDecimatePro::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkDecimatePro *aDecimatePro = vtkDecimatePro::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(AbsoluteError, (0));
	AbsoluteError.setValue(aDecimatePro->GetAbsoluteError());

	SO_ENGINE_ADD_INPUT(Splitting, (0));
	Splitting.setValue(aDecimatePro->GetSplitting());

	SO_ENGINE_ADD_INPUT(AccumulateError, (0));
	AccumulateError.setValue(aDecimatePro->GetAccumulateError());

	SO_ENGINE_ADD_INPUT(InflectionPointRatio, (0));
	InflectionPointRatio.setValue(aDecimatePro->GetInflectionPointRatio());

	SO_ENGINE_ADD_INPUT(MaximumError, (0));
	MaximumError.setValue(aDecimatePro->GetMaximumError());

	SO_ENGINE_ADD_INPUT(ErrorIsAbsolute, (0));
	ErrorIsAbsolute.setValue(aDecimatePro->GetErrorIsAbsolute());

	SO_ENGINE_ADD_INPUT(TargetReduction, (0));
	TargetReduction.setValue(aDecimatePro->GetTargetReduction());

	SO_ENGINE_ADD_INPUT(BoundaryVertexDeletion, (0));
	BoundaryVertexDeletion.setValue(aDecimatePro->GetBoundaryVertexDeletion());

	SO_ENGINE_ADD_INPUT(PreserveTopology, (0));
	PreserveTopology.setValue(aDecimatePro->GetPreserveTopology());

	SO_ENGINE_ADD_INPUT(PreSplitMesh, (0));
	PreSplitMesh.setValue(aDecimatePro->GetPreSplitMesh());

	SO_ENGINE_ADD_INPUT(Degree, (0));
	Degree.setValue(aDecimatePro->GetDegree());

	SO_ENGINE_ADD_INPUT(FeatureAngle, (0));
	FeatureAngle.setValue(aDecimatePro->GetFeatureAngle());

	SO_ENGINE_ADD_INPUT(SplitAngle, (0));
	SplitAngle.setValue(aDecimatePro->GetSplitAngle());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aDecimatePro->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkDecimatePro::~SoVtkDecimatePro()
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

void SoVtkDecimatePro::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDecimatePro, SoEngine, "Engine" );
}

void SoVtkDecimatePro::evaluate()
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


void SoVtkDecimatePro::inputChanged(SoField * f)
{
	// Get the AbsoluteError value
	if ( f == &AbsoluteError )
		SO_VTK_SET_FIELD_VALUE( mObject, AbsoluteError);

	// Get the Splitting value
	if ( f == &Splitting )
		SO_VTK_SET_FIELD_VALUE( mObject, Splitting);

	// Get the AccumulateError value
	if ( f == &AccumulateError )
		SO_VTK_SET_FIELD_VALUE( mObject, AccumulateError);

	// Get the InflectionPointRatio value
	if ( f == &InflectionPointRatio )
		SO_VTK_SET_FIELD_VALUE( mObject, InflectionPointRatio);

	// Get the MaximumError value
	if ( f == &MaximumError )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumError);

	// Get the ErrorIsAbsolute value
	if ( f == &ErrorIsAbsolute )
		SO_VTK_SET_FIELD_VALUE( mObject, ErrorIsAbsolute);

	// Get the TargetReduction value
	if ( f == &TargetReduction )
		SO_VTK_SET_FIELD_VALUE( mObject, TargetReduction);

	// Get the BoundaryVertexDeletion value
	if ( f == &BoundaryVertexDeletion )
		SO_VTK_SET_FIELD_VALUE( mObject, BoundaryVertexDeletion);

	// Get the PreserveTopology value
	if ( f == &PreserveTopology )
		SO_VTK_SET_FIELD_VALUE( mObject, PreserveTopology);

	// Get the PreSplitMesh value
	if ( f == &PreSplitMesh )
		SO_VTK_SET_FIELD_VALUE( mObject, PreSplitMesh);

	// Get the Degree value
	if ( f == &Degree )
		SO_VTK_SET_FIELD_VALUE( mObject, Degree);

	// Get the FeatureAngle value
	if ( f == &FeatureAngle )
		SO_VTK_SET_FIELD_VALUE( mObject, FeatureAngle);

	// Get the SplitAngle value
	if ( f == &SplitAngle )
		SO_VTK_SET_FIELD_VALUE( mObject, SplitAngle);

	mObject->Update();
}

void SoVtkDecimatePro::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkDecimatePro::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the AbsoluteError value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AbsoluteError);

	// Get the Splitting value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Splitting);

	// Get the AccumulateError value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AccumulateError);

	// Get the InflectionPointRatio value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InflectionPointRatio);

	// Get the MaximumError value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumError);

	// Get the ErrorIsAbsolute value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ErrorIsAbsolute);

	// Get the TargetReduction value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TargetReduction);

	// Get the BoundaryVertexDeletion value
	
		SO_VTK_SET_FIELD_VALUE( mObject, BoundaryVertexDeletion);

	// Get the PreserveTopology value
	
		SO_VTK_SET_FIELD_VALUE( mObject, PreserveTopology);

	// Get the PreSplitMesh value
	
		SO_VTK_SET_FIELD_VALUE( mObject, PreSplitMesh);

	// Get the Degree value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Degree);

	// Get the FeatureAngle value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FeatureAngle);

	// Get the SplitAngle value
	
		SO_VTK_SET_FIELD_VALUE( mObject, SplitAngle);

	mObject->Update();
}
