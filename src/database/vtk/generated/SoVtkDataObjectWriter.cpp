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
 
 
# include "SoVtkDataObjectWriter.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"


SO_ENGINE_SOURCE( SoVtkDataObjectWriter )

SoVtkDataObjectWriter::SoVtkDataObjectWriter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDataObjectWriter);

	mObject = vtkDataObjectWriter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkDataObjectWriter *aDataObjectWriter = vtkDataObjectWriter::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(FieldDataName, (""));

	SO_ENGINE_ADD_INPUT(FileType, (0));
	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(Header, (""));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aDataObjectWriter->Delete();


	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkDataObjectWriter::~SoVtkDataObjectWriter()
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

void SoVtkDataObjectWriter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDataObjectWriter, SoEngine, "Engine" );
}

void SoVtkDataObjectWriter::evaluate()
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


void SoVtkDataObjectWriter::inputChanged(SoField * f)
{
	// Get the FieldDataName value
	if ( f == &FieldDataName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FieldDataName);

	// Get the FileType value
	if ( f == &FileType )
		SO_VTK_SET_FIELD_VALUE( mObject, FileType);

	// Get the FileName value
	if ( f == &FileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the Header value
	if ( f == &Header )
		SO_VTK_SET_FIELD_MFSTRING( mObject, Header);

	mObject->Update();
}

void SoVtkDataObjectWriter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkDataObjectWriter::New();
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

	// Get the FileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the Header value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, Header);

	mObject->Update();
}
