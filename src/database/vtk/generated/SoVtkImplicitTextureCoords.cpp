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
 
 
# include "SoVtkImplicitTextureCoords.h"
# include "SoVtkUtils.h"

# include "vtkImplicitFunction.h"
# include "vtkAlgorithmOutput.h"
# include "vtkStructuredPoints.h"
# include "vtkStructuredGrid.h"
# include "vtkPolyData.h"
# include "vtkImageData.h"
# include "vtkDataSet.h"
# include "vtkUnstructuredGrid.h"
# include "vtkRectilinearGrid.h"


SO_ENGINE_SOURCE( SoVtkImplicitTextureCoords )

SoVtkImplicitTextureCoords::SoVtkImplicitTextureCoords()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImplicitTextureCoords);

	mObject = vtkImplicitTextureCoords::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImplicitTextureCoords *aImplicitTextureCoords = vtkImplicitTextureCoords::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(TFunction, (0));

	SO_ENGINE_ADD_INPUT(SFunction, (0));

	SO_ENGINE_ADD_INPUT(RFunction, (0));

	SO_ENGINE_ADD_INPUT(FlipTexture, (0));
	FlipTexture.setValue(aImplicitTextureCoords->GetFlipTexture());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImplicitTextureCoords->Delete();


	SO_ENGINE_ADD_OUTPUT( oStructuredPointsOutput, SoSFVtkObject );
	mStructuredPointsOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oRFunction, SoSFVtkObject );
	mRFunction = 0;
	SO_ENGINE_ADD_OUTPUT( oStructuredGridOutput, SoSFVtkObject );
	mStructuredGridOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oPolyDataOutput, SoSFVtkObject );
	mPolyDataOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oImageDataOutput, SoSFVtkObject );
	mImageDataOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oTFunction, SoSFVtkObject );
	mTFunction = 0;
	SO_ENGINE_ADD_OUTPUT( oSFunction, SoSFVtkObject );
	mSFunction = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( oUnstructuredGridOutput, SoSFVtkObject );
	mUnstructuredGridOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oRectilinearGridOutput, SoSFVtkObject );
	mRectilinearGridOutput = 0;


	addCalled = 0;
}

SoVtkImplicitTextureCoords::~SoVtkImplicitTextureCoords()
{
	// Deletion of the objects if they exist
	if ( mStructuredPointsOutput )
	{
	
		mStructuredPointsOutput->unref();
		mStructuredPointsOutput = 0;
	}
	
	if ( mRFunction )
	{
	
		mRFunction->unref();
		mRFunction = 0;
	}
	
	if ( mStructuredGridOutput )
	{
	
		mStructuredGridOutput->unref();
		mStructuredGridOutput = 0;
	}
	
	if ( mPolyDataOutput )
	{
	
		mPolyDataOutput->unref();
		mPolyDataOutput = 0;
	}
	
	if ( mImageDataOutput )
	{
	
		mImageDataOutput->unref();
		mImageDataOutput = 0;
	}
	
	if ( mTFunction )
	{
	
		mTFunction->unref();
		mTFunction = 0;
	}
	
	if ( mSFunction )
	{
	
		mSFunction->unref();
		mSFunction = 0;
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
	
	if ( mUnstructuredGridOutput )
	{
	
		mUnstructuredGridOutput->unref();
		mUnstructuredGridOutput = 0;
	}
	
	if ( mRectilinearGridOutput )
	{
	
		mRectilinearGridOutput->unref();
		mRectilinearGridOutput = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkImplicitTextureCoords::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImplicitTextureCoords, SoEngine, "Engine" );
}

void SoVtkImplicitTextureCoords::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
		if ( mStructuredPointsOutput )
		{
		
			mStructuredPointsOutput->unref();
			mStructuredPointsOutput = 0;
		}
		
		if ( mRFunction )
		{
		
			mRFunction->unref();
			mRFunction = 0;
		}
		
		if ( mStructuredGridOutput )
		{
		
			mStructuredGridOutput->unref();
			mStructuredGridOutput = 0;
		}
		
		if ( mPolyDataOutput )
		{
		
			mPolyDataOutput->unref();
			mPolyDataOutput = 0;
		}
		
		if ( mImageDataOutput )
		{
		
			mImageDataOutput->unref();
			mImageDataOutput = 0;
		}
		
		if ( mTFunction )
		{
		
			mTFunction->unref();
			mTFunction = 0;
		}
		
		if ( mSFunction )
		{
		
			mSFunction->unref();
			mSFunction = 0;
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
		
		if ( mUnstructuredGridOutput )
		{
		
			mUnstructuredGridOutput->unref();
			mUnstructuredGridOutput = 0;
		}
		
		if ( mRectilinearGridOutput )
		{
		
			mRectilinearGridOutput->unref();
			mRectilinearGridOutput = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetStructuredPointsOutput();
		mStructuredPointsOutput = new SoVtkObject();
		mStructuredPointsOutput->ref();
		mStructuredPointsOutput->setPointer( mObject->GetStructuredPointsOutput() );

		mObject->GetRFunction();
		mRFunction = new SoVtkObject();
		mRFunction->ref();
		mRFunction->setPointer( mObject->GetRFunction() );

		mObject->GetStructuredGridOutput();
		mStructuredGridOutput = new SoVtkObject();
		mStructuredGridOutput->ref();
		mStructuredGridOutput->setPointer( mObject->GetStructuredGridOutput() );

		mObject->GetPolyDataOutput();
		mPolyDataOutput = new SoVtkObject();
		mPolyDataOutput->ref();
		mPolyDataOutput->setPointer( mObject->GetPolyDataOutput() );

		mObject->GetImageDataOutput();
		mImageDataOutput = new SoVtkObject();
		mImageDataOutput->ref();
		mImageDataOutput->setPointer( mObject->GetImageDataOutput() );

		mObject->GetTFunction();
		mTFunction = new SoVtkObject();
		mTFunction->ref();
		mTFunction->setPointer( mObject->GetTFunction() );

		mObject->GetSFunction();
		mSFunction = new SoVtkObject();
		mSFunction->ref();
		mSFunction->setPointer( mObject->GetSFunction() );

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

		mObject->GetUnstructuredGridOutput();
		mUnstructuredGridOutput = new SoVtkObject();
		mUnstructuredGridOutput->ref();
		mUnstructuredGridOutput->setPointer( mObject->GetUnstructuredGridOutput() );

		mObject->GetRectilinearGridOutput();
		mRectilinearGridOutput = new SoVtkObject();
		mRectilinearGridOutput->ref();
		mRectilinearGridOutput->setPointer( mObject->GetRectilinearGridOutput() );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oStructuredPointsOutput, SoSFVtkObject, setValue( mStructuredPointsOutput ) );
	SO_ENGINE_OUTPUT( oRFunction, SoSFVtkObject, setValue( mRFunction ) );
	SO_ENGINE_OUTPUT( oStructuredGridOutput, SoSFVtkObject, setValue( mStructuredGridOutput ) );
	SO_ENGINE_OUTPUT( oPolyDataOutput, SoSFVtkObject, setValue( mPolyDataOutput ) );
	SO_ENGINE_OUTPUT( oImageDataOutput, SoSFVtkObject, setValue( mImageDataOutput ) );
	SO_ENGINE_OUTPUT( oTFunction, SoSFVtkObject, setValue( mTFunction ) );
	SO_ENGINE_OUTPUT( oSFunction, SoSFVtkObject, setValue( mSFunction ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( oUnstructuredGridOutput, SoSFVtkObject, setValue( mUnstructuredGridOutput ) );
	SO_ENGINE_OUTPUT( oRectilinearGridOutput, SoSFVtkObject, setValue( mRectilinearGridOutput ) );
}


void SoVtkImplicitTextureCoords::inputChanged(SoField * f)
{
	// Get the TFunction value
	if ( f == &TFunction )
		SO_VTK_SET_FIELD_DATA( mObject, TFunction, vtkImplicitFunction);

	// Get the SFunction value
	if ( f == &SFunction )
		SO_VTK_SET_FIELD_DATA( mObject, SFunction, vtkImplicitFunction);

	// Get the RFunction value
	if ( f == &RFunction )
		SO_VTK_SET_FIELD_DATA( mObject, RFunction, vtkImplicitFunction);

	// Get the FlipTexture value
	if ( f == &FlipTexture )
		SO_VTK_SET_FIELD_VALUE( mObject, FlipTexture);

	mObject->Update();
}

void SoVtkImplicitTextureCoords::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImplicitTextureCoords::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the TFunction value
	
		SO_VTK_SET_FIELD_DATA( mObject, TFunction, vtkImplicitFunction);

	// Get the SFunction value
	
		SO_VTK_SET_FIELD_DATA( mObject, SFunction, vtkImplicitFunction);

	// Get the RFunction value
	
		SO_VTK_SET_FIELD_DATA( mObject, RFunction, vtkImplicitFunction);

	// Get the FlipTexture value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FlipTexture);

	mObject->Update();
}
