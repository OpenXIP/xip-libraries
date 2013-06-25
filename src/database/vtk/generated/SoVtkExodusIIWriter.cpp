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
 
#include "SoVtkExodusIIWriter.h"
#include "SoVtkUtils.h"

#include "vtkModelMetadata.h"
#include "vtkAlgorithmOutput.h"

#ifdef WIN64
#include "vtkMultiBlockDataSet.h"
#endif

SO_ENGINE_SOURCE( SoVtkExodusIIWriter )

SoVtkExodusIIWriter::SoVtkExodusIIWriter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkExodusIIWriter);

	mObject = vtkExodusIIWriter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkExodusIIWriter *aExodusIIWriter = vtkExodusIIWriter::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(GhostLevel, (0));
	GhostLevel.setValue(aExodusIIWriter->GetGhostLevel());

	SO_ENGINE_ADD_INPUT(StoreDoubles, (0));
	StoreDoubles.setValue(aExodusIIWriter->GetStoreDoubles());

	SO_ENGINE_ADD_INPUT(WriteOutBlockIdArray, (0));
	WriteOutBlockIdArray.setValue(aExodusIIWriter->
	  GetWriteOutBlockIdArray());

	SO_ENGINE_ADD_INPUT(WriteOutGlobalElementIdArray, (0));
	WriteOutGlobalElementIdArray.setValue(aExodusIIWriter->
	  GetWriteOutGlobalElementIdArray());

	SO_ENGINE_ADD_INPUT(WriteOutGlobalNodeIdArray, (0));
	WriteOutGlobalNodeIdArray.setValue(aExodusIIWriter->
	  GetWriteOutGlobalNodeIdArray());

	//SO_ENGINE_ADD_INPUT(CurrentTimeStep, (0));
	//CurrentTimeStep.setValue(aExodusIIWriter->GetCurrentTimeStep());

	SO_ENGINE_ADD_INPUT(ModelMetadata, (0));

	//SO_ENGINE_ADD_INPUT(GlobalNodeIdArrayName, (""));

	//SO_ENGINE_ADD_INPUT(GlobalElementIdArrayName, (""));

	SO_ENGINE_ADD_INPUT(ErrorStatus, (0));

#ifdef WIN32 //WARNING - this is probably more of a VTK version specific thing...
	ErrorStatus.setValue(aExodusIIWriter->GetErrorStatus());
#endif //WIN32

	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(BlockIdArrayName, (""));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aExodusIIWriter->Delete();


	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( oOrCreateModelMetadata, SoSFVtkObject );
	mOrCreateModelMetadata = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkExodusIIWriter::~SoVtkExodusIIWriter()
{
	// Deletion of the objects if they exist
	if ( mOutputPort )
	{
	
		mOutputPort->unref();
		mOutputPort = 0;
	}
	
	if ( mOrCreateModelMetadata )
	{
	
		mOrCreateModelMetadata->unref();
		mOrCreateModelMetadata = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkExodusIIWriter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkExodusIIWriter, SoEngine, "Engine" );
}

void SoVtkExodusIIWriter::evaluate()
{
	try
	{
        
#ifdef WIN32 //WARNING - this is probably more of a VTK version specific thing...
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
		
		if ( mOrCreateModelMetadata )
		{
		
			mOrCreateModelMetadata->unref();
			mOrCreateModelMetadata = 0;
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
		mObject->GetOrCreateModelMetadata();
		mOrCreateModelMetadata = new SoVtkObject();
		mOrCreateModelMetadata->ref();
		mOrCreateModelMetadata->setPointer( mObject->GetOrCreateModelMetadata() );

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );
#endif //WIN32 
        
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( oOrCreateModelMetadata, SoSFVtkObject, setValue( mOrCreateModelMetadata ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkExodusIIWriter::inputChanged(SoField * f)
{
	// Get the GhostLevel value
	if ( f == &GhostLevel )
		SO_VTK_SET_FIELD_VALUE( mObject, GhostLevel);

	// Get the StoreDoubles value
	if ( f == &StoreDoubles )
		SO_VTK_SET_FIELD_VALUE( mObject, StoreDoubles);

	// Get the WriteOutBlockIdArray value
	if ( f == &WriteOutBlockIdArray )
		SO_VTK_SET_FIELD_VALUE( mObject, WriteOutBlockIdArray);

	// Get the WriteOutGlobalElementIdArray value
	if ( f == &WriteOutGlobalElementIdArray )
		SO_VTK_SET_FIELD_VALUE( mObject, WriteOutGlobalElementIdArray);

	// Get the WriteOutGlobalNodeIdArray value
	if ( f == &WriteOutGlobalNodeIdArray )
		SO_VTK_SET_FIELD_VALUE( mObject, WriteOutGlobalNodeIdArray);

	// Get the CurrentTimeStep value
	//if ( f == &CurrentTimeStep )
  //SO_VTK_SET_FIELD_VALUE( mObject, CurrentTimeStep);

	// Get the ModelMetadata value
	if ( f == &ModelMetadata )
		SO_VTK_SET_FIELD_DATA( mObject, ModelMetadata, vtkModelMetadata);

	// Get the GlobalNodeIdArrayName value
	//if ( f == &GlobalNodeIdArrayName )
	//SO_VTK_SET_FIELD_MFSTRING( mObject, GlobalNodeIdArrayName);

	// Get the GlobalElementIdArrayName value
	//if ( f == &GlobalElementIdArrayName )
	//SO_VTK_SET_FIELD_MFSTRING( mObject, GlobalElementIdArrayName);

#ifdef WIN32 //WARNING - this is probably more of a VTK version specific thing...
	// Get the ErrorStatus value
	if ( f == &ErrorStatus )
		SO_VTK_SET_FIELD_VALUE( mObject, ErrorStatus);
#endif //WIN32
    
	// Get the FileName value
	if ( f == &FileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the BlockIdArrayName value
	if ( f == &BlockIdArrayName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, BlockIdArrayName);

	mObject->Update();
}

void SoVtkExodusIIWriter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkExodusIIWriter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the GhostLevel value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GhostLevel);

	// Get the StoreDoubles value
	
		SO_VTK_SET_FIELD_VALUE( mObject, StoreDoubles);

	// Get the WriteOutBlockIdArray value
	
		SO_VTK_SET_FIELD_VALUE( mObject, WriteOutBlockIdArray);

	// Get the WriteOutGlobalElementIdArray value
	
		SO_VTK_SET_FIELD_VALUE( mObject, WriteOutGlobalElementIdArray);

	// Get the WriteOutGlobalNodeIdArray value
	
		SO_VTK_SET_FIELD_VALUE( mObject, WriteOutGlobalNodeIdArray);

	// Get the CurrentTimeStep value
	//SO_VTK_SET_FIELD_VALUE( mObject, CurrentTimeStep);

	// Get the ModelMetadata value
	SO_VTK_SET_FIELD_DATA( mObject, ModelMetadata, vtkModelMetadata);

	// Get the GlobalNodeIdArrayName value
	//SO_VTK_SET_FIELD_MFSTRING( mObject, GlobalNodeIdArrayName);

	// Get the GlobalElementIdArrayName value
	//SO_VTK_SET_FIELD_MFSTRING( mObject, GlobalElementIdArrayName);

	// Get the ErrorStatus value
#ifdef WIN32 //WARNING - this is probably more of a VTK version specific thing...
		SO_VTK_SET_FIELD_VALUE( mObject, ErrorStatus);
#endif //WIN32

	// Get the FileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the BlockIdArrayName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, BlockIdArrayName);

	mObject->Update();
}

