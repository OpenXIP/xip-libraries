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
 
 
 
# include "SoVtkGenericProbeFilter.h"
# include "SoVtkUtils.h"

# include "vtkGenericDataSet.h"
# include "vtkDataSet.h"
# include "vtkAlgorithmOutput.h"
# include "vtkStructuredPoints.h"
# include "vtkStructuredGrid.h"
# include "vtkPolyData.h"
# include "vtkUnstructuredGrid.h"
# include "vtkRectilinearGrid.h"


SO_ENGINE_SOURCE( SoVtkGenericProbeFilter )

SoVtkGenericProbeFilter::SoVtkGenericProbeFilter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkGenericProbeFilter);

	mObject = vtkGenericProbeFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkGenericProbeFilter *aGenericProbeFilter = vtkGenericProbeFilter::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(Source, (0));

	SO_ENGINE_ADD_INPUT(Input, (0));

	SO_ENGINE_ADD_INPUT(NumberOfInputConnections, ());
	NumberOfInputConnections.setFormat("int int");

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aGenericProbeFilter->Delete();


	SO_ENGINE_ADD_OUTPUT( oStructuredPointsOutput, SoSFVtkObject );
	mStructuredPointsOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oStructuredGridOutput, SoSFVtkObject );
	mStructuredGridOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oPolyDataOutput, SoSFVtkObject );
	mPolyDataOutput = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( oUnstructuredGridOutput, SoSFVtkObject );
	mUnstructuredGridOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oRectilinearGridOutput, SoSFVtkObject );
	mRectilinearGridOutput = 0;
	SO_ENGINE_ADD_OUTPUT( oSource, SoSFVtkObject );
	mSource = 0;


	addCalled = 0;
}

SoVtkGenericProbeFilter::~SoVtkGenericProbeFilter()
{
	// Deletion of the objects if they exist
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
	
	if ( mPolyDataOutput )
	{
	
		mPolyDataOutput->unref();
		mPolyDataOutput = 0;
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
	
	if ( mSource )
	{
	
		mSource->unref();
		mSource = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkGenericProbeFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkGenericProbeFilter, SoEngine, "Engine" );
}

void SoVtkGenericProbeFilter::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkObject *inputPtr = Input.getValue();
		
		if (inputPtr && inputPtr->getPointer()->IsA("vtkDataSet"))
			mObject->SetInput(vtkDataSet::SafeDownCast(inputPtr->getPointer()));

		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		// Deletion of the objects if they exist
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
		
		if ( mPolyDataOutput )
		{
		
			mPolyDataOutput->unref();
			mPolyDataOutput = 0;
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
		
		if ( mSource )
		{
		
			mSource->unref();
			mSource = 0;
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

		mObject->GetStructuredGridOutput();
		mStructuredGridOutput = new SoVtkObject();
		mStructuredGridOutput->ref();
		mStructuredGridOutput->setPointer( mObject->GetStructuredGridOutput() );

		mObject->GetPolyDataOutput();
		mPolyDataOutput = new SoVtkObject();
		mPolyDataOutput->ref();
		mPolyDataOutput->setPointer( mObject->GetPolyDataOutput() );

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

		mObject->GetSource();
		mSource = new SoVtkObject();
		mSource->ref();
		mSource->setPointer( mObject->GetSource() );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oStructuredPointsOutput, SoSFVtkObject, setValue( mStructuredPointsOutput ) );
	SO_ENGINE_OUTPUT( oStructuredGridOutput, SoSFVtkObject, setValue( mStructuredGridOutput ) );
	SO_ENGINE_OUTPUT( oPolyDataOutput, SoSFVtkObject, setValue( mPolyDataOutput ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( oUnstructuredGridOutput, SoSFVtkObject, setValue( mUnstructuredGridOutput ) );
	SO_ENGINE_OUTPUT( oRectilinearGridOutput, SoSFVtkObject, setValue( mRectilinearGridOutput ) );
	SO_ENGINE_OUTPUT( oSource, SoSFVtkObject, setValue( mSource ) );
}


void SoVtkGenericProbeFilter::inputChanged(SoField * f)
{
	// Get the Source value
	if ( f == &Source )
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkGenericDataSet);

	// Get the NumberOfInputConnections value
	if ( f == &NumberOfInputConnections )
	{
		SbVariant *vNumberOfInputConnections = (SbVariant *)NumberOfInputConnections.getValues(0);
		SoInput input;
		int nb_fields = NumberOfInputConnections.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vNumberOfInputConnections[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			//mObject->SetNumberOfInputConnections( (int) val0, (int) val1 );
		}
	}

	mObject->Update();
}

void SoVtkGenericProbeFilter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkGenericProbeFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkObject *inputPtr = Input.getValue();
	
	if (inputPtr && inputPtr->getPointer()->IsA("vtkDataSet"))
		mObject->SetInput(vtkDataSet::SafeDownCast(inputPtr->getPointer()));

	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the Source value
	
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkGenericDataSet);

	// Get the NumberOfInputConnections value
	if (addCalled == 1)
	{
		SbVariant *vNumberOfInputConnections = (SbVariant *)NumberOfInputConnections.getValues(0);
		SoInput input;
		int nb_fields = NumberOfInputConnections.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vNumberOfInputConnections[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			//mObject->SetNumberOfInputConnections( (int) val0, (int) val1 );
		}
	}

	mObject->Update();
}

