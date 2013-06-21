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

#include "SoVtkGenericEnSightReader.h"
#include "SoVtkUtils.h"

#include "vtkAlgorithmOutput.h"
#include "vtkDataSet.h"
#include "vtkMultiBlockDataSet.h"

SO_ENGINE_SOURCE( SoVtkGenericEnSightReader )

SoVtkGenericEnSightReader::SoVtkGenericEnSightReader()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkGenericEnSightReader);

	mObject = vtkGenericEnSightReader::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkGenericEnSightReader *aGenericEnSightReader =
	  vtkGenericEnSightReader::New();

	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(ByteOrder, (0));
	ByteOrder.setValue(aGenericEnSightReader->GetByteOrder());

	SO_ENGINE_ADD_INPUT(TimeValue, (0));
	SO_ENGINE_ADD_INPUT(FilePath, (""));

	SO_ENGINE_ADD_INPUT(NumberOfInputConnections, ());
	NumberOfInputConnections.setFormat("int int");

	SO_ENGINE_ADD_INPUT(CaseFileName, (""));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(ReadAllVariables, (0));
	ReadAllVariables.setValue(aGenericEnSightReader->GetReadAllVariables());

	aGenericEnSightReader->Delete();

	SO_ENGINE_DEFINE_ENUM_VALUE( FileTypes, ENSIGHT_GOLD_BINARY );
	SO_ENGINE_DEFINE_ENUM_VALUE( FileTypes, ENSIGHT_6_BINARY );
	SO_ENGINE_DEFINE_ENUM_VALUE( FileTypes, ENSIGHT_GOLD );
	SO_ENGINE_DEFINE_ENUM_VALUE( FileTypes, ENSIGHT_6 );
	SO_ENGINE_DEFINE_ENUM_VALUE( FileTypes, ENSIGHT_MASTER_SERVER );
	SO_ENGINE_SET_SF_ENUM_TYPE( FileTypesEnum, FileTypes );

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

	addCalled = 0;
}

SoVtkGenericEnSightReader::~SoVtkGenericEnSightReader()
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

void SoVtkGenericEnSightReader::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkGenericEnSightReader, SoEngine, "Engine" );
}

void SoVtkGenericEnSightReader::evaluate()
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
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput,
	  setValue( mOutputPort ) );
}

void SoVtkGenericEnSightReader::inputChanged(SoField * f)
{
	// Get the ByteOrder value
	if ( f == &ByteOrder )
		SO_VTK_SET_FIELD_VALUE( mObject, ByteOrder);

	// Get the TimeValue value
	if ( f == &TimeValue )
		SO_VTK_SET_FIELD_VALUE( mObject, TimeValue);

	// Get the FilePath value
	if ( f == &FilePath )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePath);

	// Get the NumberOfInputConnections value
	if ( f == &NumberOfInputConnections )
	{
		SbVariant *vNumberOfInputConnections = (SbVariant *)NumberOfInputConnections.getValues(0);
		SoInput input;
		int nb_fields = NumberOfInputConnections.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vNumberOfInputConnections[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			//mObject->SetNumberOfInputConnections( (int) val0, (int) val1 );
		}
	}

	// Get the CaseFileName value
	if ( f == &CaseFileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, CaseFileName);

	// Get the ReadAllVariables value
	if ( f == &ReadAllVariables )
		SO_VTK_SET_FIELD_VALUE( mObject, ReadAllVariables);

	mObject->Update();
}

void SoVtkGenericEnSightReader::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkGenericEnSightReader::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the ByteOrder value
	SO_VTK_SET_FIELD_VALUE( mObject, ByteOrder);

	// Get the TimeValue value
	SO_VTK_SET_FIELD_VALUE( mObject, TimeValue);

	// Get the FilePath value
	SO_VTK_SET_FIELD_MFSTRING( mObject, FilePath);

	// Get the NumberOfInputConnections value
	if (addCalled == 1)
	{
		SbVariant *vNumberOfInputConnections = (SbVariant *)NumberOfInputConnections.getValues(0);
		SoInput input;
		int nb_fields = NumberOfInputConnections.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vNumberOfInputConnections[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			//mObject->SetNumberOfInputConnections( (int) val0, (int) val1 );
		}
	}

	// Get the CaseFileName value
	SO_VTK_SET_FIELD_MFSTRING( mObject, CaseFileName);

	// Get the ReadAllVariables value
	SO_VTK_SET_FIELD_VALUE( mObject, ReadAllVariables);

	mObject->Update();
}

