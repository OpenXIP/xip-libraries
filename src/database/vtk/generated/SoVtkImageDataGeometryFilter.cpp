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
 
 
# include "SoVtkImageDataGeometryFilter.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkImageDataGeometryFilter )

SoVtkImageDataGeometryFilter::SoVtkImageDataGeometryFilter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageDataGeometryFilter);

	mObject = vtkImageDataGeometryFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageDataGeometryFilter *aImageDataGeometryFilter = vtkImageDataGeometryFilter::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(OutputTriangles, (0));
	OutputTriangles.setValue(aImageDataGeometryFilter->GetOutputTriangles());

	SO_ENGINE_ADD_INPUT(Extent, ());
	Extent.setFormat("int int int int int int");

	SO_ENGINE_ADD_INPUT(ThresholdCells, (0));
	ThresholdCells.setValue(aImageDataGeometryFilter->GetThresholdCells());

	SO_ENGINE_ADD_INPUT(ThresholdValue, (0));
	ThresholdValue.setValue(aImageDataGeometryFilter->GetThresholdValue());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageDataGeometryFilter->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageDataGeometryFilter::~SoVtkImageDataGeometryFilter()
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

void SoVtkImageDataGeometryFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageDataGeometryFilter, SoEngine, "Engine" );
}

void SoVtkImageDataGeometryFilter::evaluate()
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


void SoVtkImageDataGeometryFilter::inputChanged(SoField * f)
{
	// Get the OutputTriangles value
	if ( f == &OutputTriangles )
		SO_VTK_SET_FIELD_VALUE( mObject, OutputTriangles);

	// Get the Extent value
	if ( f == &Extent )
	{
		SbVariant *vExtent = (SbVariant *)Extent.getValues(0);
		SoInput input;
		int nb_fields = Extent.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		int val4;
		int val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vExtent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetExtent( 
				(int) val0,
				(int) val1,
				(int) val2,
				(int) val3,
				(int) val4,
				(int) val5
			);
		}
	}

	// Get the ThresholdCells value
	if ( f == &ThresholdCells )
		SO_VTK_SET_FIELD_VALUE( mObject, ThresholdCells);

	// Get the ThresholdValue value
	if ( f == &ThresholdValue )
		SO_VTK_SET_FIELD_VALUE( mObject, ThresholdValue);

	mObject->Update();
}

void SoVtkImageDataGeometryFilter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageDataGeometryFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the OutputTriangles value
	
		SO_VTK_SET_FIELD_VALUE( mObject, OutputTriangles);

	// Get the Extent value
	if (addCalled == 1)
	{
		SbVariant *vExtent = (SbVariant *)Extent.getValues(0);
		SoInput input;
		int nb_fields = Extent.getNum();

		int val0;
		int val1;
		int val2;
		int val3;
		int val4;
		int val5;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vExtent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			mObject->SetExtent( 
				(int) val0,
				(int) val1,
				(int) val2,
				(int) val3,
				(int) val4,
				(int) val5
			);
		}
	}

	// Get the ThresholdCells value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ThresholdCells);

	// Get the ThresholdValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ThresholdValue);

	mObject->Update();
}
