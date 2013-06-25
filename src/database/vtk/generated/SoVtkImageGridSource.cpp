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
 
 
# include "SoVtkImageGridSource.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkImageData.h"


SO_ENGINE_SOURCE( SoVtkImageGridSource )

SoVtkImageGridSource::SoVtkImageGridSource()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageGridSource);

	mObject = vtkImageGridSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageGridSource *aImageGridSource = vtkImageGridSource::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(DataSpacing, (0,0,0));

	x = aImageGridSource->GetDataSpacing();
	DataSpacing.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(GridSpacing, (0,0,0));

	y = (int *) aImageGridSource->GetGridSpacing();
	GridSpacing.setValue((float) y[0],(float) y[1],(float) y[2]);

	SO_ENGINE_ADD_INPUT(FillValue, (0));
	FillValue.setValue(aImageGridSource->GetFillValue());

	SO_ENGINE_ADD_INPUT(LineValue, (0));
	LineValue.setValue(aImageGridSource->GetLineValue());

	SO_ENGINE_ADD_INPUT(GridOrigin, (0,0,0));

	y = (int *) aImageGridSource->GetGridOrigin();
	GridOrigin.setValue((float) y[0],(float) y[1],(float) y[2]);

	SO_ENGINE_ADD_INPUT(DataOrigin, (0,0,0));

	x = aImageGridSource->GetDataOrigin();
	DataOrigin.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(DataScalarType, (0));
	DataScalarType.setValue(aImageGridSource->GetDataScalarType());

	SO_ENGINE_ADD_INPUT(DataExtent, (0));

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aImageGridSource->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageGridSource::~SoVtkImageGridSource()
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

void SoVtkImageGridSource::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageGridSource, SoEngine, "Engine" );
}

void SoVtkImageGridSource::evaluate()
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


void SoVtkImageGridSource::inputChanged(SoField * f)
{
	// Get the DataSpacing value
	if ( f == &DataSpacing )
		SO_VTK_SET_FIELD_VEC3F( mObject, DataSpacing);

	// Get the GridSpacing value
	if ( f == &GridSpacing )
		SO_VTK_SET_FIELD_VEC3F( mObject, GridSpacing);

	// Get the FillValue value
	if ( f == &FillValue )
		SO_VTK_SET_FIELD_VALUE( mObject, FillValue);

	// Get the LineValue value
	if ( f == &LineValue )
		SO_VTK_SET_FIELD_VALUE( mObject, LineValue);

	// Get the GridOrigin value
	if ( f == &GridOrigin )
		SO_VTK_SET_FIELD_VEC3F( mObject, GridOrigin);

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

	mObject->Update();
}

void SoVtkImageGridSource::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageGridSource::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the DataSpacing value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, DataSpacing);

	// Get the GridSpacing value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, GridSpacing);

	// Get the FillValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FillValue);

	// Get the LineValue value
	
		SO_VTK_SET_FIELD_VALUE( mObject, LineValue);

	// Get the GridOrigin value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, GridOrigin);

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

	mObject->Update();
}
