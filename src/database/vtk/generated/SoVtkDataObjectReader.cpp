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
 
 
# include "SoVtkDataObjectReader.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkCharArray.h"
# include "vtkDataObject.h"


SO_ENGINE_SOURCE( SoVtkDataObjectReader )

SoVtkDataObjectReader::SoVtkDataObjectReader()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDataObjectReader);

	mObject = vtkDataObjectReader::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkDataObjectReader *aDataObjectReader = vtkDataObjectReader::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(FieldDataName, (""));

	SO_ENGINE_ADD_INPUT(ReadFromInputString, (0));
	ReadFromInputString.setValue(aDataObjectReader->GetReadFromInputString());

	SO_ENGINE_ADD_INPUT(TCoordsName, (""));

	SO_ENGINE_ADD_INPUT(ReadAllNormals, (0));
	ReadAllNormals.setValue(aDataObjectReader->GetReadAllNormals());

	SO_ENGINE_ADD_INPUT(VectorsName, (""));

	SO_ENGINE_ADD_INPUT(ReadAllTCoords, (0));
	ReadAllTCoords.setValue(aDataObjectReader->GetReadAllTCoords());

	SO_ENGINE_ADD_INPUT(ReadAllColorScalars, (0));
	ReadAllColorScalars.setValue(aDataObjectReader->GetReadAllColorScalars());

	SO_ENGINE_ADD_INPUT(ReadAllTensors, (0));
	ReadAllTensors.setValue(aDataObjectReader->GetReadAllTensors());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(InputArray, (0));

	SO_ENGINE_ADD_INPUT(LookupTableName, (""));

	SO_ENGINE_ADD_INPUT(ScalarsName, (""));

	SO_ENGINE_ADD_INPUT(NormalsName, (""));

	SO_ENGINE_ADD_INPUT(ReadAllScalars, (0));
	ReadAllScalars.setValue(aDataObjectReader->GetReadAllScalars());

	SO_ENGINE_ADD_INPUT(ReadAllVectors, (0));
	ReadAllVectors.setValue(aDataObjectReader->GetReadAllVectors());

	SO_ENGINE_ADD_INPUT(TensorsName, (""));

	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(InputString, (""));

	SO_ENGINE_ADD_INPUT(ReadAllFields, (0));
	ReadAllFields.setValue(aDataObjectReader->GetReadAllFields());

	aDataObjectReader->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkDataObjectReader::~SoVtkDataObjectReader()
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

void SoVtkDataObjectReader::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDataObjectReader, SoEngine, "Engine" );
}

void SoVtkDataObjectReader::evaluate()
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


void SoVtkDataObjectReader::inputChanged(SoField * f)
{
	// Get the FieldDataName value
	if ( f == &FieldDataName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FieldDataName);

	// Get the ReadFromInputString value
	if ( f == &ReadFromInputString )
		SO_VTK_SET_FIELD_VALUE( mObject, ReadFromInputString);

	// Get the TCoordsName value
	if ( f == &TCoordsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, TCoordsName);

	// Get the ReadAllNormals value
	if ( f == &ReadAllNormals )
		SO_VTK_SET_FIELD_VALUE( mObject, ReadAllNormals);

	// Get the VectorsName value
	if ( f == &VectorsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, VectorsName);

	// Get the ReadAllTCoords value
	if ( f == &ReadAllTCoords )
		SO_VTK_SET_FIELD_VALUE( mObject, ReadAllTCoords);

	// Get the ReadAllColorScalars value
	if ( f == &ReadAllColorScalars )
		SO_VTK_SET_FIELD_VALUE( mObject, ReadAllColorScalars);

	// Get the ReadAllTensors value
	if ( f == &ReadAllTensors )
		SO_VTK_SET_FIELD_VALUE( mObject, ReadAllTensors);

	// Get the InputArray value
	if ( f == &InputArray )
		SO_VTK_SET_FIELD_DATA( mObject, InputArray, vtkCharArray);

	// Get the LookupTableName value
	if ( f == &LookupTableName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, LookupTableName);

	// Get the ScalarsName value
	if ( f == &ScalarsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, ScalarsName);

	// Get the NormalsName value
	if ( f == &NormalsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, NormalsName);

	// Get the ReadAllScalars value
	if ( f == &ReadAllScalars )
		SO_VTK_SET_FIELD_VALUE( mObject, ReadAllScalars);

	// Get the ReadAllVectors value
	if ( f == &ReadAllVectors )
		SO_VTK_SET_FIELD_VALUE( mObject, ReadAllVectors);

	// Get the TensorsName value
	if ( f == &TensorsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, TensorsName);

	// Get the FileName value
	if ( f == &FileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the InputString value
	if ( f == &InputString )
		SO_VTK_SET_FIELD_MFSTRING( mObject, InputString);

	// Get the ReadAllFields value
	if ( f == &ReadAllFields )
		SO_VTK_SET_FIELD_VALUE( mObject, ReadAllFields);

	mObject->Update();
}

void SoVtkDataObjectReader::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkDataObjectReader::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the FieldDataName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FieldDataName);

	// Get the ReadFromInputString value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ReadFromInputString);

	// Get the TCoordsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, TCoordsName);

	// Get the ReadAllNormals value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ReadAllNormals);

	// Get the VectorsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, VectorsName);

	// Get the ReadAllTCoords value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ReadAllTCoords);

	// Get the ReadAllColorScalars value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ReadAllColorScalars);

	// Get the ReadAllTensors value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ReadAllTensors);

	// Get the InputArray value
	
		SO_VTK_SET_FIELD_DATA( mObject, InputArray, vtkCharArray);

	// Get the LookupTableName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, LookupTableName);

	// Get the ScalarsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, ScalarsName);

	// Get the NormalsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, NormalsName);

	// Get the ReadAllScalars value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ReadAllScalars);

	// Get the ReadAllVectors value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ReadAllVectors);

	// Get the TensorsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, TensorsName);

	// Get the FileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the InputString value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, InputString);

	// Get the ReadAllFields value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ReadAllFields);

	mObject->Update();
}
