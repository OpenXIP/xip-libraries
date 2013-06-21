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
 
 
# include "SoVtkEnSightWriter.h"
# include "SoVtkUtils.h"

# include "vtkModelMetadata.h"
# include "vtkAlgorithmOutput.h"


SO_ENGINE_SOURCE( SoVtkEnSightWriter )

SoVtkEnSightWriter::SoVtkEnSightWriter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkEnSightWriter);

	mObject = vtkEnSightWriter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkEnSightWriter *aEnSightWriter = vtkEnSightWriter::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(GhostLevel, (0));
	GhostLevel.setValue(aEnSightWriter->GetGhostLevel());

	SO_ENGINE_ADD_INPUT(ProcessNumber, (0));
	ProcessNumber.setValue(aEnSightWriter->GetProcessNumber());

	SO_ENGINE_ADD_INPUT(BlockIDs, (0));

	SO_ENGINE_ADD_INPUT(ModelMetadata, (0));

	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(Path, (""));

	SO_ENGINE_ADD_INPUT(TransientGeometry, (0));
	TransientGeometry.setValue(aEnSightWriter->GetTransientGeometry());

	SO_ENGINE_ADD_INPUT(TimeStep, (0));
	TimeStep.setValue(aEnSightWriter->GetTimeStep());

	SO_ENGINE_ADD_INPUT(BaseName, (""));

	SO_ENGINE_ADD_INPUT(NumberOfBlocks, (0));
	NumberOfBlocks.setValue(aEnSightWriter->GetNumberOfBlocks());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aEnSightWriter->Delete();


	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkEnSightWriter::~SoVtkEnSightWriter()
{
	// Deletion of the objects if they exist
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

void SoVtkEnSightWriter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkEnSightWriter, SoEngine, "Engine" );
}

void SoVtkEnSightWriter::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
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

		if ( mObject->GetNumberOfOutputPorts() > 0 )
		{
			mObject->GetOutputPort()->Register(0);
			mOutputPort = new SoVtkAlgorithmOutput();
			mOutputPort->ref();
			mOutputPort->setPointer( mObject->GetOutputPort() );
		}

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkEnSightWriter::inputChanged(SoField * f)
{
	// Get the GhostLevel value
	if ( f == &GhostLevel )
		SO_VTK_SET_FIELD_VALUE( mObject, GhostLevel);

	// Get the ProcessNumber value
	if ( f == &ProcessNumber )
		SO_VTK_SET_FIELD_VALUE( mObject, ProcessNumber);

	// Get the BlockIDs value
	if ( f == &BlockIDs )
	{
		if ( BlockIDs.getNum() >= 5)
		{
			SO_VTK_SET_FIELD_MFINT32( mObject, BlockIDs);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 5 values." );
		}
	}

	// Get the ModelMetadata value
	if ( f == &ModelMetadata )
		SO_VTK_SET_FIELD_DATA( mObject, ModelMetadata, vtkModelMetadata);

	// Get the FileName value
	if ( f == &FileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the Path value
	if ( f == &Path )
		SO_VTK_SET_FIELD_MFSTRING( mObject, Path);

	// Get the TransientGeometry value
	if ( f == &TransientGeometry )
		SO_VTK_SET_FIELD_VALUE( mObject, TransientGeometry);

	// Get the TimeStep value
	if ( f == &TimeStep )
		SO_VTK_SET_FIELD_VALUE( mObject, TimeStep);

	// Get the BaseName value
	if ( f == &BaseName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, BaseName);

	// Get the NumberOfBlocks value
	if ( f == &NumberOfBlocks )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfBlocks);

	mObject->Update();
}

void SoVtkEnSightWriter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkEnSightWriter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the GhostLevel value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GhostLevel);

	// Get the ProcessNumber value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ProcessNumber);

	// Get the BlockIDs value
	
	{
		if ( BlockIDs.getNum() >= 5)
		{
			SO_VTK_SET_FIELD_MFINT32( mObject, BlockIDs);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 5 values." );
		}
	}

	// Get the ModelMetadata value
	
		SO_VTK_SET_FIELD_DATA( mObject, ModelMetadata, vtkModelMetadata);

	// Get the FileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the Path value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, Path);

	// Get the TransientGeometry value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TransientGeometry);

	// Get the TimeStep value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TimeStep);

	// Get the BaseName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, BaseName);

	// Get the NumberOfBlocks value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfBlocks);

	mObject->Update();
}
