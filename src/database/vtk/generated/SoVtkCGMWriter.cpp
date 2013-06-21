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
 
 
# include "SoVtkCGMWriter.h"
# include "SoVtkUtils.h"

# include "vtkViewport.h"
# include "vtkAlgorithmOutput.h"


SO_ENGINE_SOURCE( SoVtkCGMWriter )

SoVtkCGMWriter::SoVtkCGMWriter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkCGMWriter);

	mObject = vtkCGMWriter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkCGMWriter *aCGMWriter = vtkCGMWriter::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(FieldDataName, (""));

	SO_ENGINE_ADD_INPUT(Viewport, (0));

	SO_ENGINE_ADD_INPUT(TCoordsName, (""));

	SO_ENGINE_ADD_INPUT(Sort, (0));
	Sort.setValue(aCGMWriter->GetSort());

	SO_ENGINE_ADD_INPUT(VectorsName, (""));

	SO_ENGINE_ADD_INPUT(SpecifiedColor, (0,0,0));

	z = aCGMWriter->GetSpecifiedColor();
	SpecifiedColor.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Resolution, (0));
	Resolution.setValue(aCGMWriter->GetResolution());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(LookupTableName, (""));

	SO_ENGINE_ADD_INPUT(FileType, (0));
	FileType.setValue(aCGMWriter->GetFileType());

	SO_ENGINE_ADD_INPUT(ScalarsName, (""));

	SO_ENGINE_ADD_INPUT(NormalsName, (""));

	SO_ENGINE_ADD_INPUT(WriteToOutputString, (0));
	WriteToOutputString.setValue(aCGMWriter->GetWriteToOutputString());

	SO_ENGINE_ADD_INPUT(TensorsName, (""));

	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(ColorMode, (0));
	ColorMode.setValue(aCGMWriter->GetColorMode());

	SO_ENGINE_ADD_INPUT(Header, (""));

	aCGMWriter->Delete();


	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkCGMWriter::~SoVtkCGMWriter()
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

void SoVtkCGMWriter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkCGMWriter, SoEngine, "Engine" );
}

void SoVtkCGMWriter::evaluate()
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


void SoVtkCGMWriter::inputChanged(SoField * f)
{
	// Get the FieldDataName value
	if ( f == &FieldDataName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FieldDataName);

	// Get the Viewport value
	if ( f == &Viewport )
		SO_VTK_SET_FIELD_DATA( mObject, Viewport, vtkViewport);

	// Get the TCoordsName value
	if ( f == &TCoordsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, TCoordsName);

	// Get the Sort value
	if ( f == &Sort )
		SO_VTK_SET_FIELD_VALUE( mObject, Sort);

	// Get the VectorsName value
	if ( f == &VectorsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, VectorsName);

	// Get the SpecifiedColor value
	if ( f == &SpecifiedColor )
		SO_VTK_SET_FIELD_VEC3F( mObject, SpecifiedColor);

	// Get the Resolution value
	if ( f == &Resolution )
		SO_VTK_SET_FIELD_VALUE( mObject, Resolution);

	// Get the LookupTableName value
	if ( f == &LookupTableName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, LookupTableName);

	// Get the FileType value
	if ( f == &FileType )
		SO_VTK_SET_FIELD_VALUE( mObject, FileType);

	// Get the ScalarsName value
	if ( f == &ScalarsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, ScalarsName);

	// Get the NormalsName value
	if ( f == &NormalsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, NormalsName);

	// Get the WriteToOutputString value
	if ( f == &WriteToOutputString )
		SO_VTK_SET_FIELD_VALUE( mObject, WriteToOutputString);

	// Get the TensorsName value
	if ( f == &TensorsName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, TensorsName);

	// Get the FileName value
	if ( f == &FileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the ColorMode value
	if ( f == &ColorMode )
		SO_VTK_SET_FIELD_VALUE( mObject, ColorMode);

	// Get the Header value
	if ( f == &Header )
		SO_VTK_SET_FIELD_MFSTRING( mObject, Header);

	mObject->Update();
}

void SoVtkCGMWriter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkCGMWriter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the FieldDataName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FieldDataName);

	// Get the Viewport value
	
		SO_VTK_SET_FIELD_DATA( mObject, Viewport, vtkViewport);

	// Get the TCoordsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, TCoordsName);

	// Get the Sort value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Sort);

	// Get the VectorsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, VectorsName);

	// Get the SpecifiedColor value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, SpecifiedColor);

	// Get the Resolution value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Resolution);

	// Get the LookupTableName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, LookupTableName);

	// Get the FileType value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FileType);

	// Get the ScalarsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, ScalarsName);

	// Get the NormalsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, NormalsName);

	// Get the WriteToOutputString value
	
		SO_VTK_SET_FIELD_VALUE( mObject, WriteToOutputString);

	// Get the TensorsName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, TensorsName);

	// Get the FileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the ColorMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ColorMode);

	// Get the Header value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, Header);

	mObject->Update();
}
