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
 
 
# include "SoVtkDataObjectToDataSetFilter.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"
# include "vtkStructuredPoints.h"
# include "vtkStructuredGrid.h"
# include "vtkDataSet.h"
# include "vtkRectilinearGrid.h"
# include "vtkUnstructuredGrid.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkDataObjectToDataSetFilter )

SoVtkDataObjectToDataSetFilter::SoVtkDataObjectToDataSetFilter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDataObjectToDataSetFilter);

	mObject = vtkDataObjectToDataSetFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkDataObjectToDataSetFilter *aDataObjectToDataSetFilter = vtkDataObjectToDataSetFilter::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(DefaultNormalize, (0));
	DefaultNormalize.setValue(aDataObjectToDataSetFilter->GetDefaultNormalize());

	SO_ENGINE_ADD_INPUT(DataSetType, (0));
	SO_ENGINE_ADD_INPUT(Dimensions, (0,0,0));

	y = (int *) aDataObjectToDataSetFilter->GetDimensions();
	Dimensions.setValue((float) y[0],(float) y[1],(float) y[2]);

	SO_ENGINE_ADD_INPUT(Origin, (0,0,0));

	x = aDataObjectToDataSetFilter->GetOrigin();
	Origin.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Spacing, (0,0,0));

	x = aDataObjectToDataSetFilter->GetSpacing();
	Spacing.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aDataObjectToDataSetFilter->Delete();


	SO_ENGINE_ADD_OUTPUT( oImageDataOutput, SoSFVtkObject );
	mImageDataOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oStructuredPointsOutput, SoSFVtkObject );
	mStructuredPointsOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oStructuredGridOutput, SoSFVtkObject );
	mStructuredGridOutput = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oRectilinearGridOutput, SoSFVtkObject );
	mRectilinearGridOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oUnstructuredGridOutput, SoSFVtkObject );
	mUnstructuredGridOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( oPolyDataOutput, SoSFVtkObject );
	mPolyDataOutput = 0;


	addCalled = 0;
}

SoVtkDataObjectToDataSetFilter::~SoVtkDataObjectToDataSetFilter()
{
	// Deletion of the objects if they exist
	if ( mImageDataOutput )
	{
	
		mImageDataOutput->unref();
		mImageDataOutput = 0;
	}
	
	if ( mStructuredPointsOutput )
	{
	
		mStructuredPointsOutput->unref();
		mStructuredPointsOutput = 0;
	}
	
	if ( mStructuredGridOutput )
	{
	
		mStructuredGridOutput->unref();
		mStructuredGridOutput = 0;
	}
	
	if ( mOutput )
	{
	
		mOutput->unref();
		mOutput = 0;
	}
	
	if ( mRectilinearGridOutput )
	{
	
		mRectilinearGridOutput->unref();
		mRectilinearGridOutput = 0;
	}
	
	if ( mUnstructuredGridOutput )
	{
	
		mUnstructuredGridOutput->unref();
		mUnstructuredGridOutput = 0;
	}
	
	if ( mOutputPort )
	{
	
		mOutputPort->unref();
		mOutputPort = 0;
	}
	
	if ( mPolyDataOutput )
	{
	
		mPolyDataOutput->unref();
		mPolyDataOutput = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkDataObjectToDataSetFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDataObjectToDataSetFilter, SoEngine, "Engine" );
}

void SoVtkDataObjectToDataSetFilter::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mImageDataOutput )
		{
		
			mImageDataOutput->unref();
			mImageDataOutput = 0;
		}
		
		if ( mStructuredPointsOutput )
		{
		
			mStructuredPointsOutput->unref();
			mStructuredPointsOutput = 0;
		}
		
		if ( mStructuredGridOutput )
		{
		
			mStructuredGridOutput->unref();
			mStructuredGridOutput = 0;
		}
		
		if ( mOutput )
		{
		
			mOutput->unref();
			mOutput = 0;
		}
		
		if ( mRectilinearGridOutput )
		{
		
			mRectilinearGridOutput->unref();
			mRectilinearGridOutput = 0;
		}
		
		if ( mUnstructuredGridOutput )
		{
		
			mUnstructuredGridOutput->unref();
			mUnstructuredGridOutput = 0;
		}
		
		if ( mOutputPort )
		{
		
			mOutputPort->unref();
			mOutputPort = 0;
		}
		
		if ( mPolyDataOutput )
		{
		
			mPolyDataOutput->unref();
			mPolyDataOutput = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetImageDataOutput();
		mImageDataOutput = new SoVtkObject();
		mImageDataOutput->ref();
		mImageDataOutput->setPointer( mObject->GetImageDataOutput() );

		mObject->GetStructuredPointsOutput();
		mStructuredPointsOutput = new SoVtkObject();
		mStructuredPointsOutput->ref();
		mStructuredPointsOutput->setPointer( mObject->GetStructuredPointsOutput() );

		mObject->GetStructuredGridOutput();
		mStructuredGridOutput = new SoVtkObject();
		mStructuredGridOutput->ref();
		mStructuredGridOutput->setPointer( mObject->GetStructuredGridOutput() );

		mObject->GetOutput()->Register(0);
		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject->GetOutput() );

		mObject->GetRectilinearGridOutput();
		mRectilinearGridOutput = new SoVtkObject();
		mRectilinearGridOutput->ref();
		mRectilinearGridOutput->setPointer( mObject->GetRectilinearGridOutput() );

		mObject->GetUnstructuredGridOutput();
		mUnstructuredGridOutput = new SoVtkObject();
		mUnstructuredGridOutput->ref();
		mUnstructuredGridOutput->setPointer( mObject->GetUnstructuredGridOutput() );

		if ( mObject->GetNumberOfOutputPorts() > 0 )
		{
			mObject->GetOutputPort()->Register(0);
			mOutputPort = new SoVtkAlgorithmOutput();
			mOutputPort->ref();
			mOutputPort->setPointer( mObject->GetOutputPort() );
		}

		mObject->GetPolyDataOutput();
		mPolyDataOutput = new SoVtkObject();
		mPolyDataOutput->ref();
		mPolyDataOutput->setPointer( mObject->GetPolyDataOutput() );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oImageDataOutput, SoSFVtkObject, setValue( mImageDataOutput ) );
	SO_ENGINE_OUTPUT( oStructuredPointsOutput, SoSFVtkObject, setValue( mStructuredPointsOutput ) );
	SO_ENGINE_OUTPUT( oStructuredGridOutput, SoSFVtkObject, setValue( mStructuredGridOutput ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( oRectilinearGridOutput, SoSFVtkObject, setValue( mRectilinearGridOutput ) );
	SO_ENGINE_OUTPUT( oUnstructuredGridOutput, SoSFVtkObject, setValue( mUnstructuredGridOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( oPolyDataOutput, SoSFVtkObject, setValue( mPolyDataOutput ) );
}


void SoVtkDataObjectToDataSetFilter::inputChanged(SoField * f)
{
	// Get the DefaultNormalize value
	if ( f == &DefaultNormalize )
		SO_VTK_SET_FIELD_VALUE( mObject, DefaultNormalize);

	// Get the DataSetType value
	if ( f == &DataSetType )
		SO_VTK_SET_FIELD_VALUE( mObject, DataSetType);

	// Get the Dimensions value
	if ( f == &Dimensions )
		SO_VTK_SET_FIELD_VEC3F( mObject, Dimensions);

	// Get the Origin value
	if ( f == &Origin )
		SO_VTK_SET_FIELD_VEC3F( mObject, Origin);

	// Get the Spacing value
	if ( f == &Spacing )
		SO_VTK_SET_FIELD_VEC3F( mObject, Spacing);

	mObject->Update();
}

void SoVtkDataObjectToDataSetFilter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkDataObjectToDataSetFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the DefaultNormalize value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DefaultNormalize);

	// Get the DataSetType value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DataSetType);

	// Get the Dimensions value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Dimensions);

	// Get the Origin value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Origin);

	// Get the Spacing value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, Spacing);

	mObject->Update();
}
