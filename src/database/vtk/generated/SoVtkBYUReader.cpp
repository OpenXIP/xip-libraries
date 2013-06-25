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

#include "SoVtkBYUReader.h"
#include "SoVtkUtils.h"

#include "vtkDataObject.h"
#include "vtkAlgorithmOutput.h"
#include "vtkPolyData.h"

SO_ENGINE_SOURCE( SoVtkBYUReader )

SoVtkBYUReader::SoVtkBYUReader()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkBYUReader);

	mObject = vtkBYUReader::New();

	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkBYUReader *aBYUReader = vtkBYUReader::New();

	SO_ENGINE_ADD_INPUT(ReadTexture, (0));
	ReadTexture.setValue(aBYUReader->GetReadTexture());

	SO_ENGINE_ADD_INPUT(ScalarFileName, (""));

	SO_ENGINE_ADD_INPUT(TextureFileName, (""));

	SO_ENGINE_ADD_INPUT(ReadDisplacement, (0));
	ReadDisplacement.setValue(aBYUReader->GetReadDisplacement());

	SO_ENGINE_ADD_INPUT(GeometryFileName, (""));

	SO_ENGINE_ADD_INPUT(PartNumber, (0));
	PartNumber.setValue(aBYUReader->GetPartNumber());

	SO_ENGINE_ADD_INPUT(DisplacementFileName, (""));

	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(InputArrayToProcess, ());
	InputArrayToProcess.setFormat("int int int int char*");

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(ReadScalar, (0));
	ReadScalar.setValue(aBYUReader->GetReadScalar());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aBYUReader->Delete();

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
}

SoVtkBYUReader::~SoVtkBYUReader()
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

void SoVtkBYUReader::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkBYUReader, SoEngine, "Engine" );
}

void SoVtkBYUReader::evaluate()
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


void SoVtkBYUReader::inputChanged(SoField * f)
{
	// Get the ReadTexture value
	if ( f == &ReadTexture )
		SO_VTK_SET_FIELD_VALUE( mObject, ReadTexture);

	// Get the ScalarFileName value
	if ( f == &ScalarFileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, ScalarFileName);

	// Get the TextureFileName value
	if ( f == &TextureFileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, TextureFileName);

	// Get the ReadDisplacement value
	if ( f == &ReadDisplacement )
		SO_VTK_SET_FIELD_VALUE( mObject, ReadDisplacement);

	// Get the GeometryFileName value
	if ( f == &GeometryFileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, GeometryFileName);

	// Get the PartNumber value
	if ( f == &PartNumber )
		SO_VTK_SET_FIELD_VALUE( mObject, PartNumber);

	// Get the DisplacementFileName value
	if ( f == &DisplacementFileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, DisplacementFileName);

	// Get the FileName value
	if ( f == &FileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

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
	// Get the ReadScalar value
	if ( f == &ReadScalar )
		SO_VTK_SET_FIELD_VALUE( mObject, ReadScalar);

	//mObject->Update();
	
}

