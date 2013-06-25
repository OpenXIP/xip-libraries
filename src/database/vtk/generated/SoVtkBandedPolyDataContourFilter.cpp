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
 * \author Sylvain Jaume <sylvain.jaume@siemens.com>, Francois Huguet
 */
 
#include "SoVtkBandedPolyDataContourFilter.h"
#include "SoVtkUtils.h"

#include "vtkAlgorithmOutput.h"
#include "vtkPolyData.h"

SO_ENGINE_SOURCE( SoVtkBandedPolyDataContourFilter )

SoVtkBandedPolyDataContourFilter::SoVtkBandedPolyDataContourFilter()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkBandedPolyDataContourFilter);

	mObject = vtkBandedPolyDataContourFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkBandedPolyDataContourFilter *aBandedPolyDataContourFilter =
				 vtkBandedPolyDataContourFilter::New();

	SO_ENGINE_ADD_INPUT(ScalarMode, (0));
	ScalarMode.setValue(aBandedPolyDataContourFilter->GetScalarMode());

	SO_ENGINE_ADD_INPUT(NumberOfContours, (0));
	NumberOfContours.setValue(aBandedPolyDataContourFilter->
									GetNumberOfContours());

	SO_ENGINE_ADD_INPUT(Value, ());
	Value.setFormat("int double");

	SO_ENGINE_ADD_INPUT(GenerateContourEdges, (0));
	GenerateContourEdges.setValue(aBandedPolyDataContourFilter->
									GetGenerateContourEdges());

	SO_ENGINE_ADD_INPUT(Clipping, (0));
	Clipping.setValue(aBandedPolyDataContourFilter->GetClipping());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aBandedPolyDataContourFilter->Delete();

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

	SO_ENGINE_ADD_OUTPUT( oContourEdgesOutput, SoSFVtkObject );
	mContourEdgesOutput = 0;

	addCalled = 0;
}

SoVtkBandedPolyDataContourFilter::~SoVtkBandedPolyDataContourFilter()
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
	
	if ( mContourEdgesOutput )
	{
		mContourEdgesOutput->unref();
		mContourEdgesOutput = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
}

void SoVtkBandedPolyDataContourFilter::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkBandedPolyDataContourFilter, SoEngine,
								 "Engine" );
}

void SoVtkBandedPolyDataContourFilter::evaluate()
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
		
		if ( mContourEdgesOutput )
		{
		
			mContourEdgesOutput->unref();
			mContourEdgesOutput = 0;
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

		mObject->GetContourEdgesOutput();
		mContourEdgesOutput = new SoVtkObject();
		mContourEdgesOutput->ref();
		mContourEdgesOutput->setPointer( mObject->GetContourEdgesOutput() );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( oContourEdgesOutput, SoSFVtkObject, setValue( mContourEdgesOutput ) );
}


void SoVtkBandedPolyDataContourFilter::inputChanged(SoField * f)
{
	// Get the ScalarMode value
	if ( f == &ScalarMode )
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarMode);

	// Get the NumberOfContours value
	if ( f == &NumberOfContours )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfContours);

	// Get the Value value
	if ( f == &Value )
	{
		SbVariant *vValue = (SbVariant *)Value.getValues(0);
		SoInput input;
		int nb_fields = Value.getNum();

		int val0;
		double val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vValue[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetValue( 
				(int) val0,
				(double) val1
			);
		}
	}

	// Get the GenerateContourEdges value
	if ( f == &GenerateContourEdges )
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateContourEdges);

	// Get the Clipping value
	if ( f == &Clipping )
		SO_VTK_SET_FIELD_VALUE( mObject, Clipping);

	mObject->Update();
}

void SoVtkBandedPolyDataContourFilter::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkBandedPolyDataContourFilter::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the ScalarMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarMode);

	// Get the NumberOfContours value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfContours);

	// Get the Value value
	if (addCalled == 1)
	{
		SbVariant *vValue = (SbVariant *)Value.getValues(0);
		SoInput input;
		int nb_fields = Value.getNum();

		int val0;
		double val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vValue[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetValue( 
				(int) val0,
				(double) val1
			);
		}
	}

	// Get the GenerateContourEdges value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateContourEdges);

	// Get the Clipping value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Clipping);

	mObject->Update();
}

