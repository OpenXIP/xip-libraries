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
 
 
# include "SoVtkDataWriter.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"


SO_ENGINE_SOURCE( SoVtkDataWriter )

SoVtkDataWriter::SoVtkDataWriter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDataWriter);

	mObject = vtkDataWriter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkDataWriter *aDataWriter = vtkDataWriter::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(FieldDataName, (""));

	SO_ENGINE_ADD_INPUT(FileType, (0));
	FileType.setValue(aDataWriter->GetFileType());

	SO_ENGINE_ADD_INPUT(LookupTableName, (""));

	SO_ENGINE_ADD_INPUT(TCoordsName, (""));

	SO_ENGINE_ADD_INPUT(ScalarsName, (""));

	SO_ENGINE_ADD_INPUT(NormalsName, (""));

	SO_ENGINE_ADD_INPUT(VectorsName, (""));

	SO_ENGINE_ADD_INPUT(WriteToOutputString, (0));
	WriteToOutputString.setValue(aDataWriter->GetWriteToOutputString());

	SO_ENGINE_ADD_INPUT(TensorsName, (""));

	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(Header, (""));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aDataWriter->Delete();


	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkDataWriter::~SoVtkDataWriter()
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

void SoVtkDataWriter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDataWriter, SoEngine, "Engine" );
}

void SoVtkDataWriter::evaluate()
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


void SoVtkDataWriter::inputChanged(SoField * f)
{
	// Get the FieldDataName value
	if ( f == &FieldDataName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FieldDataName);

	// Get the FileType value
	if ( f == &FileType )
		SO_VTK_SET_FIELD_VALUE( mObject, FileType);

	// Get the LookupTableName value
	if ( f == &LookupTableName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, LookupTableName);

	// Get the TCoordsName value
	if ( f == &TCoordsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, TCoordsName);

	// Get the ScalarsName value
	if ( f == &ScalarsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, ScalarsName);

	// Get the NormalsName value
	if ( f == &NormalsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, NormalsName);

	// Get the VectorsName value
	if ( f == &VectorsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, VectorsName);

	// Get the WriteToOutputString value
	if ( f == &WriteToOutputString )
		SO_VTK_SET_FIELD_VALUE( mObject, WriteToOutputString);

	// Get the TensorsName value
	if ( f == &TensorsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, TensorsName);

	// Get the FileName value
	if ( f == &FileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the Header value
	if ( f == &Header )
		SO_VTK_SET_FIELD_MFSTRING( mObject, Header);

	mObject->Update();
}

void SoVtkDataWriter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkDataWriter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the FieldDataName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FieldDataName);

	// Get the FileType value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FileType);

	// Get the LookupTableName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, LookupTableName);

	// Get the TCoordsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, TCoordsName);

	// Get the ScalarsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, ScalarsName);

	// Get the NormalsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, NormalsName);

	// Get the VectorsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, VectorsName);

	// Get the WriteToOutputString value
	
		SO_VTK_SET_FIELD_VALUE( mObject, WriteToOutputString);

	// Get the TensorsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, TensorsName);

	// Get the FileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the Header value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, Header);

	mObject->Update();
}
