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
 
 
# include "SoVtkGESignaReader.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkGESignaReader )

SoVtkGESignaReader::SoVtkGESignaReader()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkGESignaReader);

	mObject = vtkGESignaReader::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkGESignaReader *aGESignaReader = vtkGESignaReader::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(DataSpacing, (0,0,0));

	x = aGESignaReader->GetDataSpacing();
	DataSpacing.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(ImageNumber, (""));

	SO_ENGINE_ADD_INPUT(FilePattern, (""));

	SO_ENGINE_ADD_INPUT(Series, (""));

	SO_ENGINE_ADD_INPUT(PatientID, (""));

	SO_ENGINE_ADD_INPUT(FilePrefix, (""));

	SO_ENGINE_ADD_INPUT(FileDimensionality, (0));
	FileDimensionality.setValue(aGESignaReader->GetFileDimensionality());

	SO_ENGINE_ADD_INPUT(Modality, (""));

	SO_ENGINE_ADD_INPUT(DataOrigin, (0,0,0));

	x = aGESignaReader->GetDataOrigin();
	DataOrigin.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(DataScalarType, (0));
	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(DataExtent, (0));

	SO_ENGINE_ADD_INPUT(HeaderSize, (0));
	HeaderSize.setValue(aGESignaReader->GetHeaderSize());

	SO_ENGINE_ADD_INPUT(PatientName, (""));

	SO_ENGINE_ADD_INPUT(FileNameSliceOffset, (0));
	FileNameSliceOffset.setValue(aGESignaReader->GetFileNameSliceOffset());

	SO_ENGINE_ADD_INPUT(NumberOfScalarComponents, (0));
	NumberOfScalarComponents.setValue(aGESignaReader->GetNumberOfScalarComponents());

	SO_ENGINE_ADD_INPUT(Date, (""));

	SO_ENGINE_ADD_INPUT(FileLowerLeft, (0));
	FileLowerLeft.setValue(aGESignaReader->GetFileLowerLeft());

	SO_ENGINE_ADD_INPUT(DataByteOrder, (0));
	DataByteOrder.setValue(aGESignaReader->GetDataByteOrder());

	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(SwapBytes, (0));
	SwapBytes.setValue(aGESignaReader->GetSwapBytes());

	SO_ENGINE_ADD_INPUT(Study, (""));

	SO_ENGINE_ADD_INPUT(FileNameSliceSpacing, (0));
	FileNameSliceSpacing.setValue(aGESignaReader->GetFileNameSliceSpacing());

	aGESignaReader->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkGESignaReader::~SoVtkGESignaReader()
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

void SoVtkGESignaReader::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkGESignaReader, SoEngine, "Engine" );
}

void SoVtkGESignaReader::evaluate()
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


void SoVtkGESignaReader::inputChanged(SoField * f)
{
	// Get the DataSpacing value
	if ( f == &DataSpacing )
		SO_VTK_SET_FIELD_VEC3F( mObject, DataSpacing);

	// Get the ImageNumber value
	if ( f == &ImageNumber )
		SO_VTK_SET_FIELD_MFSTRING( mObject, ImageNumber);

	// Get the FilePattern value
	if ( f == &FilePattern )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePattern);

	// Get the Series value
	if ( f == &Series )
		SO_VTK_SET_FIELD_MFSTRING( mObject, Series);

	// Get the PatientID value
	if ( f == &PatientID )
		SO_VTK_SET_FIELD_MFSTRING( mObject, PatientID);

	// Get the FilePrefix value
	if ( f == &FilePrefix )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePrefix);

	// Get the FileDimensionality value
	if ( f == &FileDimensionality )
		SO_VTK_SET_FIELD_VALUE( mObject, FileDimensionality);

	// Get the Modality value
	if ( f == &Modality )
		SO_VTK_SET_FIELD_MFSTRING( mObject, Modality);

	// Get the DataOrigin value
	if ( f == &DataOrigin )
		SO_VTK_SET_FIELD_VEC3F( mObject, DataOrigin);

	// Get the DataScalarType value
	if ( f == &DataScalarType )
		SO_VTK_SET_FIELD_VALUE( mObject, DataScalarType);

	// Get the DataExtent value
	if ( f == &DataExtent )
	{
		if ( DataExtent.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, DataExtent);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the HeaderSize value
	if ( f == &HeaderSize )
		SO_VTK_SET_FIELD_VALUE( mObject, HeaderSize);

	// Get the PatientName value
	if ( f == &PatientName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, PatientName);

	// Get the FileNameSliceOffset value
	if ( f == &FileNameSliceOffset )
		SO_VTK_SET_FIELD_VALUE( mObject, FileNameSliceOffset);

	// Get the NumberOfScalarComponents value
	if ( f == &NumberOfScalarComponents )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfScalarComponents);

	// Get the Date value
	if ( f == &Date )
		SO_VTK_SET_FIELD_MFSTRING( mObject, Date);

	// Get the FileLowerLeft value
	if ( f == &FileLowerLeft )
		SO_VTK_SET_FIELD_VALUE( mObject, FileLowerLeft);

	// Get the DataByteOrder value
	if ( f == &DataByteOrder )
		SO_VTK_SET_FIELD_VALUE( mObject, DataByteOrder);

	// Get the FileName value
	if ( f == &FileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the SwapBytes value
	if ( f == &SwapBytes )
		SO_VTK_SET_FIELD_VALUE( mObject, SwapBytes);

	// Get the Study value
	if ( f == &Study )
		SO_VTK_SET_FIELD_MFSTRING( mObject, Study);

	// Get the FileNameSliceSpacing value
	if ( f == &FileNameSliceSpacing )
		SO_VTK_SET_FIELD_VALUE( mObject, FileNameSliceSpacing);

	mObject->Update();
}

void SoVtkGESignaReader::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkGESignaReader::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the DataSpacing value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, DataSpacing);

	// Get the ImageNumber value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, ImageNumber);

	// Get the FilePattern value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePattern);

	// Get the Series value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, Series);

	// Get the PatientID value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, PatientID);

	// Get the FilePrefix value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePrefix);

	// Get the FileDimensionality value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FileDimensionality);

	// Get the Modality value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, Modality);

	// Get the DataOrigin value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, DataOrigin);

	// Get the DataScalarType value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DataScalarType);

	// Get the DataExtent value
	
	{
		if ( DataExtent.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, DataExtent);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the HeaderSize value
	
		SO_VTK_SET_FIELD_VALUE( mObject, HeaderSize);

	// Get the PatientName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, PatientName);

	// Get the FileNameSliceOffset value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FileNameSliceOffset);

	// Get the NumberOfScalarComponents value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfScalarComponents);

	// Get the Date value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, Date);

	// Get the FileLowerLeft value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FileLowerLeft);

	// Get the DataByteOrder value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DataByteOrder);

	// Get the FileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the SwapBytes value
	
		SO_VTK_SET_FIELD_VALUE( mObject, SwapBytes);

	// Get the Study value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, Study);

	// Get the FileNameSliceSpacing value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FileNameSliceSpacing);

	mObject->Update();
}
