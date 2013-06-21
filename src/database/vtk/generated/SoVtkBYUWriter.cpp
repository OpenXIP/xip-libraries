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
 
#include "SoVtkBYUWriter.h"
#include "SoVtkUtils.h"

#include "vtkAlgorithmOutput.h"

SO_ENGINE_SOURCE( SoVtkBYUWriter )

SoVtkBYUWriter::SoVtkBYUWriter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkBYUWriter);

	mObject = vtkBYUWriter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkBYUWriter *aBYUWriter = vtkBYUWriter::New();

	SO_ENGINE_ADD_INPUT(FieldDataName, (""));

	SO_ENGINE_ADD_INPUT(TCoordsName, (""));

	SO_ENGINE_ADD_INPUT(VectorsName, (""));

	SO_ENGINE_ADD_INPUT(WriteDisplacement, (0));
	WriteDisplacement.setValue(aBYUWriter->GetWriteDisplacement());

	SO_ENGINE_ADD_INPUT(DisplacementFileName, (""));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(LookupTableName, (""));

	SO_ENGINE_ADD_INPUT(FileType, (0));
	FileType.setValue(aBYUWriter->GetFileType());

	SO_ENGINE_ADD_INPUT(ScalarsName, (""));

	SO_ENGINE_ADD_INPUT(ScalarFileName, (""));

	SO_ENGINE_ADD_INPUT(NormalsName, (""));

	SO_ENGINE_ADD_INPUT(TextureFileName, (""));

	SO_ENGINE_ADD_INPUT(WriteToOutputString, (0));
	WriteToOutputString.setValue(aBYUWriter->GetWriteToOutputString());

	SO_ENGINE_ADD_INPUT(GeometryFileName, (""));

	SO_ENGINE_ADD_INPUT(WriteScalar, (0));
	WriteScalar.setValue(aBYUWriter->GetWriteScalar());

	SO_ENGINE_ADD_INPUT(TensorsName, (""));

	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(WriteTexture, (0));
	WriteTexture.setValue(aBYUWriter->GetWriteTexture());

	SO_ENGINE_ADD_INPUT(Header, (""));

	aBYUWriter->Delete();

	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	addCalled = 0;
}

SoVtkBYUWriter::~SoVtkBYUWriter()
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

void SoVtkBYUWriter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkBYUWriter, SoEngine, "Engine" );
}

void SoVtkBYUWriter::evaluate()
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


void SoVtkBYUWriter::inputChanged(SoField * f)
{
	// Get the FieldDataName value
	if ( f == &FieldDataName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FieldDataName);

	// Get the TCoordsName value
	if ( f == &TCoordsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, TCoordsName);

	// Get the VectorsName value
	if ( f == &VectorsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, VectorsName);

	// Get the WriteDisplacement value
	if ( f == &WriteDisplacement )
		SO_VTK_SET_FIELD_VALUE( mObject, WriteDisplacement);

	// Get the DisplacementFileName value
	if ( f == &DisplacementFileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, DisplacementFileName);

	// Get the LookupTableName value
	if ( f == &LookupTableName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, LookupTableName);

	// Get the FileType value
	if ( f == &FileType )
		SO_VTK_SET_FIELD_VALUE( mObject, FileType);

	// Get the ScalarsName value
	if ( f == &ScalarsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, ScalarsName);

	// Get the ScalarFileName value
	if ( f == &ScalarFileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, ScalarFileName);

	// Get the NormalsName value
	if ( f == &NormalsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, NormalsName);

	// Get the TextureFileName value
	if ( f == &TextureFileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, TextureFileName);

	// Get the WriteToOutputString value
	if ( f == &WriteToOutputString )
		SO_VTK_SET_FIELD_VALUE( mObject, WriteToOutputString);

	// Get the GeometryFileName value
	if ( f == &GeometryFileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, GeometryFileName);

	// Get the WriteScalar value
	if ( f == &WriteScalar )
		SO_VTK_SET_FIELD_VALUE( mObject, WriteScalar);

	// Get the TensorsName value
	if ( f == &TensorsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, TensorsName);

	// Get the FileName value
	if ( f == &FileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the WriteTexture value
	if ( f == &WriteTexture )
		SO_VTK_SET_FIELD_VALUE( mObject, WriteTexture);

	// Get the Header value
	if ( f == &Header )
		SO_VTK_SET_FIELD_MFSTRING( mObject, Header);

	mObject->Update();
}

void SoVtkBYUWriter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkBYUWriter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the FieldDataName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FieldDataName);

	// Get the TCoordsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, TCoordsName);

	// Get the VectorsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, VectorsName);

	// Get the WriteDisplacement value
	
		SO_VTK_SET_FIELD_VALUE( mObject, WriteDisplacement);

	// Get the DisplacementFileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, DisplacementFileName);

	// Get the LookupTableName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, LookupTableName);

	// Get the FileType value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FileType);

	// Get the ScalarsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, ScalarsName);

	// Get the ScalarFileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, ScalarFileName);

	// Get the NormalsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, NormalsName);

	// Get the TextureFileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, TextureFileName);

	// Get the WriteToOutputString value
	
		SO_VTK_SET_FIELD_VALUE( mObject, WriteToOutputString);

	// Get the GeometryFileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, GeometryFileName);

	// Get the WriteScalar value
	
		SO_VTK_SET_FIELD_VALUE( mObject, WriteScalar);

	// Get the TensorsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, TensorsName);

	// Get the FileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the WriteTexture value
	
		SO_VTK_SET_FIELD_VALUE( mObject, WriteTexture);

	// Get the Header value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, Header);

	mObject->Update();
}

