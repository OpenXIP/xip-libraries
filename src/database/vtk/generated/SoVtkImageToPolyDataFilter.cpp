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
 
 
# include "SoVtkImageToPolyDataFilter.h"
# include "SoVtkUtils.h"

# include "vtkScalarsToColors.h"
# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkImageToPolyDataFilter )

SoVtkImageToPolyDataFilter::SoVtkImageToPolyDataFilter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageToPolyDataFilter);

	mObject = vtkImageToPolyDataFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageToPolyDataFilter *aImageToPolyDataFilter = vtkImageToPolyDataFilter::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Decimation, (0));
	Decimation.setValue(aImageToPolyDataFilter->GetDecimation());

	SO_ENGINE_ADD_INPUT(LookupTable, (0));

	SO_ENGINE_ADD_INPUT(SubImageSize, (0));
	SubImageSize.setValue(aImageToPolyDataFilter->GetSubImageSize());

	SO_ENGINE_ADD_INPUT(Error, (0));
	Error.setValue(aImageToPolyDataFilter->GetError());

	SO_ENGINE_ADD_INPUT(OutputStyle, (0));
	OutputStyle.setValue(aImageToPolyDataFilter->GetOutputStyle());

	SO_ENGINE_ADD_INPUT(NumberOfSmoothingIterations, (0));
	NumberOfSmoothingIterations.setValue(aImageToPolyDataFilter->GetNumberOfSmoothingIterations());

	SO_ENGINE_ADD_INPUT(DecimationError, (0));
	DecimationError.setValue(aImageToPolyDataFilter->GetDecimationError());

	SO_ENGINE_ADD_INPUT(ColorMode, (0));
	ColorMode.setValue(aImageToPolyDataFilter->GetColorMode());

	SO_ENGINE_ADD_INPUT(Smoothing, (0));
	Smoothing.setValue(aImageToPolyDataFilter->GetSmoothing());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageToPolyDataFilter->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( oLookupTable, SoSFVtkObject );
	mLookupTable = 0;


	addCalled = 0;
}

SoVtkImageToPolyDataFilter::~SoVtkImageToPolyDataFilter()
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
	
	if ( mLookupTable )
	{
	
		mLookupTable->unref();
		mLookupTable = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkImageToPolyDataFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageToPolyDataFilter, SoEngine, "Engine" );
}

void SoVtkImageToPolyDataFilter::evaluate()
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
		
		if ( mLookupTable )
		{
		
			mLookupTable->unref();
			mLookupTable = 0;
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

		mObject->GetLookupTable();
		mLookupTable = new SoVtkObject();
		mLookupTable->ref();
		mLookupTable->setPointer( mObject->GetLookupTable() );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( oLookupTable, SoSFVtkObject, setValue( mLookupTable ) );
}


void SoVtkImageToPolyDataFilter::inputChanged(SoField * f)
{
	// Get the Decimation value
	if ( f == &Decimation )
		SO_VTK_SET_FIELD_VALUE( mObject, Decimation);

	// Get the LookupTable value
	if ( f == &LookupTable )
		SO_VTK_SET_FIELD_DATA( mObject, LookupTable, vtkScalarsToColors);

	// Get the SubImageSize value
	if ( f == &SubImageSize )
		SO_VTK_SET_FIELD_VALUE( mObject, SubImageSize);

	// Get the Error value
	if ( f == &Error )
		SO_VTK_SET_FIELD_VALUE( mObject, Error);

	// Get the OutputStyle value
	if ( f == &OutputStyle )
		SO_VTK_SET_FIELD_VALUE( mObject, OutputStyle);

	// Get the NumberOfSmoothingIterations value
	if ( f == &NumberOfSmoothingIterations )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfSmoothingIterations);

	// Get the DecimationError value
	if ( f == &DecimationError )
		SO_VTK_SET_FIELD_VALUE( mObject, DecimationError);

	// Get the ColorMode value
	if ( f == &ColorMode )
		SO_VTK_SET_FIELD_VALUE( mObject, ColorMode);

	// Get the Smoothing value
	if ( f == &Smoothing )
		SO_VTK_SET_FIELD_VALUE( mObject, Smoothing);

	mObject->Update();
}

void SoVtkImageToPolyDataFilter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageToPolyDataFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Decimation value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Decimation);

	// Get the LookupTable value
	
		SO_VTK_SET_FIELD_DATA( mObject, LookupTable, vtkScalarsToColors);

	// Get the SubImageSize value
	
		SO_VTK_SET_FIELD_VALUE( mObject, SubImageSize);

	// Get the Error value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Error);

	// Get the OutputStyle value
	
		SO_VTK_SET_FIELD_VALUE( mObject, OutputStyle);

	// Get the NumberOfSmoothingIterations value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfSmoothingIterations);

	// Get the DecimationError value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DecimationError);

	// Get the ColorMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ColorMode);

	// Get the Smoothing value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Smoothing);

	mObject->Update();
}
