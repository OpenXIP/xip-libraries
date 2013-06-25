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
 
 
# include "SoVtkExtractTensorComponents.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"
# include "vtkStructuredPoints.h"
# include "vtkStructuredGrid.h"
# include "vtkDataSet.h"
# include "vtkRectilinearGrid.h"
# include "vtkUnstructuredGrid.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkExtractTensorComponents )

SoVtkExtractTensorComponents::SoVtkExtractTensorComponents()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkExtractTensorComponents);

	mObject = vtkExtractTensorComponents::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkExtractTensorComponents *aExtractTensorComponents = vtkExtractTensorComponents::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(NormalComponents, (0));

	SO_ENGINE_ADD_INPUT(NumberOfTCoords, (0));
	NumberOfTCoords.setValue(aExtractTensorComponents->GetNumberOfTCoords());

	SO_ENGINE_ADD_INPUT(VectorComponents, (0));

	SO_ENGINE_ADD_INPUT(ExtractScalars, (0));
	ExtractScalars.setValue(aExtractTensorComponents->GetExtractScalars());

	SO_ENGINE_ADD_INPUT(ExtractVectors, (0));
	ExtractVectors.setValue(aExtractTensorComponents->GetExtractVectors());

	SO_ENGINE_ADD_INPUT(TCoordComponents, (0));

	SO_ENGINE_ADD_INPUT(ExtractNormals, (0));
	ExtractNormals.setValue(aExtractTensorComponents->GetExtractNormals());

	SO_ENGINE_ADD_INPUT(ScalarMode, (0));
	ScalarMode.setValue(aExtractTensorComponents->GetScalarMode());

	SO_ENGINE_ADD_INPUT(PassTensorsToOutput, (0));
	PassTensorsToOutput.setValue(aExtractTensorComponents->GetPassTensorsToOutput());

	SO_ENGINE_ADD_INPUT(NormalizeNormals, (0));
	NormalizeNormals.setValue(aExtractTensorComponents->GetNormalizeNormals());

	SO_ENGINE_ADD_INPUT(ScalarComponents, (0,0));

	y = (int *) aExtractTensorComponents->GetScalarComponents();
	ScalarComponents.setValue((float) y[0],(float) y[1]);

	SO_ENGINE_ADD_INPUT(ExtractTCoords, (0));
	ExtractTCoords.setValue(aExtractTensorComponents->GetExtractTCoords());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aExtractTensorComponents->Delete();


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

SoVtkExtractTensorComponents::~SoVtkExtractTensorComponents()
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

void SoVtkExtractTensorComponents::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkExtractTensorComponents, SoEngine, "Engine" );
}

void SoVtkExtractTensorComponents::evaluate()
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


void SoVtkExtractTensorComponents::inputChanged(SoField * f)
{
	// Get the NormalComponents value
	if ( f == &NormalComponents )
	{
		if ( NormalComponents.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, NormalComponents);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the NumberOfTCoords value
	if ( f == &NumberOfTCoords )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfTCoords);

	// Get the VectorComponents value
	if ( f == &VectorComponents )
	{
		if ( VectorComponents.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, VectorComponents);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the ExtractScalars value
	if ( f == &ExtractScalars )
		SO_VTK_SET_FIELD_VALUE( mObject, ExtractScalars);

	// Get the ExtractVectors value
	if ( f == &ExtractVectors )
		SO_VTK_SET_FIELD_VALUE( mObject, ExtractVectors);

	// Get the TCoordComponents value
	if ( f == &TCoordComponents )
	{
		if ( TCoordComponents.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, TCoordComponents);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the ExtractNormals value
	if ( f == &ExtractNormals )
		SO_VTK_SET_FIELD_VALUE( mObject, ExtractNormals);

	// Get the ScalarMode value
	if ( f == &ScalarMode )
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarMode);

	// Get the PassTensorsToOutput value
	if ( f == &PassTensorsToOutput )
		SO_VTK_SET_FIELD_VALUE( mObject, PassTensorsToOutput);

	// Get the NormalizeNormals value
	if ( f == &NormalizeNormals )
		SO_VTK_SET_FIELD_VALUE( mObject, NormalizeNormals);

	// Get the ScalarComponents value
	if ( f == &ScalarComponents )
		SO_VTK_SET_FIELD_VEC2F( mObject, ScalarComponents);

	// Get the ExtractTCoords value
	if ( f == &ExtractTCoords )
		SO_VTK_SET_FIELD_VALUE( mObject, ExtractTCoords);

	mObject->Update();
}

void SoVtkExtractTensorComponents::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkExtractTensorComponents::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the NormalComponents value
	
	{
		if ( NormalComponents.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, NormalComponents);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the NumberOfTCoords value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfTCoords);

	// Get the VectorComponents value
	
	{
		if ( VectorComponents.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, VectorComponents);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the ExtractScalars value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ExtractScalars);

	// Get the ExtractVectors value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ExtractVectors);

	// Get the TCoordComponents value
	
	{
		if ( TCoordComponents.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, TCoordComponents);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the ExtractNormals value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ExtractNormals);

	// Get the ScalarMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarMode);

	// Get the PassTensorsToOutput value
	
		SO_VTK_SET_FIELD_VALUE( mObject, PassTensorsToOutput);

	// Get the NormalizeNormals value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NormalizeNormals);

	// Get the ScalarComponents value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, ScalarComponents);

	// Get the ExtractTCoords value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ExtractTCoords);

	mObject->Update();
}
