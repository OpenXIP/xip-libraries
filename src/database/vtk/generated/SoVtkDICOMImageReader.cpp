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

# include "SoVtkDICOMImageReader.h"
# include "SoVtkUtils.h"

# include "vtkDataObject.h"
# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkDICOMImageReader )

SoVtkDICOMImageReader::SoVtkDICOMImageReader()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDICOMImageReader);

	mObject = vtkDICOMImageReader::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkDICOMImageReader *aDICOMImageReader = vtkDICOMImageReader::New();

	double x[3] = {0.0, 0.0, 0.0};
	SO_ENGINE_ADD_INPUT(DataSpacing, (0,0,0));

	aDICOMImageReader->GetDataSpacing(x);
	DataSpacing.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(FilePattern, (""));

	SO_ENGINE_ADD_INPUT(FilePrefix, (""));

	SO_ENGINE_ADD_INPUT(FileDimensionality, (0));
	FileDimensionality.setValue(aDICOMImageReader->GetFileDimensionality());

	SO_ENGINE_ADD_INPUT(DataOrigin, (0,0,0));

	aDICOMImageReader->GetDataOrigin(x);
	DataOrigin.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(InputArrayToProcess, ());
	InputArrayToProcess.setFormat("int int int int char*");

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(DataScalarType, (0));
	DataScalarType.setValue(aDICOMImageReader->GetDataScalarType());

	SO_ENGINE_ADD_INPUT(DataExtent, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(HeaderSize, (0));
	HeaderSize.setValue(aDICOMImageReader->GetHeaderSize());

	SO_ENGINE_ADD_INPUT(FileNameSliceOffset, (0));
	FileNameSliceOffset.setValue(aDICOMImageReader->GetFileNameSliceOffset());

	SO_ENGINE_ADD_INPUT(DirectoryName, (""));

	SO_ENGINE_ADD_INPUT(NumberOfScalarComponents, (0));
	NumberOfScalarComponents.setValue(aDICOMImageReader->GetNumberOfScalarComponents());

	SO_ENGINE_ADD_INPUT(FileLowerLeft, (0));
	FileLowerLeft.setValue(aDICOMImageReader->GetFileLowerLeft());

	SO_ENGINE_ADD_INPUT(DataByteOrder, (0));
	DataByteOrder.setValue(aDICOMImageReader->GetDataByteOrder());

	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(SwapBytes, (0));
	SwapBytes.setValue(aDICOMImageReader->GetSwapBytes());

	SO_ENGINE_ADD_INPUT(FileNameSliceSpacing, (0));
	FileNameSliceSpacing.setValue(aDICOMImageReader->GetFileNameSliceSpacing());

	aDICOMImageReader->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

}

SoVtkDICOMImageReader::~SoVtkDICOMImageReader()
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

void SoVtkDICOMImageReader::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDICOMImageReader, SoEngine, "Engine" );
}

void SoVtkDICOMImageReader::evaluate()
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


void SoVtkDICOMImageReader::inputChanged(SoField * f)
{
	// Get the DataSpacing value
	if ( f == &DataSpacing )
		SO_VTK_SET_FIELD_VEC3F( mObject, DataSpacing);

	// Get the FilePattern value
	if ( f == &FilePattern )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePattern);

	// Get the FilePrefix value
	if ( f == &FilePrefix )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePrefix);

	// Get the FileDimensionality value
	if ( f == &FileDimensionality )
		SO_VTK_SET_FIELD_VALUE( mObject, FileDimensionality);

	// Get the DataOrigin value
	if ( f == &DataOrigin )
		SO_VTK_SET_FIELD_VEC3F( mObject, DataOrigin);

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
	// Get the DataScalarType value
	if ( f == &DataScalarType )
		SO_VTK_SET_FIELD_VALUE( mObject, DataScalarType);

	// Get the DataExtent value
	if ( f == &DataExtent )
	{
		if ( DataExtent.getNum() >= 6)
		{
			SO_VTK_SET_FIELD_MFINT32( mObject, DataExtent);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the HeaderSize value
	if ( f == &HeaderSize )
		SO_VTK_SET_FIELD_VALUE( mObject, HeaderSize);

	// Get the FileNameSliceOffset value
	if ( f == &FileNameSliceOffset )
		SO_VTK_SET_FIELD_VALUE( mObject, FileNameSliceOffset);

	// Get the DirectoryName value
	if ( f == &DirectoryName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, DirectoryName);

	// Get the NumberOfScalarComponents value
	if ( f == &NumberOfScalarComponents )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfScalarComponents);

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

	// Get the FileNameSliceSpacing value
	if ( f == &FileNameSliceSpacing )
		SO_VTK_SET_FIELD_VALUE( mObject, FileNameSliceSpacing);

	//mObject->Update();
	
}

