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
 
 
# include "SoVtkGeometryFilter.h"
# include "SoVtkUtils.h"

# include "vtkPointLocator.h"
# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkGeometryFilter )

SoVtkGeometryFilter::SoVtkGeometryFilter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkGeometryFilter);

	mObject = vtkGeometryFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkGeometryFilter *aGeometryFilter = vtkGeometryFilter::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(CellClipping, (0));
	CellClipping.setValue(aGeometryFilter->GetCellClipping());

	SO_ENGINE_ADD_INPUT(Locator, (0));

	SO_ENGINE_ADD_INPUT(PointClipping, (0));
	PointClipping.setValue(aGeometryFilter->GetPointClipping());

	SO_ENGINE_ADD_INPUT(ExtentClipping, (0));
	ExtentClipping.setValue(aGeometryFilter->GetExtentClipping());

	SO_ENGINE_ADD_INPUT(Merging, (0));
	Merging.setValue(aGeometryFilter->GetMerging());

	SO_ENGINE_ADD_INPUT(Extent, ());
	Extent.setFormat("double double double double double double");

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aGeometryFilter->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oLocator, SoSFVtkObject );
	mLocator = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkGeometryFilter::~SoVtkGeometryFilter()
{
	// Deletion of the objects if they exist
	if ( mOutput )
	{
	
		mOutput->unref();
		mOutput = 0;
	}
	
	if ( mLocator )
	{
	
		mLocator->unref();
		mLocator = 0;
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

void SoVtkGeometryFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkGeometryFilter, SoEngine, "Engine" );
}

void SoVtkGeometryFilter::evaluate()
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
		
		if ( mLocator )
		{
		
			mLocator->unref();
			mLocator = 0;
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

		mObject->GetLocator();
		mLocator = new SoVtkObject();
		mLocator->ref();
		mLocator->setPointer( mObject->GetLocator() );

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
	SO_ENGINE_OUTPUT( oLocator, SoSFVtkObject, setValue( mLocator ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkGeometryFilter::inputChanged(SoField * f)
{
	// Get the CellClipping value
	if ( f == &CellClipping )
		SO_VTK_SET_FIELD_VALUE( mObject, CellClipping);

	// Get the Locator value
	if ( f == &Locator )
		SO_VTK_SET_FIELD_DATA( mObject, Locator, vtkPointLocator);

	// Get the PointClipping value
	if ( f == &PointClipping )
		SO_VTK_SET_FIELD_VALUE( mObject, PointClipping);

	// Get the ExtentClipping value
	if ( f == &ExtentClipping )
		SO_VTK_SET_FIELD_VALUE( mObject, ExtentClipping);

	// Get the Merging value
	if ( f == &Merging )
		SO_VTK_SET_FIELD_VALUE( mObject, Merging);

	// Get the Extent value
	if ( f == &Extent )
	{
		SbVariant *vExtent = (SbVariant *)Extent.getValues(0);
		SoInput input;
		int nb_fields = Extent.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
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
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5
			);
		}
	}

	mObject->Update();
}

void SoVtkGeometryFilter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkGeometryFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the CellClipping value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CellClipping);

	// Get the Locator value
	
		SO_VTK_SET_FIELD_DATA( mObject, Locator, vtkPointLocator);

	// Get the PointClipping value
	
		SO_VTK_SET_FIELD_VALUE( mObject, PointClipping);

	// Get the ExtentClipping value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ExtentClipping);

	// Get the Merging value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Merging);

	// Get the Extent value
	if (addCalled == 1)
	{
		SbVariant *vExtent = (SbVariant *)Extent.getValues(0);
		SoInput input;
		int nb_fields = Extent.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
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
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5
			);
		}
	}

	mObject->Update();
}
