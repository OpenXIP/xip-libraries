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

# include "SoVtkPolyDataNormals.h"
# include "SoVtkUtils.h"

# include "vtkDataObject.h"
# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkPolyDataNormals )

SoVtkPolyDataNormals::SoVtkPolyDataNormals()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkPolyDataNormals);

	mObject = vtkPolyDataNormals::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkPolyDataNormals *aPolyDataNormals = vtkPolyDataNormals::New();

	SO_ENGINE_ADD_INPUT(Splitting, (0));
	Splitting.setValue(aPolyDataNormals->GetSplitting());

	SO_ENGINE_ADD_INPUT(ComputePointNormals, (0));
	ComputePointNormals.setValue(aPolyDataNormals->GetComputePointNormals());

	SO_ENGINE_ADD_INPUT(NonManifoldTraversal, (0));
	NonManifoldTraversal.setValue(aPolyDataNormals->GetNonManifoldTraversal());

	SO_ENGINE_ADD_INPUT(ComputeCellNormals, (0));
	ComputeCellNormals.setValue(aPolyDataNormals->GetComputeCellNormals());

	SO_ENGINE_ADD_INPUT(FlipNormals, (0));
	FlipNormals.setValue(aPolyDataNormals->GetFlipNormals());

	SO_ENGINE_ADD_INPUT(Consistency, (0));
	Consistency.setValue(aPolyDataNormals->GetConsistency());

	SO_ENGINE_ADD_INPUT(InputArrayToProcess, ());
	InputArrayToProcess.setFormat("int int int int char*");

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(FeatureAngle, (0));
	FeatureAngle.setValue(aPolyDataNormals->GetFeatureAngle());

	SO_ENGINE_ADD_INPUT(AutoOrientNormals, (0));
	AutoOrientNormals.setValue(aPolyDataNormals->GetAutoOrientNormals());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aPolyDataNormals->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

}

SoVtkPolyDataNormals::~SoVtkPolyDataNormals()
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

void SoVtkPolyDataNormals::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkPolyDataNormals, SoEngine, "Engine" );
}

void SoVtkPolyDataNormals::evaluate()
{
	try
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
		
		// Get the input type(s)
		SoVtkObject *inputPtr = Input.getValue();
		
		if (inputPtr && inputPtr->getPointer()->IsA("vtkDataObject"))
			mObject->SetInput(vtkDataObject::SafeDownCast(inputPtr->getPointer()));

		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

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


void SoVtkPolyDataNormals::inputChanged(SoField * f)
{
	// Get the Splitting value
	if ( f == &Splitting )
		SO_VTK_SET_FIELD_VALUE( mObject, Splitting);

	// Get the ComputePointNormals value
	if ( f == &ComputePointNormals )
		SO_VTK_SET_FIELD_VALUE( mObject, ComputePointNormals);

	// Get the NonManifoldTraversal value
	if ( f == &NonManifoldTraversal )
		SO_VTK_SET_FIELD_VALUE( mObject, NonManifoldTraversal);

	// Get the ComputeCellNormals value
	if ( f == &ComputeCellNormals )
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeCellNormals);

	// Get the FlipNormals value
	if ( f == &FlipNormals )
		SO_VTK_SET_FIELD_VALUE( mObject, FlipNormals);

	// Get the Consistency value
	if ( f == &Consistency )
		SO_VTK_SET_FIELD_VALUE( mObject, Consistency);

	// Get the InputArrayToProcess value
	if ( f == &InputArrayToProcess )
	{
		SbVariant vInputArrayToProcess = (SbVariant)InputArrayToProcess.getValue();
		SoInput input;
		int val0;
		int val1;
		int val2;
		int val3;
		SbString val4;
	
		input.setBuffer((void *)vInputArrayToProcess.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		input.read(val2);
		input.read(val3);
		input.read(val4);
		mObject->SetInputArrayToProcess( 
			(int) val0,
			(int) val1,
			(int) val2,
			(int) val3,
			val4.getString()
		);
	}
	// Get the FeatureAngle value
	if ( f == &FeatureAngle )
		SO_VTK_SET_FIELD_VALUE( mObject, FeatureAngle);

	// Get the AutoOrientNormals value
	if ( f == &AutoOrientNormals )
		SO_VTK_SET_FIELD_VALUE( mObject, AutoOrientNormals);

	//mObject->Update();
	
}

