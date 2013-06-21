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
 
 
# include "SoVtkImageReader.h"
# include "SoVtkUtils.h"

# include "vtkTransform.h"
# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageReader )

SoVtkImageReader::SoVtkImageReader()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageReader);

	mObject = vtkImageReader::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageReader *aImageReader = vtkImageReader::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(DataSpacing, (0,0,0));

	x = aImageReader->GetDataSpacing();
	DataSpacing.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Transform, (0));

	SO_ENGINE_ADD_INPUT(DataVOI, (0));

	SO_ENGINE_ADD_INPUT(FilePattern, (""));

	SO_ENGINE_ADD_INPUT(FilePrefix, (""));

	SO_ENGINE_ADD_INPUT(FileDimensionality, (0));
	FileDimensionality.setValue(aImageReader->GetFileDimensionality());

	SO_ENGINE_ADD_INPUT(DataOrigin, (0,0,0));

	x = aImageReader->GetDataOrigin();
	DataOrigin.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(DataMask, (0));
	SO_ENGINE_ADD_INPUT(DataScalarType, (0));
	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(DataExtent, (0));

	SO_ENGINE_ADD_INPUT(HeaderSize, (0));
	HeaderSize.setValue(aImageReader->GetHeaderSize());

	SO_ENGINE_ADD_INPUT(FileNameSliceOffset, (0));
	FileNameSliceOffset.setValue(aImageReader->GetFileNameSliceOffset());

	SO_ENGINE_ADD_INPUT(NumberOfScalarComponents, (0));
	NumberOfScalarComponents.setValue(aImageReader->GetNumberOfScalarComponents());

	SO_ENGINE_ADD_INPUT(FileLowerLeft, (0));
	FileLowerLeft.setValue(aImageReader->GetFileLowerLeft());

	SO_ENGINE_ADD_INPUT(ScalarArrayName, (""));

	SO_ENGINE_ADD_INPUT(DataByteOrder, (0));
	DataByteOrder.setValue(aImageReader->GetDataByteOrder());

	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(SwapBytes, (0));
	SwapBytes.setValue(aImageReader->GetSwapBytes());

	SO_ENGINE_ADD_INPUT(FileNameSliceSpacing, (0));
	FileNameSliceSpacing.setValue(aImageReader->GetFileNameSliceSpacing());

	aImageReader->Delete();


	SO_ENGINE_ADD_OUTPUT( oTransform, SoSFVtkObject );
	mTransform = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageReader::~SoVtkImageReader()
{
	// Deletion of the objects if they exist
	if ( mTransform )
	{
	
		mTransform->unref();
		mTransform = 0;
	}
	
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

void SoVtkImageReader::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageReader, SoEngine, "Engine" );
}

void SoVtkImageReader::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mTransform )
		{
		
			mTransform->unref();
			mTransform = 0;
		}
		
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

		mObject->GetTransform();
		mTransform = new SoVtkObject();
		mTransform->ref();
		mTransform->setPointer( mObject->GetTransform() );

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
	SO_ENGINE_OUTPUT( oTransform, SoSFVtkObject, setValue( mTransform ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkImageReader::inputChanged(SoField * f)
{
	// Get the DataSpacing value
	if ( f == &DataSpacing )
		SO_VTK_SET_FIELD_VEC3F( mObject, DataSpacing);

	// Get the Transform value
	if ( f == &Transform )
		SO_VTK_SET_FIELD_DATA( mObject, Transform, vtkTransform);

	// Get the DataVOI value
	if ( f == &DataVOI )
	{
		if ( DataVOI.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, DataVOI);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

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

	// Get the DataMask value
	if ( f == &DataMask )
		SO_VTK_SET_FIELD_VALUE( mObject, DataMask);

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

	// Get the FileNameSliceOffset value
	if ( f == &FileNameSliceOffset )
		SO_VTK_SET_FIELD_VALUE( mObject, FileNameSliceOffset);

	// Get the NumberOfScalarComponents value
	if ( f == &NumberOfScalarComponents )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfScalarComponents);

	// Get the FileLowerLeft value
	if ( f == &FileLowerLeft )
		SO_VTK_SET_FIELD_VALUE( mObject, FileLowerLeft);

	// Get the ScalarArrayName value
	if ( f == &ScalarArrayName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, ScalarArrayName);

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

	mObject->Update();
}

void SoVtkImageReader::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageReader::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the DataSpacing value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, DataSpacing);

	// Get the Transform value
	
		SO_VTK_SET_FIELD_DATA( mObject, Transform, vtkTransform);

	// Get the DataVOI value
	
	{
		if ( DataVOI.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, DataVOI);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the FilePattern value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePattern);

	// Get the FilePrefix value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePrefix);

	// Get the FileDimensionality value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FileDimensionality);

	// Get the DataOrigin value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, DataOrigin);

	// Get the DataMask value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DataMask);

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

	// Get the FileNameSliceOffset value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FileNameSliceOffset);

	// Get the NumberOfScalarComponents value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfScalarComponents);

	// Get the FileLowerLeft value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FileLowerLeft);

	// Get the ScalarArrayName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, ScalarArrayName);

	// Get the DataByteOrder value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DataByteOrder);

	// Get the FileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the SwapBytes value
	
		SO_VTK_SET_FIELD_VALUE( mObject, SwapBytes);

	// Get the FileNameSliceSpacing value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FileNameSliceSpacing);

	mObject->Update();
}
