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

# include "SoVtkVolume16Reader.h"
# include "SoVtkUtils.h"

# include "vtkTransform.h"
# include "vtkDataObject.h"
# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkVolume16Reader )

SoVtkVolume16Reader::SoVtkVolume16Reader()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkVolume16Reader);
	mObject = vtkVolume16Reader::New();
	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkVolume16Reader *aVolume16Reader = vtkVolume16Reader::New();
	double *x;
	int *y;

	SO_ENGINE_ADD_INPUT(DataSpacing, (0,0,0));

	x= aVolume16Reader->GetDataSpacing();
	DataSpacing.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Transform, (0));

	SO_ENGINE_ADD_INPUT(HeaderSize, (0));
	HeaderSize.setValue(aVolume16Reader->GetHeaderSize());

	SO_ENGINE_ADD_INPUT(DataDimensions, (0,0));

	y= aVolume16Reader->GetDataDimensions();
	DataDimensions.setValue((float) y[0],(float) y[1]);

	SO_ENGINE_ADD_INPUT(FilePattern, (""));

	SO_ENGINE_ADD_INPUT(FilePrefix, (""));

	SO_ENGINE_ADD_INPUT(DataByteOrder, (0));
	DataByteOrder.setValue(aVolume16Reader->GetDataByteOrder());

	SO_ENGINE_ADD_INPUT(ImageRange, (0,0));

	y= aVolume16Reader->GetImageRange();
	ImageRange.setValue((float) y[0],(float) y[1]);

	SO_ENGINE_ADD_INPUT(SwapBytes, (0));
	SwapBytes.setValue(aVolume16Reader->GetSwapBytes());

	SO_ENGINE_ADD_INPUT(DataOrigin, (0,0,0));

	x= aVolume16Reader->GetDataOrigin();
	DataOrigin.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(DataMask, (0));
	DataMask.setValue(aVolume16Reader->GetDataMask());

	SO_ENGINE_ADD_INPUT(InputArrayToProcess, ());
	InputArrayToProcess.setFormat("int int int int char*");

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aVolume16Reader->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT(OutputDCO, SoSFVtkObject );
	mOutputDCO = 0;

}

SoVtkVolume16Reader::~SoVtkVolume16Reader()
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
	
	if ( mOutputDCO )
	{
	
		mOutputDCO->unref();
		mOutputDCO = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkVolume16Reader::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkVolume16Reader, SoEngine, "Engine" );
}

void SoVtkVolume16Reader::evaluate()
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
		
		if ( mOutputDCO )
		{
		
			mOutputDCO->unref();
			mOutputDCO = 0;
		}
		
		// Get the input type(s)
		SoVtkObject *inputPtr = Input.getValue();
		
		if (inputPtr && inputPtr->getPointer()->IsA("vtkDataObject"))
			mObject->SetInput(vtkDataObject::SafeDownCast(inputPtr->getPointer()));

		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		mOutputDCO = new SoVtkObject();
		mOutputDCO->ref();
		mOutputDCO->setPointer( mObject );

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
	SO_ENGINE_OUTPUT( OutputDCO, SoSFVtkObject, setValue( mOutputDCO ) );
}


void SoVtkVolume16Reader::inputChanged(SoField * f)
{
	// Get the DataSpacing value
	if ( f == &DataSpacing )
		SO_VTK_SET_FIELD_VEC3F( mObject, DataSpacing);

	// Get the Transform value
	if ( f == &Transform )
		SO_VTK_SET_FIELD_DATA( mObject, Transform, vtkTransform);

	// Get the HeaderSize value
	if ( f == &HeaderSize )
		SO_VTK_SET_FIELD_VALUE( mObject, HeaderSize);

	// Get the DataDimensions value
	if ( f == &DataDimensions )
		SO_VTK_SET_FIELD_VEC2F( mObject, DataDimensions);

	// Get the FilePattern value
	if ( f == &FilePattern )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePattern);

	// Get the FilePrefix value
	if ( f == &FilePrefix )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FilePrefix);

	// Get the DataByteOrder value
	if ( f == &DataByteOrder )
		SO_VTK_SET_FIELD_VALUE( mObject, DataByteOrder);

	// Get the ImageRange value
	if ( f == &ImageRange )
		SO_VTK_SET_FIELD_VEC2F( mObject, ImageRange);

	// Get the SwapBytes value
	if ( f == &SwapBytes )
		SO_VTK_SET_FIELD_VALUE( mObject, SwapBytes);

	// Get the DataOrigin value
	if ( f == &DataOrigin )
		SO_VTK_SET_FIELD_VEC3F( mObject, DataOrigin);

	// Get the DataMask value
	if ( f == &DataMask )
		SO_VTK_SET_FIELD_VALUE( mObject, DataMask);

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
	//mObject->Update();
	
}
