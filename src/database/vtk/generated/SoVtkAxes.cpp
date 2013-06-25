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
 * \author Sylvain Jaume <sylvain.jaume@siemens.com>, Francois Huguet
 */

#include "SoVtkAxes.h"
#include "SoVtkUtils.h"

#include "vtkAlgorithmOutput.h"
#include "vtkPolyData.h"

SO_ENGINE_SOURCE( SoVtkAxes )

SoVtkAxes::SoVtkAxes()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkAxes);

	mObject = vtkAxes::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkAxes *aAxes = vtkAxes::New();

	SO_ENGINE_ADD_INPUT(Symmetric, (0));
	Symmetric.setValue(aAxes->GetSymmetric());

	SO_ENGINE_ADD_INPUT(Origin, (0,0,0));

	double x[3] = {0.0, 0.0, 0.0};
	aAxes->GetOrigin(x);
	Origin.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(ComputeNormals, (0));
	ComputeNormals.setValue(aAxes->GetComputeNormals());

	SO_ENGINE_ADD_INPUT(ScaleFactor, (0));
	ScaleFactor.setValue(aAxes->GetScaleFactor());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aAxes->Delete();

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

	addCalled = 0;
}

SoVtkAxes::~SoVtkAxes()
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

void SoVtkAxes::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkAxes, SoEngine, "Engine" );
}

void SoVtkAxes::evaluate()
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


void SoVtkAxes::inputChanged(SoField * f)
{
	// Get the Symmetric value
	if ( f == &Symmetric )
		SO_VTK_SET_FIELD_VALUE( mObject, Symmetric);

	// Get the Origin value
	if ( f == &Origin )
		SO_VTK_SET_FIELD_VEC3F( mObject, Origin);

	// Get the ComputeNormals value
	if ( f == &ComputeNormals )
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeNormals);

	// Get the ScaleFactor value
	if ( f == &ScaleFactor )
		SO_VTK_SET_FIELD_VALUE( mObject, ScaleFactor);

	mObject->Update();
}

void SoVtkAxes::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkAxes::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Symmetric value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Symmetric);

	// Get the Origin value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Origin);

	// Get the ComputeNormals value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeNormals);

	// Get the ScaleFactor value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ScaleFactor);

	mObject->Update();
}

