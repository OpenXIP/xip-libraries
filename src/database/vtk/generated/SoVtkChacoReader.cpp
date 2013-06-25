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
 
 
# include "SoVtkChacoReader.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkUnstructuredGrid.h"


SO_ENGINE_SOURCE( SoVtkChacoReader )

SoVtkChacoReader::SoVtkChacoReader()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkChacoReader);

	mObject = vtkChacoReader::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkChacoReader *aChacoReader = vtkChacoReader::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(GenerateVertexWeightArrays, (0));
	GenerateVertexWeightArrays.setValue(aChacoReader->GetGenerateVertexWeightArrays());

	SO_ENGINE_ADD_INPUT(BaseName, (""));

	SO_ENGINE_ADD_INPUT(GenerateEdgeWeightArrays, (0));
	GenerateEdgeWeightArrays.setValue(aChacoReader->GetGenerateEdgeWeightArrays());

	SO_ENGINE_ADD_INPUT(GenerateGlobalNodeIdArray, (0));
	GenerateGlobalNodeIdArray.setValue(aChacoReader->GetGenerateGlobalNodeIdArray());

	SO_ENGINE_ADD_INPUT(GenerateGlobalElementIdArray, (0));
	GenerateGlobalElementIdArray.setValue(aChacoReader->GetGenerateGlobalElementIdArray());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aChacoReader->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkChacoReader::~SoVtkChacoReader()
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

void SoVtkChacoReader::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkChacoReader, SoEngine, "Engine" );
}

void SoVtkChacoReader::evaluate()
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


void SoVtkChacoReader::inputChanged(SoField * f)
{
	// Get the GenerateVertexWeightArrays value
	if ( f == &GenerateVertexWeightArrays )
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateVertexWeightArrays);

	// Get the BaseName value
	if ( f == &BaseName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, BaseName);

	// Get the GenerateEdgeWeightArrays value
	if ( f == &GenerateEdgeWeightArrays )
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateEdgeWeightArrays);

	// Get the GenerateGlobalNodeIdArray value
	if ( f == &GenerateGlobalNodeIdArray )
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateGlobalNodeIdArray);

	// Get the GenerateGlobalElementIdArray value
	if ( f == &GenerateGlobalElementIdArray )
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateGlobalElementIdArray);

	mObject->Update();
}

void SoVtkChacoReader::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkChacoReader::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the GenerateVertexWeightArrays value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateVertexWeightArrays);

	// Get the BaseName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, BaseName);

	// Get the GenerateEdgeWeightArrays value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateEdgeWeightArrays);

	// Get the GenerateGlobalNodeIdArray value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateGlobalNodeIdArray);

	// Get the GenerateGlobalElementIdArray value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateGlobalElementIdArray);

	mObject->Update();
}
