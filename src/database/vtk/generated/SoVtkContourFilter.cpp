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

# include "SoVtkContourFilter.h"
# include "SoVtkUtils.h"

# include "vtkScalarTree.h"
# include "vtkPointLocator.h"
# include "vtkDataObject.h"
# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkContourFilter )

SoVtkContourFilter::SoVtkContourFilter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkContourFilter);

	mObject = vtkContourFilter::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkContourFilter *aContourFilter = vtkContourFilter::New();

	SO_ENGINE_ADD_INPUT(NumberOfContours, (0));
	NumberOfContours.setValue(aContourFilter->GetNumberOfContours());

	SO_ENGINE_ADD_INPUT(Value, ());
	Value.setFormat("int double");

	SO_ENGINE_ADD_INPUT(ComputeScalars, (0));
	ComputeScalars.setValue(aContourFilter->GetComputeScalars());

	SO_ENGINE_ADD_INPUT(UseScalarTree, (0));
	UseScalarTree.setValue(aContourFilter->GetUseScalarTree());

	SO_ENGINE_ADD_INPUT(ScalarTree, (0));

	SO_ENGINE_ADD_INPUT(ComputeGradients, (0));
	ComputeGradients.setValue(aContourFilter->GetComputeGradients());

	SO_ENGINE_ADD_INPUT(Locator, (0));

	SO_ENGINE_ADD_INPUT(InputArrayToProcess, ());
	InputArrayToProcess.setFormat("int int int int char*");

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(ComputeNormals, (0));
	ComputeNormals.setValue(aContourFilter->GetComputeNormals());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aContourFilter->Delete();

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
}

SoVtkContourFilter::~SoVtkContourFilter()
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

void SoVtkContourFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkContourFilter, SoEngine, "Engine" );
}

void SoVtkContourFilter::evaluate()
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

void SoVtkContourFilter::inputChanged(SoField * f)
{
	// Get the NumberOfContours value
	if ( f == &NumberOfContours )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfContours);

	// Get the Value value
	if ( f == &Value )
	{
		SbVariant vValue = (SbVariant)Value.getValue();
		SoInput input;
		int val0;
		double val1;
	
		input.setBuffer((void *)vValue.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		mObject->SetValue( (int) val0, (double) val1 );
	}
	// Get the ComputeScalars value
	if ( f == &ComputeScalars )
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeScalars);

	// Get the UseScalarTree value
	if ( f == &UseScalarTree )
		SO_VTK_SET_FIELD_VALUE( mObject, UseScalarTree);

	// Get the ScalarTree value
	if ( f == &ScalarTree )
		SO_VTK_SET_FIELD_DATA( mObject, ScalarTree, vtkScalarTree);

	// Get the ComputeGradients value
	if ( f == &ComputeGradients )
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeGradients);

	// Get the Locator value
	if ( f == &Locator )
		SO_VTK_SET_FIELD_DATA( mObject, Locator, vtkPointLocator);

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
	// Get the ComputeNormals value
	if ( f == &ComputeNormals )
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeNormals);

	//mObject->Update();
	
}

